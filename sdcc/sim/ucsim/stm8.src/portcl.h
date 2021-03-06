/*
 * Simulator of microcontrollers (stm8.src/portcl.h)
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

#ifndef PORTCL_HEADER
#define PORTCL_HEADER

#include "port_hwcl.h"


class cl_port: public cl_hw
{
 private:
  int portnr;
  t_addr base;
 public:
  class cl_memory_cell *cell_p, *cell_in, *cell_dir, *cell_cr1, *cell_cr2;
 public:
  cl_port(class cl_uc *auc, int iportnr/*, int aid*/, const char *aname);
  virtual int init(void);
  virtual void reset(void);

  virtual void write(class cl_memory_cell *cell, t_mem *val);

  virtual void print_info(class cl_console_base *con);

 private:
  bool pin_or_port_high(t_mem exti_conf1, t_mem exti_conf2);
  bool pin_or_port_low(t_mem exti_conf1, t_mem exti_conf2);
  bool port_used_for_interrupt(t_mem exti_conf1, t_mem exti_conf2);
  int port_sensitivity(t_mem exti_cr1, t_mem exti_cr2, t_mem exti_cr3, t_mem exti_cr4);
  void port_interrupt(t_mem *exti_sr1, t_mem *exti_sr2);
  void port_check_interrupt(t_mem input_and_enabled, t_mem in, t_mem prev_in, t_mem bitmask, int bithigh, int bitlow, t_mem exti_cr1, t_mem exti_cr2, t_mem exti_cr3, t_mem exti_cr4, t_mem *exti_sr1, t_mem *edge_exti_sr1, t_mem *exti_sr2, t_mem *edge_exti_sr2);
  void pin_check_interrupt(t_mem input_and_enabled, t_mem exti_crn, t_mem in, t_mem prev_in, int bithigh, int bitlow, t_mem *exti_sr1, t_mem *edge_exti_sr1);
};


#endif

/* End of stm8.src/portcl.h */
