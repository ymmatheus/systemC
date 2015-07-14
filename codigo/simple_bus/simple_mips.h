#ifndef __mips_stage_h
#define __mips_stage_h

#include "systemc.h"

#include "simple_bus_types.h"
#include "simple_bus_non_blocking_if.h"

#include <cstdint>



SC_MODULE(simple_mips){

    sc_in_clk clock;
    sc_port<simple_bus_non_blocking_if> bus_port;

    sc_event dec_ex;

    SC_HAS_PROCESS(simple_mips);

    // constructor
    simple_mips(sc_module_name _name , unsigned int unique_priority
        , unsigned int data_address ,unsigned int inst_address 
        , bool lock , int timeout)
    : sc_module(_name)
    , m_unique_priority(unique_priority)
    , m_data_address(data_address)
    , m_inst_address(inst_address)
    , m_lock(lock)
    , m_timeout(timeout)
    {


        SC_THREAD(fetch);
        sensitive << clock.pos();
        SC_THREAD(decode);
        sensitive << clock.pos();
        SC_THREAD(execute);
        sensitive << clock.pos();



        sc_fifo<int> IfId(1);
//        sc_fifo<int[9]> IdEx(1);
    }

    void fetch();
    void decode();
    void execute();

private:
  unsigned int m_unique_priority;
  unsigned int m_data_address;
  unsigned int m_inst_address;
  bool m_lock;
  int m_timeout;


  sc_fifo<int> IfId;
  //sc_fifo<int[9]> IdEx;



};





#endif
