#ifndef __exec_stage_h
#define __exec_stage_h

#include "systemc.h"


SC_MODULE(exec_stage){

    //funcao
    void proc();

    SC_HAS_PROCESS(exec_stage);

    exec_stage(sc_module_name _name, sc_event* exe_en )
    : sc_module(_name)
    , m_exe_en(exe_en)
    {
        SC_THREAD(proc);
    }
private:
    sc_event* m_exe_en;

};

#endif