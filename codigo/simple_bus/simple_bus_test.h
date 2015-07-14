/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2004 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************
 
  simple_bus_test.h : The test bench.
 
  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
 
 *****************************************************************************/

#ifndef __simple_bus_test_h
#define __simple_bus_test_h

#include <systemc.h>

#include "simple_bus_slow_mem.h"
#include "simple_bus.h"
#include "simple_bus_arbiter.h"
#include "simple_bus_test.h"
#include "simple_multiplier.h"					// multiply
#include "simple_mips.h"

SC_MODULE(simple_bus_test)
{
  // channels
  sc_clock C1;

  // module instances
  simple_bus_slow_mem            *mem_slow;
  simple_bus                     *bus;
  simple_bus_arbiter             *arbiter;
  simple_mips                      *mips;

  // constructor
  SC_CTOR(simple_bus_test)
    : C1("C1")
  {
    // create instances
    
    mem_slow = new simple_bus_slow_mem("mem_slow", 0x80, 0x18F, 1);
    bus = new simple_bus("bus",false); // verbose output
    //bus = new simple_bus("bus");
    arbiter = new simple_bus_arbiter("arbiter",false); // verbose output
    //arbiter = new simple_bus_arbiter("arbiter");

    mips = new simple_mips("mips",3,0x80, 0x90,false, 20);

    // connect instances
    
    bus->clock(C1);

    mem_slow->clock(C1);
    bus->arbiter_port(*arbiter);
    bus->slave_port(*mem_slow);
	
  mips->bus_port(*bus);
  mips->clock(C1);


  }

  // destructor
  ~simple_bus_test()
  {
    if (mem_slow)	{delete mem_slow; mem_slow = 0;}
    if (bus)		{delete bus; bus = 0;}
    if (arbiter)	{delete arbiter; arbiter = 0;}
    if (mips) {delete mips; mips = 0;}
  }

}; // end class simple_bus_test

#endif
