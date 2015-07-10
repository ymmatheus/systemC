#ifndef __fetch_stage_h
#define __fetch_stage_h

#include "systemc.h"

#include "simple_bus_types.h"
#include "simple_bus_non_blocking_if.h"


SC_MODULE(fetch_stage){

    //funcao
    void proc();


    SC_HAS_PROCESS(fetch_stage);

    fetch_stage(sc_module_name _name, sc_event* fet_en , 
                sc_port<simple_bus_non_blocking_if> bus_port,
                unsigned int inst_address,
                unsigned int unique_priority)
    : sc_module(_name)
    , m_fet_en(fet_en)
    , m_bus_port(bus_port)
    , m_inst_address(inst_address)
    , m_unique_priority(m_unique_priority)
    {
        SC_THREAD(proc);
    }
    
private:
    sc_event* m_fet_en;
    sc_port<simple_bus_non_blocking_if> m_bus_port;
    unsigned int m_inst_address;
    unsigned int unique_priority


};

#endif