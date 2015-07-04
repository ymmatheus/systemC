/*
 *      Implementacao de funcoes do simulador
 *
 *
 *
 */


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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*A função unsigned  int32_t     fetch(uint32_t  pc) lê uma instrução da memória e coloca-
a em ri, atualizando o pc para apontar para a próxima instrução (soma 4).*/
uint32_t fetch(uint32_t pc){

    RI=MEM[pc/4];
    pc+=4;
    return pc;

}
/*Deve extrair todos os campos da instrução:
- opcode: código da operação
- rs: índice do primeiro registrador fonte
- rt: índice do segundo registrador fonte
- rd: índice do registrador destino, que recebe o resultado da operação
- shamnt: quantidade de deslocamento em instruções shift e rotate
- funct: código auxiliar para determinar a instrução a ser executada
- k16: constante de 16 bits, valor imediato em instruções tipo I
- k26: constante de 26 bits, para instruções tipo J*/
void decode(){
    
    uint32_t funct_mask = 0x3f;//111111
    funct = RI&funct_mask;

    uint32_t shamnt_shift=6;
    uint32_t shamnt_mask = 0x7c0;//11111000000
    shamnt = (RI&shamnt_mask)>>shamnt_shift;
    

    uint32_t rd_shift=11;
    uint32_t rd_mask = 0xf800;//1111100000000000
    rd = (RI&rd_mask)>>rd_shift;

    k16 = (funct|(shamnt<<shamnt_shift)|(rd<<rd_shift) );
    //printf("%d  %d\n", shamt, shamt_shift);

    uint32_t rt_shift=16;
    uint32_t rt_mask = 0x1f0000;//111110000000000000000
    rt = (RI&rt_mask)>>rt_shift;
    
    uint32_t rs_shift=21;
    uint32_t rs_mask = 0x3e00000;//11111000000000000000000000
    rs = (RI&rs_mask)>>rs_shift;

    k26 = k16|(rt<<rt_shift)|(rs<<rs_shift);
    
    uint32_t opcode_shift=26;
    opcode = RI>>opcode_shift;
    
    //printf("funct %x\nshamt %x\nk16 %x\nrd %x\nrt %x\nrs %x\nk26 %x\nopcode %x\n", funct, shamt, k16, rd, rt, rs, k26, opcode);

}
/*A função void   execute() executa a instrução que foi lida pela função
decodificada por decode()*/
void execute(){

    switch(opcode){

        case EXT:
            switch(funct){
                case ADD:
                    BREG[rd] = i_add(&BREG[rs], &BREG[rt]);
                    break;
                case SUB:
                    BREG[rd] = i_sub(&BREG[rs], &BREG[rt]);
                    break;
                case MULT:
                    i_mult(&BREG[rs], &BREG[rt]);
                    break;
                case DIV:
                    i_div(&BREG[rs], &BREG[rt]);
                    break;
                case AND:
                    BREG[rd] = i_and(&BREG[rs], &BREG[rt]);
                    break;
                case OR:
                    BREG[rd] = i_or(&BREG[rs], &BREG[rt]);
                    break;
                case XOR:
                    BREG[rd] = i_or(&BREG[rs], &BREG[rt]);
                    break;
                case NOR:
                    BREG[rd] = i_nor(&BREG[rs], &BREG[rt]);
                    break;
                case SLT:
                    BREG[rd] = i_slt(&BREG[rs], &BREG[rt]);
                    break;
                case JR:
                    i_jr(&BREG[rs]);
                    break;
                case SLL:
                    BREG[rt] = i_sll(&BREG[rs], k16);
                    break;
                case SRL:
                    BREG[rt] = i_srl(&BREG[rs], k16);
                    break;
                case SRA:
                    BREG[rt] = i_sra(&BREG[rs], k16);
                    break;
                case SYSCALL:
                    i_syscall();
                    break;
                case MFHI:
                    BREG[rt] = i_mfhi();
                    break;
                case MFLO:
                    BREG[rt] = i_mflo();
                    break;

            }
            break;
        case LW:
            BREG[rt] = i_lw(&BREG[rs], k16);
            break;
        case LB:
            BREG[rt] = i_lb(&BREG[rs], k16);
            break;
        case LBU:
            BREG[rt] = i_lbu(&BREG[rs], k16);
            break;
        case LH:
            BREG[rt] = i_lh(&BREG[rs], k16);
            break;
        case LHU:
            BREG[rt] = i_lhu(&BREG[rs], k16);
            break;
        case LUI:
            BREG[rt] = i_lui(k16);
            break;
        case SW:
            i_sw(&BREG[rs], k16, BREG[rt]);
            break;
        case SB:
            i_sb(&BREG[rs], k16, BREG[rt]);
            break;
        case SH:
            i_sh(&BREG[rs], k16, BREG[rt]);
            break;
        case BEQ:
            i_beq(&BREG[rs], &BREG[rt], k16);
            break;
        case BNE:
            i_bne(&BREG[rs], &BREG[rt], k16);
            break;          
        case BLEZ:
            i_blez(&BREG[rs], k16);
            break;      
        case BGTZ:
            i_bgtz(&BREG[rs], k16);
            break;  
        case ADDI:
            BREG[rt] = i_addi(&BREG[rs], k16);
            break;
        case ADDIU:
            BREG[rt] = i_addi(&BREG[rs], k16);
            break;      
        case SLTI:
            BREG[rt] = i_slti(&BREG[rs], k16);
            break; 
        case SLTIU:
            BREG[rt] = i_sltiu(&BREG[rs], k16);
            break; 
        case ANDI:
            BREG[rt] = i_andi(&BREG[rs], k16);
            break;  
        case ORI:
            BREG[rt] = i_ori(&BREG[rs], k16);
            break;
        case XORI:
            BREG[rt] = i_xori(&BREG[rs], k16);
            break; 
        case J:
            i_j(k26);
            break;
        case JAL:
            i_jal(k26);
            break;
        default:
            printf("Instrucao nao implementada!");
            break;
    }

}
/*A função step() executa uma instrução do MIPS:
step() => fecth(), decode(), execute()*/
void step(){

    PC = fetch(PC);
    decode();
    execute();
    
    if(PC > 4000 || (RI==0xc && BREG[v0]==10)){
        printf("\n*Programa terminado!*\n");
    }

    return;
}
/*A função run() executa o programa até encontrar uma chamada de sistema para
encerramento, ou até o pc ultrapassar o limite do segmento de código (4k words).*/
void run(){
    while(PC <= 4000 && !(RI==0xc && BREG[v0]==10)){
        step();
    }
    return;
}
/*Imprime o conteúdo da memória a partir do endereço start até o endereço end. O
formato pode ser em hexa (‘h’) ou decimal (‘d’).*/
void dump_mem(int start, int end, char format){

    int i=0;
    if(format=='h'){
        for(i=start; i<=end; i++){
            printf("(%2d) %08x\t",i, MEM[i]);
            if((i+1)%4==0){
                printf("\n");
            }
        }
        printf("\n\n");
    }
        
    else{
        for(i=start; i<=end; i++){
            printf("(%2d) %010d\t",i, MEM[i]);
            if((i+1)%4==0){
                printf("\n");
            }
        }
        printf("\n\n");
    }
        
}
/*Imprime o conteúdo dos registradores do MIPS, incluindo o banco de registradores e
os registradores pc, hi e lo. O formato pode ser em hexa (‘h’) ou decimal (‘d’).*/
void dump_reg(char format){
    int i=0;
    char reg_names[32][5] = {"zero","at","v0","v1","a0","a1","a2","a3","t0","t1","t2",
                             "t3","t4","t5","t6","t7","s0","s1","s2","s3","s4","s5",
                             "s6","s7","t8","t9","k0","k1","gp","sp","fp","ra"};
    if(format=='h'){
        for(i=0; i<32; i++){
            printf("($%s)$%2d: %08x\t",reg_names[i],i, BREG[i]);    
            if((i+1)%4 == 0){
                printf("\n");
            }            
        }
    }else{
        for(i=0; i<32; i++){
            printf("($%s)$%2d: %010d\t",reg_names[i],i, BREG[i]);
            if((i+1)%4 == 0){   
                printf("\n");
            }
        }
    }
        
}
/* Le arquivo com codigo binario do programa e arquivo binario dos dados e insere 
na variavel global memoria*/
void mem_mount(char* filename_text, char* filename_data){
    FILE* datafile = fopen(filename_data, "r");
    FILE* textfile = fopen(filename_text, "r");
    
    if(!datafile){
        printf("Nao foi possivel abrir o arquivo de dados!!!\n");
        return;
    }
    if(!textfile){
        printf("Nao foi possivel abrir o arquivo de codigo!!!\n");
        return;
    }

    int i=0, code=0; 
    char str[32];

    while( !feof(textfile) && strncmp(str,"\n",1) ){
        fscanf(textfile,"%s\n", str);
        code=strtol(str,NULL,2);        
        MEM[i]=code;
        i++;
    }
    MEM[i]=0x2002000a;
    MEM[i+1]=0xc;
    i=0;
    while( !feof(datafile) && strncmp(str,"\n",1) ){
        fscanf(datafile,"%s\n", str);
        code=strtol(str,NULL,2);        
        MEM[2048+i]=code;
        i++;
    }
    fclose(textfile);
    fclose(datafile);

    return;

}