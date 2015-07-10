#ifndef __mips_stage_h
#define __mips_stage_h

#include "systemc.h"

#include "simple_bus_types.h"
#include "simple_bus_non_blocking_if.h"

#include "fetch.h"
#include "decode.h"
#include "exec.h"
#include "mem.h"
#include "wrback.h"

SC_MODULE(mips){

    fetch_stage*        fetch;
    decode_stage*       decode;
    exec_stage*         exec;
    mem_stage*          mem;
    wrback_stage*       wrback;

    sc_event fet_en, dec_en, exe_en, mem_en, wrb_en;
    
    sc_in_clk clk;
    sc_port<simple_bus_non_blocking_if> bus_port;

    void proc();
    SC_HAS_PROCESS(mips);

    // constructor
    mips(sc_module_name _name , unsigned int unique_priority
        , unsigned int data_address ,unsigned int inst_address 
        , bool lock , int timeout)
    : sc_module(_name)
    , m_unique_priority(unique_priority)
    , m_data_address(data_address)
    , m_inst_address(inst_address)
    , m_lock(lock)
    , m_timeout(timeout)
    {
        fetch   = new fetch_stage("fetch", &fet_en, &bus_port, inst_address);
        decode  = new decode_stage("decode", &dec_en);
        exec    = new exec_stage("exec", &exe_en);
        mem     = new mem_stage("mem", &mem_en, &bus_port), data_address;
        wrback  = new wrback_stage("wrback", &wrb_en);

        SC_THREAD(proc);
        sensitive << clk.pos();
        
    }

private:
  unsigned int m_unique_priority;
  unsigned int m_data_address;
  unsigned int m_inst_address;
  bool m_lock;
  int m_timeout;


};


#endif