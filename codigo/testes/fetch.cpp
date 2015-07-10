#include "systemc.h"

#ifndef FETCH
    #define FETCH
    #include "fetch.h"
#endif

void fetch_stage::proc(){

    while(1){
        
        wait(*m_fet_en);
    
        std::cout << sc_time_stamp() << ": fetch_stage\n";
    

    }

}