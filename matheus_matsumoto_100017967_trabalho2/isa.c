/*
 *      Implementacao das instrucoes MIPS
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef ISA
#include "isa.h"
#define ISA
#endif


#ifndef MIPS
#include "mips.h"
#define MIPS
#endif


//lw $t1,-100($t2)        Load word : Set $t1 to contents of effective memory word address
int32_t i_lw(uint32_t *address, int16_t kte){
    uint32_t pos = (*address + kte)/4;
    return MEM[pos];
}
//lb $t1,-100($t2)        Load byte : Set $t1 to sign-extended 8-bit value from effective memory byte address
int32_t i_lb(uint32_t *address, int16_t kte){
    uint32_t pos = (*address + kte)/4;
    uint32_t res = (*address + kte)%4;
    int32_t word = MEM[pos];

    word = word>>8*res;
    int32_t pattern = 0x000000ff;
    int32_t wordanded = (word&pattern);
 
    return wordanded;
}
//lbu $t1,-100($t2)       Load byte unsigned : Set $t1 to zero-extended 8-bit value from effective memory byte address
int32_t i_lbu(uint32_t *address, int16_t kte){
    uint32_t pos = (*address + kte)/4;
    uint32_t res = (*address + kte)%4;
    int32_t word = MEM[pos];

    word = word>>8*res;
    int32_t pattern = 0x000000ff;
    int32_t wordanded = (word&pattern);
 
    return wordanded;
}
//lh $t1,-100($t2)        Load halfword : Set $t1 to sign-extended 16-bit value from effective memory halfword address
int32_t i_lh(uint32_t *address, int16_t kte){
    uint32_t pos = (*address + kte)/4;
    uint32_t res = (*address + kte)%4;
    int32_t word = MEM[pos];
    if (res>1){
        word = word>>16;
    }
    int32_t pattern = 0x0000ffff;
    int32_t wordanded = (word & pattern);

    return wordanded;
}
//lhu $t1,-100($t2)       Load halfword unsigned : Set $t1 to zero-extended 16-bit value from effective memory halfword address
int32_t i_lhu(uint32_t *address, uint16_t kte){
    uint32_t pos = (*address + kte)/4;
    uint32_t res = (*address + kte)%4;
    int32_t word = MEM[pos];
    if (res>1){
        word = word>>16;
    }
    int32_t pattern = 0x0000ffff;
    int32_t wordanded = (word & pattern);

    return wordanded;
}
//lui $t1,100             Load upper immediate : Set high-order 16 bits of $t1 to 16-bit immediate and low-order 16 bits to 0
int32_t i_lui(uint16_t kte){
    return 0xffff0000&(kte<<16);
}
//sw $t1,-100($t2)        Store word : Store contents of $t1 into effective memory word address
void i_sw(uint32_t *address, int16_t kte, int32_t dado){
    int pos = (*address + kte)/4;
    MEM[pos] = dado;
}
//sb $t1,-100($t2)        Store byte : Store the low-order 8 bits of $t1 into the effective memory byte address
void i_sb(uint32_t *address, int16_t kte, int32_t dado){
    int pos = (*address + kte)/4;
    int res = (*address + kte)%4;
    if (res==1){
        int32_t dado32bits = dado;
        dado32bits = dado32bits<<8;
        MEM[pos] = MEM[pos]&0xffff00ff; 
        MEM[pos] = MEM[pos]|dado32bits;
    }else if(res == 2){
        int32_t dado32bits = dado;
        dado32bits = dado32bits<<16;
        MEM[pos] = MEM[pos]&0xff00ffff; 
        MEM[pos] = MEM[pos]|dado32bits;
    }else if(res == 3){
        int32_t dado32bits = dado;
        dado32bits = dado32bits<<24;
        MEM[pos] = MEM[pos]&0x00ffffff; 
        MEM[pos] = MEM[pos]|dado32bits;        
    }else{
        MEM[pos] = MEM[pos]&0xffffff00;
        MEM[pos] = MEM[pos]|dado;
    }
}
//sh $t1,-100($t2)        Store halfword : Store the low-order 16 bits of $t1 into the effective memory halfword address
void i_sh(uint32_t *address, int16_t kte, int32_t dado){
    int pos = (*address + kte)/4;
    int res = (*address + kte)%4;
    if (res>1){
        int32_t dado32bits = dado;
        dado32bits = dado32bits<<16;
        MEM[pos] = MEM[pos]&0x0000ffff; 
        MEM[pos] = MEM[pos]|dado32bits;
        
    }else{
        MEM[pos] = MEM[pos]&0xffff0000;  
        MEM[pos] = MEM[pos]|dado;
    }
}
int32_t i_addi(int32_t *rs, int16_t imm){
    return *rs+imm;
}

//beq $t1,$t2,label       Branch if equal : Branch to statement at label's address if $t1 and $t2 are equal
void i_beq(int32_t *rs, int32_t *rt, int32_t label){
    if(*rs == *rt){
        PC = PC+label*4;
    }
    return;
}
//addi $t1,$t2,-100       Addition immediate with overflow : set $t1 to ($t2 plus signed 16-bit immediate)

//bne $t1,$t2,label       Branch if not equal : Branch to statement at label's address if $t1 and $t2 are not equal
void i_bne(int32_t *rs, int32_t *rt, int16_t label){
    if(*rs != *rt){
        PC = PC+label*4;
    }
    return;
}
//blez $t1,label          Branch if less than or equal to zero : Branch to statement at label's address if $t1 is less than or equal to zero
void i_blez(int32_t *rs, int16_t label){
    if(*rs <= 0){
        PC = PC+label*4;
    }
    return;
}
//bgtz $t1,label          Branch if greater than zero : Branch to statement at label's address if $t1 is greater than zero
void i_bgtz(int32_t *rs, int16_t label){
    if(*rs > 0){
        PC = PC+label*4;
        //printf("PC:%x\n", PC );
    }
    return;
}
//slti $t1,$t2,-100       Set less than immediate : If $t2 is less than sign-extended 16-bit immediate, then set $t1 to 1 else set $t1 to 0
int32_t i_slti(int32_t *rs, int16_t imm){
    if(*rs < imm){
        return 1;
    }else{
        return 0;
    }    
}
//sltiu $t1,$t2,-100      Set less than immediate unsigned : If $t2 is less than  sign-extended 16-bit immediate using unsigned comparison, then set $t1 to 1 else set $t1 to 0
int32_t i_sltiu(int32_t *rs, int16_t imm){
    if(imm<0){
        return 0;
    }else{
        if((uint32_t)*rs < (uint32_t)imm){
            return 1;
        }else{
            return 0;
            
        }    
    }

}
//andi $t1,$t2,100        Bitwise AND immediate : Set $t1 to bitwise AND of $t2 and zero-extended 16-bit immediate
int32_t i_andi(int32_t *rs, int16_t imm){
    return *rs&imm;
}
//ori $t1,$t2,100         Bitwise OR immediate : Set $t1 to bitwise OR of $t2 and zero-extended 16-bit immediate
int32_t i_ori(int32_t *rs, int16_t imm){
    return *rs|imm;
}
//xori $t1,$t2,100        Bitwise XOR immediate : Set $t1 to bitwise XOR of $t2 and zero-extended 16-bit immediate
int32_t i_xori(int32_t *rs, int16_t imm){
    return *rs^imm;
}
//j target                Jump unconditionally : Jump to statement at target address
void i_j(int32_t label){
    PC = ((PC & 0xf0000000) | (label << 2));
    //printf("PC:%x\n", PC );
    return;
}
//jal target              Jump and link : Set $ra to Program Counter (return address) then jump to statement at target address
void i_jal(int32_t label){
    BREG[ra] = PC; 
    PC = (PC & 0xf0000000) | (label << 2);
    return;
}



//Intrucoes para OPCODE = 0x000000
//add $t1,$t2,$t3         Addition with overflow : set $t1 to ($t2 plus $t3)
int32_t i_add(int32_t *rs, int32_t *rt){
    return *rs + *rt;
}
//sub $t1,$t2,$t3         Subtraction with overflow : set $t1 to ($t2 minus $t3)
int32_t i_sub(int32_t *rs, int32_t *rt){
    return *rs - *rt;
}
//mul $t1,$t2,$t3         Multiplication without overflow  : Set HI to high-order 32 bits, LO and $t1 to low-order 32 bits of the product of $t2 and $t3 (use mfhi to access HI, mflo to access LO)
void i_mult(int32_t *rs, int32_t *rt){
    
    int64_t res = (*rs)*(*rt);
    HI = (0xffffffff00000000&res)>>32;
    LO = 0xffffffff&res;
    return;
}
//div $t1,$t2             Division with overflow : Divide $t1 by $t2 then set LO to quotient and HI to remainder (use mfhi to access HI, mflo to access LO)
void i_div(int32_t *rs, int32_t *rt){
    LO = (*rs)/(*rt);
    LO = (*rs)%(*rt);
    return;
}
//and $t1,$t2,$t3         Bitwise AND : Set $t1 to bitwise AND of $t2 and $t3
int32_t i_and(int32_t *rs, int32_t *rt){
    return *rs&*rt;
}
//or $t1,$t2,$t3          Bitwise OR : Set $t1 to bitwise OR of $t2 and $t3
int32_t i_or(int32_t *rs, int32_t *rt){
    return *rs|*rt;
}
//xor $t1,$t2,$t3         Bitwise XOR (exclusive OR) : Set $t1 to bitwise XOR of $t2 and $t3
int32_t i_xor(int32_t *rs, int32_t *rt){
    return *rs^*rt;
}
//nor $t1,$t2,$t3         Bitwise NOR : Set $t1 to bitwise NOR of $t2 and $t3
int32_t i_nor(int32_t *rs, int32_t *rt){
    return 0xffffffff-(*rs|*rt);
}
//slt $t1,$t2,$t3         Set less than : If $t2 is less than $t3, then set $t1 to 1 else set $t1 to 0
int32_t i_slt(int32_t *rs, int32_t *rt){
    if(*rs < *rt){
        return 1;
    }else{
        return 0;
    }
}
//jr $t1                  Jump register unconditionally : Jump to statement whose address is in $t1
void i_jr(int32_t *rs){
    PC = *rs;
    //printf("PC:%x\n", PC );
    return;
}
//sll $t1,$t2,10          Shift left logical : Set $t1 to result of shifting $t2 left by number of bits specified by immediate
int32_t i_sll(int32_t *rs, uint16_t imm){
    return *rs<<imm;
}
//srl $t1,$t2,10          Shift right logical : Set $t1 to result of shifting $t2 right by number of bits specified by immediate
int32_t i_srl(int32_t *rs, uint16_t imm){
    return *rs>>imm;
}
//sra $t1,$t2,10          Shift right arithmetic : Set $t1 to result of sign-extended shifting $t2 right by number of bits specified by immediate
int32_t i_sra(int32_t *rs, uint16_t imm){
    int32_t mask = 0x80000000;
    return (*rs>>imm)|(*rs&mask);
}
//syscall                 Issue a system call : Execute the system call specified by value in $v0
void i_syscall(){
    if(BREG[v0]==1){
        printf("%d", BREG[a0]);
    }else if(BREG[v0]==4){

        int i=0,j;
        int32_t mem_data = MEM[BREG[a0]/4];
        int32_t res = BREG[a0]%4;
        char c[4];
        c[0] = mem_data&0x000000ff;
        c[1] = (mem_data&0x0000ff00)>>8;
        c[2] = (mem_data&0x00ff0000)>>16;
        c[3] = (mem_data&0xff000000)>>24;
         
        int flag_bzero=0;
        while(1){
            //printf("\na0:%x,%d \n%8x:", BREG[a0],i, mem_data);
            //getchar();
            for(j=res ; j<4 && c[j]!='\0'; j++){
                    
                    printf("%c", c[j]);
                    //getchar();
                    if( ((j+1 == 4 )&& (MEM[(BREG[a0])/4+i+1]&0x000000ff)==0) || c[(j+1)%4]=='\0' ){
                        flag_bzero++;
                        break;
                    }
            }
            if(flag_bzero) break;

            i++;
            mem_data = MEM[(BREG[a0])/4+i];
            res = 0;
            c[0] = mem_data&0x000000ff;
            c[1] = (mem_data&0x0000ff00)>>8;
            c[2] = (mem_data&0x00ff0000)>>16;
            c[3] = (mem_data&0xff000000)>>24;
               
        }

    }
    return;
}
//mfhi $t1                Move from HI register : Set $t1 to contents of HI (see multiply and divide operations)
int32_t i_mfhi(){
    return HI;
}
//mflo $t1                Move from LO register : Set $t1 to contents of LO (see multiply and divide operations)
int32_t i_mflo(){
    return LO;
}