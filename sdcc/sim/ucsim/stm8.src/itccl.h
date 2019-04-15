/*
 * Simulator of microcontrollers (itc.h)
 *
 * Copyright (C) 1999,99 Drotos Daniel, Talker Bt.
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

#ifndef STM8_ITCCL_HEADER
#define STM8_ITCCL_HEADER

#include "stypes.h"
#include "pobjcl.h"
#include "uccl.h"

#include "newcmdcl.h"


class cl_itc: public cl_hw
{
 public:
  class cl_memory_cell *spr[8];
  class cl_memory_cell *exti_cr1, *exti_cr2, *exti_cr3, *exti_cr4;
  class cl_memory_cell *exti_sr1, *exti_sr2;
  class cl_memory_cell *exti_conf1, *exti_conf2;
  class cl_memory_cell *wfe_cr1, *wfe_cr2, *wfe_cr3, *wfe_cr4;
 public:
  cl_itc(class cl_uc *auc);
  virtual int init(void);


  virtual void new_hw_added(class cl_hw *new_hw);
  virtual void added_to_uc(void);
  virtual t_mem read(class cl_memory_cell *cell);
  virtual void write(class cl_memory_cell *cell, t_mem *val);

  virtual int tick(int cycles);
  virtual void reset(void);
  virtual void happen(class cl_hw *where, enum hw_event he, void *params);

  virtual void print_info(class cl_console_base *con);
};

class cl_stm8_it_src: public cl_it_src
{
 private:
  class cl_stm8 *stm8;
  class cl_memory_cell *wfe_cell;
public:
  t_mem  wfe_mask; // Mask of bit in WFE_CR<n>

  cl_stm8_it_src(cl_uc  *Iuc,
            int    Inuof,
            class  cl_memory_cell *Iie_cell,
            t_mem  Iie_mask,
            class  cl_memory_cell *Isrc_cell,
            t_mem  Isrc_mask,
            class  cl_memory_cell *Iwfe_cell,
            t_mem  Iwfe_mask,
            t_addr Iaddr,
            bool   Iclr_bit,
            bool   Iindirect,
            const  char *Iname,
            int    apoll_priority);
  virtual ~cl_stm8_it_src(void) {}

  virtual bool pending(void);
};


#endif

/* End of s51.src/itc.h */
