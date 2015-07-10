/*
 *  Arquivo de testes das funcoes principais em funcoes.h e funcoes.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "funcoes.h"
#include "mips.h"
#include "isa.h"

void test_fetch(){

    PC = 0;
    MEM[0]=100;
    MEM[1]=101;
    MEM[2]=102;
    MEM[3]=103;
    printf("PC = %d\n", PC);
    printf("RI = %d\n", RI);

    PC = fetch(PC);
    printf("PC = %d\n", PC);
    printf("RI = %d\n", RI);

    PC = fetch(PC);
    printf("PC = %d\n", PC);
    printf("RI = %d\n", RI);

    PC = fetch(PC);
    printf("PC = %d\n", PC);
    printf("RI = %d\n", RI);

    PC = fetch(PC);
    printf("PC = %d\n", PC);
    printf("RI = %d\n", RI);        

    return;
}

void test_decode(){
    //addi $s0, $t0, 10
    RI = 0x2110000a;
    decode();
    printf("%x\n", RI);
    printf("funct %x\nshamt %x\nk16 %x\nrd %x\nrt %x\nrs %x\nk26 %x\nopcode %x\n\n", funct, shamnt, k16, rd, rt, rs, k26, opcode);

    //add $s3, $s1, $s0
    RI = 0x02309820;
    decode();
    printf("%x\n", RI);
    printf("funct %x\nshamt %x\nk16 %x\nrd %x\nrt %x\nrs %x\nk26 %x\nopcode %x\n\n", funct, shamnt, k16, rd, rt, rs, k26, opcode);

    //sw   $t2, 4($t0)
    RI = 0xad0a0004;
    decode();
    printf("%x\n", RI);
    printf("funct %x\nshamt %x\nk16 %x\nrd %x\nrt %x\nrs %x\nk26 %x\nopcode %x\n\n", funct, shamnt, k16, rd, rt, rs, k26, opcode);

    RI = 0x0f0f0f0f;
    decode();
    printf("%x\n", RI);
    printf("funct %x\nshamt %x\nk16 %x\nrd %x\nrt %x\nrs %x\nk26 %x\nopcode %x\n\n", funct, shamnt, k16, rd, rt, rs, k26, opcode);


    return;
}

void test_execute(){
    //add $t0, $t1, t2
    opcode=0;
    rs=t2;
    rt=t1;
    rd=t0;
    shamnt=0;
    funct=0x20;
    BREG[t0]=0;
    BREG[t1]=10;
    BREG[t2]=20;
    execute();
    printf("%d %d %d\n", BREG[t0], BREG[t1], BREG[t2]);

    //addi $t1, $t2, 1
    opcode=0x8;
    rs=t2;
    rt=t1;
    k16=1;
    BREG[t1]=10;
    BREG[t2]=20;
    execute();
    printf("%d %d %d\n", BREG[t0], BREG[t1], BREG[t2]);



    return;
}
void test_step(){
    PC = 0;
    MEM[0]=0x2110000a;//addi $s0, $t0, 10
    //00100001000100000000000000001010
    BREG[s0]=0;
    BREG[t0]=15;
    BREG[t2]=20;
    printf("BEFORE STEP!\n");
    printf("PC = %d\n", PC);
    printf("RI = %d\n", RI);
        dump_reg('d');
    printf("funct %x\nshamt %x\nk16 %x\nrd %x\nrt %x\nrs %x\nk26 %x\nopcode %x\n\n", funct, shamnt, k16, rd, rt, rs, k26, opcode);
    

    step();

    printf("AFTER STEP!\n");
    printf("PC = %d\n", PC);
    printf("RI = %d\n", RI);
        dump_reg('d');
    printf("funct %x\nshamt %x\nk16 %x\nrd %x\nrt %x\nrs %x\nk26 %x\nopcode %x\n\n", funct, shamnt, k16, rd, rt, rs, k26, opcode);

    return;
}

void test_run(){
    PC = 0;
    MEM[0]=0x21100002;//addi $s0, $t0, 10
    MEM[1]=0x21100004;//addi $s0, $t0, 10
    MEM[2]=0x21100006;//addi $s0, $t0, 10
    MEM[3]=0x21100008;//addi $s0, $t0, 10
    printf("BEFORE RUN!\n");
    dump_reg('d');
    run();

    printf("AFTER RUN!\n");
    dump_reg('d');
    return;
}

void test_dump_mem(){
    dump_mem(0, 10, 'd');
    return;
}

void test_dump_reg(){
    int i=0;
    for(i=0; i<32; i++){
        BREG[i]=i;
    }
    dump_reg('d');
    printf("\n");
    dump_reg('h');
    return;
}

void test_mem_mount(){
    mem_mount("code.bin", "data.bin");
    return;
}

int main(){

    //test_fetch();
    //test_decode();
    //test_execute();
    //test_step();
    //test_run();
    //test_dump_mem();
    //test_dump_reg();
    //test_mem_mount();

    return 0;
}