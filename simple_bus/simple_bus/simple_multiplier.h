/*
 *  simple_multiplier.h
 *  simple_bus
 *
 *  Created by RJ on 18/07/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 *  Multiplier accessed through mapped I/O:
 *	0x100 - x address
 *  0x104 - y address
 *	0x108 - z address
 *  0x10C - start address
 */


#ifndef __simple_multiplier_h
#define __simple_multiplier_h

#include <systemc.h>

#include "simple_bus_types.h"
#include "simple_bus_slave_if.h"


class simple_multiplier
: public simple_bus_slave_if
, public sc_module
{
public:
	// ports
	sc_in_clk clock;
	
	SC_HAS_PROCESS(simple_multiplier);
	
	// constructor
	simple_multiplier(sc_module_name name_
					  , unsigned int start_address
					  , unsigned int end_address
					  , unsigned int nr_wait_states)
    : sc_module(name_)
    , m_start_address(start_address)
    , m_end_address(end_address)
    , m_nr_wait_states(nr_wait_states)
	{
		// process declaration
		SC_METHOD(wait_loop);
		dont_initialize();
		sensitive << clock.pos();
		
		sc_assert(m_start_address <= m_end_address);
		sc_assert((m_end_address-m_start_address+1)%4 == 0);
	}
	
	// process
	void wait_loop();
	
	// direct Slave Interface
	bool direct_read(int *data, unsigned int address);
	bool direct_write(int *data, unsigned int address);
	
	// Slave Interface
	simple_bus_status read(int *data, unsigned int address);
	simple_bus_status write(int *data, unsigned int address);
	
	unsigned int start_address() const;
	unsigned int end_address() const;	
	
private:
	int x, y, start, z;
	unsigned int m_start_address;
	unsigned int m_end_address;
	unsigned int m_nr_wait_states;
	int m_wait_count;
	
}; // end class

inline void simple_multiplier::wait_loop()
{
	if (m_wait_count >= 0) m_wait_count--;
}

inline bool simple_multiplier::direct_read(int *data, unsigned int address)
{
	switch (address) {
		case X_ADDRESS:
			*data = x;
			break;
		case Y_ADDRESS:
			*data = y;
			break;
		case Z_ADDRESS:
			*data = z;
			break;
		case START_ADDRESS:
			*data = start;
			break;			
		default:
			break;
	}
	return true;
}

inline bool simple_multiplier::direct_write(int *data, unsigned int address)
{
	{
		switch (address) {
			case X_ADDRESS:
				x = *data;
				break;
			case Y_ADDRESS:
				y = *data;
				break;
			case Z_ADDRESS:
				z = *data;
				break;
			case START_ADDRESS:
				start = *data;
				if (start == 1) {
					z = x * y;
				}
				break;			
			default:
				break;
		}
		return true;
	}
}

inline simple_bus_status simple_multiplier::read(int *data, unsigned int address)
{
 switch (address) {
	case X_ADDRESS:
		*data = x;
		break;
	case Y_ADDRESS:
		*data = y;
		break;
	case Z_ADDRESS:
		 if (m_wait_count == 0) {
			*data = z;
			return SIMPLE_BUS_OK;
		 }
		 return SIMPLE_BUS_WAIT;
		break;
	case START_ADDRESS:
		*data = start;
		break;			
	default:
		break;
    }
	return SIMPLE_BUS_OK;

}

inline simple_bus_status simple_multiplier::write(int *data, unsigned int address)
{
	switch (address) {
		case X_ADDRESS:
			x = *data;
			break;
		case Y_ADDRESS:
			y = *data;
			break;
		case START_ADDRESS:
			start = *data;
			if (start == 1) {
				m_wait_count = m_nr_wait_states;
				z = x * y;
			}				
			break;			
		default:
			break;
		}		
	return SIMPLE_BUS_OK;
}


inline unsigned int simple_multiplier::start_address() const
{
	return m_start_address;
}

inline unsigned int simple_multiplier::end_address() const
{
	return m_end_address;
}

	
#endif
