/*
 * Simulator of microcontrollers (stm8.src/flash.cc)
 *
 * Copyright (C) 2017,17 Drotos Daniel, Talker Bt.
 * 
 * To contact author send email to drdani@mazsola.iit.uni-miskolc.hu
 *
 */

/* This file is part of microcontroller simulator: ucsim.

UCSIM is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

UCSIM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with UCSIM; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA. */
/*@1@*/

#include <stdlib.h>

#include "globals.h"

#include "stm8cl.h"

#include "flashcl.h"


/* Address space/cell which can contain flash memory */

t_mem
cl_flash_cell::write(t_mem val)
{
  class cl_stm8 *uc= (cl_stm8 *)(application->get_uc());

  if (uc && uc->flash_ctrl)
    {
      enum stm8_flash_state state= uc->flash_ctrl->get_state();
      if (state == fs_powerdown || state == fs_standby)
        uc->flash_ctrl->wakeup();

      if (flags & CELL_READ_ONLY)
        {
          t_addr a;
          if (uc->rom->is_owned(this, &a))
            {
              uc->flash_ctrl->flash_write(a, val);
              return d();
            }
        }
    }
  return cl_cell8::write(val);
}

t_mem
cl_flash_cell::read(void)
{
  class cl_stm8 *uc= (cl_stm8 *)(application->get_uc());
  if (uc && uc->flash_ctrl)
    {
      enum stm8_flash_state state= uc->flash_ctrl->get_state();
      if (state == fs_powerdown || state == fs_standby)
        uc->flash_ctrl->wakeup();
    }

  return cl_cell8::read();
}

cl_flash_as::cl_flash_as(const char *id, t_addr astart, t_addr asize):
  cl_address_space(id, astart, asize, 8)
{
  class cl_flash_cell c8(8);
  class cl_memory_cell *cell= &c8;
  start_address= astart;
  decoders= new cl_decoder_list(2, 2, false);
  cella= (class cl_memory_cell *)malloc(size * sizeof(class cl_memory_cell));
  //cell->init();
  int i;
  for (i= 0; i < size; i++)
    {
      void *p= &(cella[i]);
      memcpy(p, cell, sizeof(class cl_memory_cell));
      cella[i].init();
    }
  dummy= new cl_dummy_cell(8);
  dummy->init();
}

int
cl_flash_as::init(void)
{
  return cl_address_space::init();
}


/* Flash controller */

cl_flash::cl_flash(class cl_uc *auc, t_addr abase, const char *aname):
	cl_hw(auc, HW_FLASH, 0, aname)
{
  base= abase;
  set_name(aname);
  wbuf_started= false;
  wbuf_start= 0;
  rww= true;
}

int
cl_flash::init(void)
{
  cl_hw::init();
  registration();
  reset();
  return 0;
}

char *
cl_flash::cfg_help(t_addr addr)
{
  switch (addr)
    {
    case stm8_flash_on: return (char*)"Turn simulation of flash on/off (bool, RW)";
    }
  return (char*)"Not used";
}

int
cl_flash::tick(int cycles)
{
  if (state & fs_busy)
    {
      double now= uc->get_rtime();
      double elapsed= (now - start_time) * 10e6;

      if ((state == fs_pre_erase) &&
	  (elapsed > tprog/2.0))
	{
	  int i;
	  uc->sim->app->debug("FLASH zeroing %06lx .. %d\n", wbuf_start, wbuf_size);
	  for (i= 0; i < wbuf_size; i++)
	    {
	      class cl_memory_cell *c= uc->rom->get_cell(wbuf_start + i);
	      c->download(0);
	    }
	  if (mode == fm_erase)
	    {
	      uc->sim->app->debug("FLASH end of erase, finish\n");
	      finish_program(true);
	    }
	  else
	    {
	      uc->sim->app->debug("FLASH end of erase, cont program\n");
	      state= fs_program;
	    }
	}
      else if (elapsed > tprog)
	{
	  int i;
	  uc->sim->app->debug("FLASH dl-ing %06lx .. %d\n", wbuf_start, wbuf_size);
	  for (i= 0; i < wbuf_size; i++)
	    {
	      class cl_memory_cell *c= uc->rom->get_cell(wbuf_start + i);
	      t_mem org= c->get();
	      c->download(org | wbuf[i]);
	    }
	  uc->sim->app->debug("FLASH end of program\n");
	  finish_program(true);
	}
    }
  return 0;
}

void
cl_flash::finish_program(bool ok)
{
  if (ok)
    iapsr->set_bit1(0x04);
  else
    iapsr->set_bit1(0x01);
  state= fs_wait_mode;
}

void
cl_flash::reset(void)
{
  uc->sim->app->debug("FLASH reset\n");
  puk1st= false;
  duk1st= false;
  p_unlocked= false;
  d_unlocked= false;
  p_failed= false;
  d_failed= false;

  state= fs_wait_mode;
  mode= fm_unknown;
  
  cr1r->write(0);
  iapsr->write(0x40);
  cr2r->write(0);
  if (ncr2r)
    ncr2r->write(0xff);
}

t_mem
cl_flash::read(class cl_memory_cell *cell)
{
  t_mem v= cell->get();

  if (cell == pukr)
    v= 0;
  else if (cell == dukr)
    v= 0;
  else if (cell == iapsr)
    {
      v&= ~0x0a;
      if (p_unlocked)
	v|= 0x02;
      if (d_unlocked)
	v|= 0x08;
      // read clears EOP and WR_PG_DIS bits
      cell->set(v & ~0x05);
      if (v & 0x05) uc->sim->app->debug("FLASH read iapsr5 %02x\n",v);	
    }
  return v;
}

void
cl_flash::write(class cl_memory_cell *cell, t_mem *val)
{
  if (conf(cell, val))
    return;

  if (conf(cell, NULL))
    return;
  
  if (cell == pukr)
    {
      uc->sim->app->debug("FLASH write-pukr %02x\n",*val);
      if (p_failed)
	;
      else if (!puk1st)
	{
	  if (*val == PMASS1)
	    puk1st= true;
	  else
	    p_failed= true;
	}
      else
	{
	  if (*val == PMASS2)
	    puk1st= false, p_unlocked= true;
	  else
	    puk1st= false, p_failed= true;
	}
      *val= 0;
    }
  else if (cell == dukr)
    {
      uc->sim->app->debug("FLASH write-dukr %02x\n",*val);
      if (d_failed)
	;
      else if (!duk1st)
	{
	  if (*val == DMASS1)
	    duk1st= true;
	  else
	    d_failed= true;
	}
      else
	{
	  if (*val == DMASS2)
	    duk1st= false, d_unlocked= true;
	  else
	    duk1st= false, d_failed= true;
	}
      *val= 0;
    }
  else if (cell == iapsr)
    {
      uc->sim->app->debug("FLASH write-iapsr %02x\n",*val);
      t_mem org= iapsr->get();
      // PUL, DUL
      if (!(*val & 0x02))
	p_unlocked= puk1st= false;
      if (!(*val & 0x08))
	d_unlocked= duk1st= false;
      *val&= ~0x0a;
      if (p_unlocked)
	*val|= 0x02;
      if (d_unlocked)
	*val|= 0x08;
      // HVOFF
      *val&= ~0x40;
      // EOP
      *val&= 0x40;
      if (org & 0x40)
	*val|= 0x40;
    }
  else if (cell == cr2r)
    {
      uc->sim->app->debug("FLASH write-cr2r %02x\n",*val);
      *val&= ~0x0e;
      if (state & fs_busy)
	{
	  *val&= ~0x30;
	  *val|= (cr2r->get() & 0x30);
	}
      if ((ncr2r == NULL) ||
	  (ncr2r->get() == ((~(*val))&0xff)))
	set_flash_mode(*val);
    }
  else if ((ncr2r != NULL) &&
	   (cell == ncr2r))
    {
      uc->sim->app->debug("FLASH write-ncr2r %02x\n",*val);
      *val|= 0x0e;
      if (state & fs_busy)
	{
	  *val&= ~0x30;
	  *val|= (ncr2r->get() & 0x30);
	}
      if (cr2r->get() == ((~(*val))&0xff))
	set_flash_mode((~(*val))&0xff);
    }
}

t_mem
cl_flash::conf_op(cl_memory_cell *cell, t_addr addr, t_mem *val)
{
  switch ((enum stm8_flash_cfg)addr)
    {
    case stm8_flash_on:
      if (val)
	{
	  if (*val)
	    on= true;
	  else
	    on= false;
	}
      else
	cell->set(on?1:0);
      break;
    case stm8_flash_nuof_cfg:
      break;
    }
  return cell->get();
}

void
cl_flash::flash_write(t_addr a, t_mem val)
{
  uc->sim->app->debug("FLASH wr(%06lx,%02x)\n",a,val);
  if (!uc)
    {
      uc->sim->app->debug("  no uc\n");
      return;
    }
  if (uc->rom == NULL)
    {
      uc->sim->app->debug("  no rom\n");
      return;
    }
  if ((a >= 0x8000) &&
      !p_unlocked)
    {
      uc->sim->app->debug("  plocked\n");
      return;
    }
  if ((a < 0x8000) &&
      !d_unlocked)
    {
      uc->sim->app->debug("  dlocked\n");
      return;
    }
  if (state & fs_busy)
    {
      uc->sim->app->debug("  busy %d\n",state);
      return;
    }

  uc->sim->app->debug("  wbuf_start=%06lx\n",wbuf_start);
  if (wbuf_start == 0)
    {
      uc->sim->app->debug("  calling start_wbuf(%06lx)\n",a);
      start_wbuf(a);
    }
  
  int offset= a - wbuf_start;
  uc->sim->app->debug("  offset=%d\n",offset);
  if (mode == fm_byte)
    {
      // fixup tprog
      wbuf[0]= uc->rom->get(wbuf_start + 0);
      wbuf[1]= uc->rom->get(wbuf_start + 1);
      wbuf[2]= uc->rom->get(wbuf_start + 2);
      wbuf[3]= uc->rom->get(wbuf_start + 3);
      if (tprog < 6000)
	{
	  if (wbuf[0] ||
	      wbuf[1] ||
	      wbuf[2] ||
	      wbuf[3])
	    tprog= 6000;
	}
      wbuf[offset]= val;
      if (tprog < 6000)
	start_program(fs_program);
    }
  else if (mode == fm_erase)
    {
      uc->sim->app->debug("  romwrite in erase mode\n");
      wbuf[offset]= val;
      wbuf_writes++;
      if ((wbuf_writes == 4) &&
	  (((a+1) % 4) == 0))
	{
	  u8_t v= 0;
	  v|= wbuf[0];
	  v|= wbuf[1];
	  v|= wbuf[2];
	  v|= wbuf[3];
	  if (v == 0)
	    {
	      uc->sim->app->debug("  starting erase\n");
	      start_program(fs_pre_erase);
	    }
	}
    }
  else
    {
      wbuf[offset]= val;
      wbuf_started= true;
      wbuf_writes++;
      if ((wbuf_writes == wbuf_size) ||
	  (offset == wbuf_size-1))
	{
	  if ((mode == fm_fast_word) ||
	      (mode == fm_fast_block))
	    start_program(fs_program);
	  else
	    start_program(fs_pre_erase);
	}
    }
}

// normal program: 6 ms
// fast program: 3 ms
// erase: 3 ms

void
cl_flash::set_flash_mode(t_mem cr2val)
{
  bool fix= cr1r->get() & 0x01; /* FIX */

  uc->sim->app->debug("FLASH set_mode %02x\n", cr2val);
  if (cr2val & 0x40 /* WPRG */ )
    {
      mode= fm_word;
      tprog= 6000; /* normal mode */
      wbuf_size= 4;
    }
  else if (cr2val & 0x20 /* ERASE */ )
    {
      mode= fm_erase;
      tprog= 3000;
      wbuf_size= 128;
    }
  else if (cr2val & 0x10 /* FPRG */ )
    {
      mode= fm_fast_block;
      tprog= 3000;
      wbuf_size= 128;
    }
  else if (cr2val & 0x01 /* PRG */ )
    {
      mode= fm_block;
      tprog= 6000;
      wbuf_size= 128;
    }
  else
    {
      mode= fm_byte;
      tprog= fix?6000:3000;
      wbuf_size= 4;
    }
  state= fs_wait_data;
  wbuf_started= false;
  wbuf_start= 0;
}

void
cl_flash::start_wbuf(t_addr addr)
{
  int i;
  wbuf_start= addr - (addr % wbuf_size);
  wbuf_writes= 0;
  for (i= 0; i < 256; i++)
    wbuf[i]= 0;
  uc->sim->app->debug("FLASH start_wbuf %06lx (wbuf_start=%06lx,size=%d)\n", addr, wbuf_start, wbuf_size);
}

void
cl_flash::start_program(enum stm8_flash_state start_state)
{
  uc->sim->app->debug("FLASH start prg %d\n", start_state);
  state= start_state;
  start_time= uc->get_rtime();
}

void
cl_flash::wait(void)
{
}

void
cl_flash::halt(void)
{
  state= fs_powerdown;
}

void
cl_flash::wakeup(void)
{
  class cl_stm8 *stm8 = (cl_stm8 *)uc;

  // Clocks are running and driving hardware but the CPU is stalled waiting for the
  // flash to become ready.
  if (state == fs_powerdown)
    {
      // RM0031 3.7: When the Flash program memory and data EEPROM exit from I_DDQ mode,
      // the recovery time is lower than 2.8µs and depends on supply voltage and temperature.
      stm8->tick_stall(0.0000028);
    }
  else if ((state & fs_standby))
    {
      // FIXME: 2ns assumed for flash wakeup from standby.
      stm8->tick_stall(0.000000002);
    }

  state= fs_wait_mode;
}

const char *
cl_flash::state_name(enum stm8_flash_state s)
{
  switch (s)
    {
    case fs_wait_mode: return "wait_mode";
    case fs_wait_data: return "wait_data";
    case fs_pre_erase: return "erase";
    case fs_program: return "program";
    case fs_busy: return "busy";
    case fs_standby: return "standby";
    case fs_powerdown: return "power-down";
    }
  return "unknown";
}
  
void
cl_flash::print_info(class cl_console_base *con)
{
  con->dd_printf(chars("", "Flash at %s\n", uc->rom->addr_format), base);
  con->dd_printf("PUK: ");
  if (p_failed)
    con->dd_printf("fail");
  else if (p_unlocked)
    con->dd_printf("unlocked");
  else if (puk1st)
    con->dd_printf("MASS1");
  else
    con->dd_printf("locked");
  con->dd_printf("\n");

  con->dd_printf("DUK: ");
  if (d_failed)
    con->dd_printf("fail");
  else if (d_unlocked)
    con->dd_printf("unlocked");
  else if (duk1st)
    con->dd_printf("MASS1");
  else
    con->dd_printf("locked");
  con->dd_printf("\n");

  con->dd_printf("State: %s\n", state_name(state));
  print_cfg_info(con);
}


/* SAF */

cl_saf_flash::cl_saf_flash(class cl_uc *auc, t_addr abase):
	cl_flash(auc, abase, "flash")
{
}

void
cl_saf_flash::registration(void)
{
  class cl_it_src *is;

  hwreg(uc->rom, base+0, "CR1", "Flash control register 1",
    "HALT",  3, 3, "Power-down in Halt mode",
    "AHALT", 2, 2, "Power-down in Active-halt mode",
    "IE",    1, 1, "Flash Interrupt enable",
    "FIX",   0, 0, "Fixed Byte programming time",
    NULL);
  cr1r= register_cell(uc->rom, base+0);

  hwreg(uc->rom, base+1, "CR2", "Flash control register 2",
    "OPT",   7, 7, "Write option bytes",
    "WPRG",  6, 6, "Word programming",
    "ERASE", 5, 5, "Block erasing",
    "FPRG",  4, 4, "Fast block programming",
    "PRG",   0, 0, "Standard block programming",
    NULL);
  cr2r= register_cell(uc->rom, base+1);

  hwreg(uc->rom, base+2, "NCR2", "Flash complementary control register 2",
    "NOPT",   7, 7, "Write option bytes",
    "NWPRG",  6, 6, "Word programming",
    "NERASE", 5, 5, "Block erasing",
    "NFPRG",  4, 4, "Fast block programming",
    "NPRG",   0, 0, "Standard block programming",
    NULL);
  ncr2r= register_cell(uc->rom, base+2);

  hwreg(uc->rom, base+3, "FPR", "Flash protection register",
    "WPB", 5, 0, "User boot code area protection bits",
    NULL);
  //fpr= register_cell(uc->rom, base+3);

  hwreg(uc->rom, base+4, "NFPR", "Flash protection register",
    "NWPB", 5, 0, "User boot code area protection bits",
    NULL);
  //nfpr= register_cell(uc->rom, base+3);

  hwreg(uc->rom, base+5, "IAPSR", "Flash status register",
    "HVOFF",     6, 6, "End of high voltage flag",
    "DUL",       3, 3, "Data EEPROM area unlocked flag",
    "EOP",       2, 2, "End of programming (write or erase operation) flag",
    "PUL",       1, 1, "Flash Program memory unlock flag",
    "WR_PG_DIS", 0, 0, "Write attempted to protected page flag",
    NULL);
  iapsr= register_cell(uc->rom, base+5);

  hwreg(uc->rom, base+8, "PUKR", "Flash program memory unprotecting key register",
    "PUK", 7, 0, "Main program memory unlock keys",
    NULL);
  pukr= register_cell(uc->rom, base+8);

  hwreg(uc->rom, base+10, "DUKR", "Data EEPROM unprotection key register",
    "DUK", 7, 0, "Data EEPROM write unlock keys",
    NULL);
  dukr= register_cell(uc->rom, base+10);

  uc->it_sources->add(is= new cl_it_src(uc, 24,
					cr1r,0x02,
					iapsr,0x04,
					0x8008+24*4, false, false,
					"FLASH_EOP", 20*20+0));
  uc->it_sources->add(is= new cl_it_src(uc, 24,
					cr1r,0x02,
					iapsr,0x01,
					0x8008+24*4, false, false,
					"FLASH_RO", 20*20+1));
  is->init();
}

void
cl_saf_flash::halt(void)
{
  // Active-halt if AWU/RTC is enabled, Halt otherwise.
  // FIXME: need to check once AWU/RTC are implemented.
  if (1)
    {
      // Active-halt
      // RM0016 10.3.2: By default the Flash remains in operating mode. Setting
      // AHALT in FLASH_CR1 causes the Flash to power-down instead.
      if ((cr1r->get() & 0x04))
        state= fs_powerdown;
    }
  else
    {
      // Halt
      // RM0016 10.3.1: By default the Flash is in power-down state. Setting HALT
      // in FLASH_CR1 causes the Flash to go to Standby mode instead.
      state= ((cr1r->get() & 0x08) ? fs_standby : fs_powerdown);
    }
}

void
cl_saf_flash::wakeup(void)
{
  static bool notified = false;
  if (!notified && uc->xtal / uc->clock_per_cycle() > 250000)
    {
      notified = true;
      uc->error(new cl_errata("Reduce f_CPU to 250kHz or lower to ensure correct Flash memory wakeup."));
    }

  cl_flash::wakeup();
}


/* L101 */

cl_l101_flash::cl_l101_flash(class cl_uc *auc, t_addr abase):
	cl_flash(auc, abase, "flash")
{
}

void
cl_l101_flash::registration(void)
{
  class cl_it_src *is;

  hwreg(uc->rom, base+0, "CR1", "Flash control register 1",
    "IE",    1, 1, "Flash Interrupt enable",
    "FIX",   0, 0, "Fixed Byte programming time",
    NULL);
  cr1r= register_cell(uc->rom, base+0);

  hwreg(uc->rom, base+1, "CR2", "Flash control register 2",
    "OPT",   7, 7, "Write option bytes",
    "WPRG",  6, 6, "Word programming",
    "ERASE", 5, 5, "Block erasing",
    "FPRG",  4, 4, "Fast block programming",
    "PRG",   0, 0, "Standard block programming",
    NULL);
  cr2r= register_cell(uc->rom, base+1);
  ncr2r= NULL;

  hwreg(uc->rom, base+2, "PUKR", "Flash program memory unprotecting key register",
    "PUK", 7, 0, "Main program memory unlock keys",
    NULL);
  pukr= register_cell(uc->rom, base+2);

  hwreg(uc->rom, base+3, "DUKR", "Data EEPROM unprotection key register",
    "DUK", 7, 0, "Data EEPROM write unlock keys",
    NULL);
  dukr= register_cell(uc->rom, base+3);

  hwreg(uc->rom, base+4, "IAPSR", "Flash status register",
    "DUL",       3, 3, "Data EEPROM area unlocked flag",
    "EOP",       2, 2, "End of programming (write or erase operation) flag",
    "PUL",       1, 1, "Flash Program memory unlock flag",
    "WR_PG_DIS", 0, 0, "Write attempted to protected page flag",
    NULL);
  iapsr= register_cell(uc->rom, base+4);
  
  uc->it_sources->add(is= new cl_it_src(uc, 1,
					cr1r,0x02,
					iapsr,0x04,
					0x8008+1*4, false, false,
					"FLASH_EOP", 20*20+0));
  uc->it_sources->add(is= new cl_it_src(uc, 1,
					cr1r,0x02,
					iapsr,0x01,
					0x8008+1*4, false, false,
					"FLASH_RO", 20*20+1));
  is->init();
}


/* AL and L */

cl_l_flash::cl_l_flash(class cl_uc *auc, t_addr abase):
  cl_l101_flash(auc, abase)
{
}

void
cl_l_flash::registration(void)
{
  cl_l101_flash::registration();

  hwreg("CR1",
    "EEPM",  3, 3, "Flash program and data EEPROM I_DDQ mode selection during run, low power run and low power wait mode",
    "WAITM", 2, 2, "Flash program and data EEPROM I_DDQ mode during wait mode",
    NULL);
}

void
cl_l_flash::write(class cl_memory_cell *cell, t_mem *val)
{
  // RM0031 3.9.1: Setting EEPM forces the flash and data EEPROM into I_DDQ mode.
  if (cell == cr1r && (cr1r->get() & 0x08))
    state= fs_powerdown;

  cl_flash::write(cell, val);
}

void
cl_l_flash::wait(void)
{
  // RM0031 3.9.1: WAITM puts the flash and data EEPROM in I_DDQ mode when the
  // device is in wait mode.
  if ((cr1r->get() & 0x04))
    state= fs_powerdown;
}

void
cl_l_flash::wakeup(void)
{
  static bool notified = false;
  if (!notified && uc->xtal / uc->clock_per_cycle() > 8000000)
    {
      notified = true;
      uc->error(new cl_errata("Reduce f_CPU to 8MHz or lower to ensure correct Flash memory wakeup."));
    }

  cl_flash::wakeup();

  // RM0031 3.9.1: EEPM is cleared by hardware just after a FLash or data EEPROM
  // memory access.
  // We actually do it before the access in the code but at the same simulation
  // time as the access and after the wakeup.
  t_mem cr1v = cr1r->get();
  if ((cr1v & 0x08))
    cr1r->write(cr1v & (~0x08));
}


/* End of stm8.src/flash.cc */
