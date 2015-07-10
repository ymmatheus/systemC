#ifndef __wrback_stage_h
#define __wrback_stage_h

#include "systemc.h"

SC_MODULE(wrback_stage){

    //funcao
    void proc();

    SC_HAS_PROCESS(wrback_stage);

    wrback_stage(sc_module_name _name, sc_event* wrb_en )
    : sc_module(_name)
    , m_wrb_en(wrb_en)
    {
        SC_THREAD(proc);
    }
private:
    sc_event* m_wrb_en;


};

#endif