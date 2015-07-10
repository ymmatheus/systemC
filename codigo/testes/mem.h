#ifndef __mem_stage_h
#define __mem_stage_h

#include "systemc.h"

SC_MODULE(mem_stage){

    //funcao
    void proc();

    SC_HAS_PROCESS(mem_stage);

    mem_stage(sc_module_name _name, sc_event* mem_en )
    : sc_module(_name)
    , m_mem_en(mem_en)
    {
        SC_THREAD(proc);
    }
private:
    sc_event* m_mem_en;

};

#endif