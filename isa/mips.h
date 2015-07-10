/*
 * mips.h
 *
 * contem variaveis globais contantes e outros
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MEM_SIZE 8192

//Memoria
int32_t MEM[ MEM_SIZE ];


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

uint32_t BREG[32];
uint32_t PC;
uint32_t RI;
uint32_t HI;
uint32_t LO;

uint32_t opcode,rs,rt,rd,shamnt,funct,k16,k26;

//int FLAG_RUN=1;
//int FLAG_STEP=1;