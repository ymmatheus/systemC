#include "systemc.h"

#ifndef MEM
    #define MEM
    #include "mem.h"
#endif

void mem_stage::proc(){

    while(1){
        wait(*m_mem_en);

        std::cout << sc_time_stamp() << ": mem_stage\n";
        
    }

}
