#include "systemc.h"

#ifndef MIPS
    #define MIPS
    #include "mips.h"
#endif

int sc_main (int argc , char *argv[]) {

    //sc_clock clk;
    sc_signal<bool> clk;
    
    mips mips("mips");
    mips.clk(clk);
    
    clk=0;
    sc_start(1,SC_NS);

    clk=1;
    sc_start(1,SC_NS);

    clk=0;
    sc_start(1,SC_NS);

    clk=1;
    sc_start(1,SC_NS);

    clk=0;
    sc_start(1,SC_NS);

    clk=1;
    sc_start(1,SC_NS);

    clk=0;
    sc_start(1,SC_NS);

    clk=1;
    sc_start(1,SC_NS);

    clk=0;
    sc_start(1,SC_NS);

    clk=1;
    sc_start(1,SC_NS);

    clk=0;
    sc_start(1,SC_NS); 
    

    return 0;
}