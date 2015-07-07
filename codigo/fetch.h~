#include "systemc.h"

#include "simple_bus_types.h"
#include "simple_bus_non_blocking_interface.h"

SC_MODULE(fetch){

	sc_in<bool> clock;
	sc_in_rv<32> PC;
	sc_lv<32> PCPlus4F;
	sc_out_rv<32> Inst;

	SC_CTOR(fetch){
		SC_METHOD(somador);
		sensitive << clock.pos();
		SC_METHOD(buscainst);
		sensitive << clock.pos();
	}
	void somador();
	void buscainst();

};
