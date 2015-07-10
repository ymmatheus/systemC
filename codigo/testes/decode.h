#ifndef __decode_stage_h
#define __decode_stage_h

#include "systemc.h"

SC_MODULE(decode_stage){

    //funcao
    void proc();


    SC_HAS_PROCESS(decode_stage);

    decode_stage(sc_module_name _name, sc_event* dec_en )
    : sc_module(_name)
    , m_dec_en(dec_en)
    {
        SC_THREAD(proc);
    }
private:
    sc_event* m_dec_en;

};

#endif