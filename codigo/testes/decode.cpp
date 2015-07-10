#include "systemc.h"

#ifndef DECODE
    #define DECODE
    #include "decode.h"
#endif

void decode_stage::proc(){

    while(1){

        wait(*m_dec_en);
        
        std::cout << sc_time_stamp() << ": decode_stage\n";
        
        
    }

}
