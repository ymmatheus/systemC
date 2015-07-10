/*
 *  Arquivo de testes das intrucoes em isa.h e isa.c
 *  Ideia inicial era testar todas as instrucoes aqui, porem a maioria foi testada em tempo de execucao
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef FUNCOES
#include "funcoes.h"
#define FUNCOES
#endif

#ifndef MIPS
#include "mips.h"
#define MIPS
#endif

#ifndef ISA
#include "isa.h"
#define ISA
#endif

void test_i_lw(){
    BREG[t1]=0;
    MEM[8192] = 0x1f;
    BREG[t0] = i_lw(&BREG[t1], 0);
    printf("%x\n", BREG[t0]);
    return;
}
void test_i_lb(){
    BREG[t1]=0;
    MEM[8192] = 0x01020304;
    BREG[t0] = i_lb(&BREG[t1], 0);
    printf("%x\n", BREG[t0]);    
    return;
}
void test_i_lbu(){
    BREG[t1]=0;
    MEM[8192] = 0x01020304;
    BREG[t0] = i_lbu(&BREG[t1], 0);
    printf("%x\n", BREG[t0]);    
    return;
}
void test_i_lh(){
    BREG[t1]=0;
    MEM[8192] = 0x01020304;
    BREG[t0] = i_lh(&BREG[t1], 0);
    printf("%x\n", BREG[t0]);    
    return;
}
void test_i_lhu(){
    BREG[t1]=0;
    MEM[8192] = 0x01020304;
    BREG[t0] = i_lhu(&BREG[t1], 0);
    printf("%x\n", BREG[t0]);    
    return;
}
void test_i_lui(){
    return;
}
void test_i_sw(){

    RI=0x01020304;
    //sw t2, 0(t0)
    //1010 1101 0000 1010 0000 0000
    //rs 01 000 = 8  t0 br(t0) = 0x2000
    //rt 0 1010 = 10 t2 br(t2) = 1
    decode();
    BREG[rs]=0x2000;
    BREG[rt]=1;
    i_sw(&BREG[rs], k16, BREG[rt]);
    printf("%032x\n", MEM[2048]);

    return;
}
void test_i_sb(){

    RI=0x01020304;
    //sw t2, 0(t0)
    //1010 1101 0000 1010 0000 0000
    //rs 01 000 = 8  t0 br(t0) = 0x2000
    //rt 0 1010 = 10 t2 br(t2) = 1
    decode();
    BREG[rs]=0x2000;
    BREG[rt]=1;
    i_sb(&BREG[rs], k16, BREG[rt]);
    printf("%032x\n", MEM[2048]);

    return;
}
void test_i_sh(){

    RI=0x01020304;
    //sw t2, 0(t0)
    //1010 1101 0000 1010 0000 0000
    //rs 01 000 = 8  t0 br(t0) = 0x2000
    //rt 0 1010 = 10 t2 br(t2) = 1
    decode();
    BREG[rs]=0x2000;
    BREG[rt]=1;
    i_sh(&BREG[rs], k16, BREG[rt]);
    printf("%032x\n", MEM[2048]);

    return;
}
void test_i_beq(){
    return;
}
void test_i_bne(){
    return;
}
void test_i_blez(){
    return;
}
void test_i_bgtz(){
    return;
}
void test_i_addi(){

    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_addi(&BREG[t0], 0xff);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_slti(){
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_slti(&BREG[t0], 0x0);    
    printf("%x\n", BREG[s0]);

    BREG[t0] = 0x0f00ff00;
    BREG[s0] = i_slti(&BREG[t0], 0x0);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_sltiu(){
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_sltiu(&BREG[t0], 0x000f000);    
    printf("%x\n", BREG[s0]);

    BREG[t0] = 0x0000ff00;
    BREG[s0] = i_sltiu(&BREG[t0], 0x000f000);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_andi(){
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_andi(&BREG[t0], 0xff);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_ori(){
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_ori(&BREG[t0], 0xff);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_xori(){
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_xori(&BREG[t0], 0xff);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_j(){
    return;
}
void test_i_jal(){
    return;
}
void test_i_add(){
    BREG[t1] = 0x01020304;
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_add(&BREG[t0], &BREG[t1]);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_sub(){
    BREG[t1] = 0x01020304;
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_sub(&BREG[t0], &BREG[t1]);    
    printf("%x\n", BREG[s0]);    
    return;
}
void test_i_mult(){
    BREG[t0] = -1;
    BREG[t1] = 0x71c11112;
    i_mult(&BREG[t0], &BREG[t1]);
    //printf("HI: %x \nLO: %x\n",HI,LO );
    //printf("\n%x\n", BREG[t0]*BREG[t1]);

   // printf("HI: %d \nLO: %d\n",HI,LO );
    //printf("\n%d\n", BREG[t0]*BREG[t1]);
    return;
}
void test_i_div(){
    BREG[t1] = 2;
    BREG[t0] = 0x71c11113;
    i_div(&BREG[t0], &BREG[t1]);
    //printf("HI: %x \nLO: %x\n",HI,LO );
    //printf("\n%x\n", BREG[t0]*BREG[t1]);

   // printf("HI: %d \nLO: %d\n",HI,LO );
    //printf("\n%d\n", BREG[t0]*BREG[t1]);
}
void test_i_and(){
    BREG[t1] = 0x01020304;
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_and(&BREG[t0], &BREG[t1]);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_or(){
    BREG[t1] = 0x01020304;
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_or(&BREG[t0], &BREG[t1]);    
    printf("%x\n", BREG[s0]);    
    return;
}
void test_i_xor(){
    BREG[t1] = 0x01020304;
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_xor(&BREG[t0], &BREG[t1]);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_nor(){
    BREG[t1] = 0x01020304;
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_nor(&BREG[t0], &BREG[t1]);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_slt(){
    BREG[t1] = 0x01020304;
    BREG[t0] = 0xff00ff00;
    BREG[s0] = i_nor(&BREG[t0], &BREG[t1]);    
    printf("%x\n", BREG[s0]);

    BREG[t0] = 0x01020304;
    BREG[t1] = 0xff00ff00;
    BREG[s0] = i_nor(&BREG[t0], &BREG[t1]);    
    printf("%x\n", BREG[s0]);
    return;
}
void test_i_jr(){
    return;
}
void test_i_sll(){
    return;
}
void test_i_srl(){
    return;
}
void test_i_sra(){
    return;
}
void test_i_syscall(){
    
    //test print int
    BREG[v0] = 1;
    BREG[a0] = 10;
    i_syscall();
/*
1864397647  (2058) 0544175209   (2059) 1835627120   
(2060) 1869769061   (2061) 1970151539   (2062) 1869768045   (2063) 1919950963   
(2064) 1936682345   (2065) 1868657440   (2066) 0536879162

*/
MEM[2057] = 1864397647;
MEM[2058] = 544175209;
MEM[2059] = 1835627120;
MEM[2060] = 1869769061;
MEM[2061] = 1970151539;
MEM[2062] = 1869768045;
MEM[2063] = 1919950963;
MEM[2064] = 1936682345;
MEM[2065] = 1868657440;
MEM[2066] = 536879162;


    //test print string
    BREG[v0] = 4;
    BREG[a0] = 8228;
    //MEM[BREG[a0]] = 0x2024;
    //MEM[BREG[a0]+1] = 0x42002243;
    i_syscall();

    return;
}
void test_i_mfhi(){
    BREG[t0] = -1;
    BREG[t1] = 0x71c11112;
    i_mult(&BREG[t0], &BREG[t1]);
    printf("HI: %x\n\n", i_mfhi());
    return;
}
void test_i_mflo(){
    BREG[t0] = -1;
    BREG[t1] = 0x71c11112;
    i_mult(&BREG[t0], &BREG[t1]);
    printf("LO: %x\n\n", i_mflo());
    return;
}

int main(){

    // test_i_lw();
    // test_i_lb();
    // test_i_lbu();
    // test_i_lh();
    // test_i_lhu();
    // test_i_lui();
    // test_i_sw();
    // test_i_sb();
    // test_i_sh();
    // test_i_beq();
    // test_i_bne();
    // test_i_blez();
    // test_i_bgtz();
    // test_i_addi();
    // test_i_slti();
    // test_i_sltiu();
    // test_i_andi();
    // test_i_ori();
    // test_i_xori();
    // test_i_j();
    // test_i_jal();
    // test_i_add();
    // test_i_sub();
    // test_i_mult();
    // test_i_div();
    // test_i_and();
    // test_i_or();
    // test_i_xor();
    // test_i_nor();
    // test_i_slt();
    // test_i_jr();
    // test_i_sll();
    // test_i_srl();
    // test_i_sra();
    // test_i_syscall();
    // test_i_mfhi();
    // test_i_mflo();

    return 0;
}