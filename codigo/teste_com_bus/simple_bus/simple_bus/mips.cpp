#include "systemc.h"
#include "mips.h"

void mips::proc(){
/*
    fet_en.notify();
    
    // wait(10,SC_NS);
    wait();

    fet_en.notify();
    dec_en.notify();
    
    // wait(sc_time(10,SC_NS));
    wait();

    fet_en.notify();
    dec_en.notify();
    exe_en.notify();
    
    // wait(sc_time(10,SC_NS));
    wait();

    fet_en.notify();
    dec_en.notify();
    exe_en.notify();
    mem_en.notify();

*/
    
    while(1){
    
        wait();    
        // wait(sc_time(10,SC_NS));
        fet_en.notify();
/*        dec_en.notify();
        exe_en.notify();
        mem_en.notify();
        exe_en.notify();
*/


    }

}



