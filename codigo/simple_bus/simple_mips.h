#ifndef __mips_stage_h
#define __mips_stage_h

#include "systemc.h"

#include "simple_bus_types.h"
#include "simple_bus_non_blocking_if.h"

#include <cstdint>

typedef struct pipeline_signals_t{
  
  unsigned int ri;
  unsigned int pc;



} pipeline_sigs;



//Banco de registradores
enum REGS {
    zero=0,     at=1,       v0=2,       v1=3,       a0=4,
    a1=5,       a2=6,       a3=7,       t0=8,       t1=9,
    t2=10,      t3=11,      t4=12,      t5=13,      t6=14,
    t7=15,      s0=16,      s1=17,      s2=18,      s3=19,
    s4=20,      s5=21,      s6=22,      s7=23,      t8=24,
    t9=25,      k0=26,      k1=27,      gp=28,      sp=29,
    fp=30,      ra=31
};


enum OPCODES{
    EXT=0x00,   LW=0x23,    LB=0x20,    LBU=0x24,  
    LH=0x21,    LHU=0x25,   LUI=0x0F,   SW=0x2B,
    SB=0x28,    SH=0x29,    BEQ=0x04,   BNE=0x05,  
    BLTZ=0x06,  BGEZ=0x07,  ADDI=0x08,  SLTI=0x0A, 
    SLTIU=0x0B, ANDI=0x0C,  ORI=0x0D,   XORI=0x0E, 
    J=0x02,     JAL=0x03,   ADDIU=0x09, MUL=0x1C,
    MTHI=0x11,  MTLO=0x13,  SE=0x1F
}; 

enum FUNCT {   
    ADD=0x20,   ADDU=0x21,  SUB=0x22,   MULT=0x18,   DIV=0x1A,     AND=0x24,  
    OR=0x25,    XOR=0x26,   NOR=0x27,   SLT=0x2A,       JR=0x08,  SUBU=0x23,
    SLL=0x00,   SRL=0x02,   SRA=0x03,   SYSCALL=0x0c,   MFHI=0x10, MFLO=0x12,
  
};



SC_MODULE(simple_mips){

    sc_in_clk clock;
    sc_port<simple_bus_non_blocking_if> bus_port;

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


      cout << " aaazzz!!";
        SC_THREAD(fetch);
        sensitive << clock.pos();
        SC_THREAD(decode);
        sensitive << clock.pos();
        SC_THREAD(execute);
        sensitive << clock.pos();



        sc_fifo<int> IfId(1);
        sc_fifo<int> IdEx(1);
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
  sc_fifo<int> IdEx;
  //sc_fifo<pipeline_sigs> IfId(0);
  //sc_fifo<pipeline_sigs> IdEx(0);



};





#endif