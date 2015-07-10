#include "systemc.h"

#ifndef WRBACK
    #define WRBACK
    #include "wrback.h"
#endif

void wrback_stage::proc(){

    while(1){
        wait(*m_wrb_en);
        
        std::cout << sc_time_stamp() << ": wrback_stage\n";
    }

}
