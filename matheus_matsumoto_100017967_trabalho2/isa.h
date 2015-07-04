/*
 * isa.h
 * 
 * Prototipo de funcoes MIPS
 *
 *
*/

enum OPCODES{
    EXT=0x00,   LW=0x23,    LB=0x20,    LBU=0x24,  
    LH=0x21,    LHU=0x25,   LUI=0x0F,   SW=0x2B,
    SB=0x28,    SH=0x29,    BEQ=0x04,   BNE=0x05,  
    BLEZ=0x06,  BGTZ=0x07,  ADDI=0x08,  SLTI=0x0A, 
    SLTIU=0x0B, ANDI=0x0C,  ORI=0x0D,   XORI=0x0E, 
    J=0x02,     JAL=0x03,   ADDIU=0x09
}; 

enum FUNCT {   
    ADD=0x20,   SUB=0x22,   MULT=0x18,   DIV=0x1A,       AND=0x24,  
    OR=0x25,    XOR=0x26,   NOR=0x27,   SLT=0x2A,       JR=0x08,
    SLL=0x00,   SRL=0x02,   SRA=0x03,   SYSCALL=0x0c,   MFHI=0x10, MFLO=0x12
};
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//Instrucoes 

//lw $t1,-100($t2)        Load word : Set $t1 to contents of effective memory word address
int32_t i_lw(uint32_t *address, int16_t kte);
//lb $t1,-100($t2)        Load byte : Set $t1 to sign-extended 8-bit value from effective memory byte address
int32_t i_lb(uint32_t *address, int16_t kte);
//lbu $t1,-100($t2)       Load byte unsigned : Set $t1 to zero-extended 8-bit value from effective memory byte address
int32_t i_lbu(uint32_t *address, int16_t kte);
//lh $t1,-100($t2)        Load halfword : Set $t1 to sign-extended 16-bit value from effective memory halfword address
int32_t i_lh(uint32_t *address, int16_t kte);
//lhu $t1,-100($t2)       Load halfword unsigned : Set $t1 to zero-extended 16-bit value from effective memory halfword address
int32_t i_lhu(uint32_t *address, uint16_t kte);
//lui $t1,100             Load upper immediate : Set high-order 16 bits of $t1 to 16-bit immediate and low-order 16 bits to 0
int32_t i_lui(uint16_t kte);
//sw $t1,-100($t2)        Store word : Store contents of $t1 into effective memory word address
void i_sw(uint32_t *address, int16_t kte, int32_t dado);
//sb $t1,-100($t2)        Store byte : Store the low-order 8 bits of $t1 into the effective memory byte address
void i_sb(uint32_t *address, int16_t kte, int32_t dado);
//sh $t1,-100($t2)        Store halfword : Store the low-order 16 bits of $t1 into the effective memory halfword address
void i_sh(uint32_t *address, int16_t kte, int32_t dado);
//beq $t1,$t2,label       Branch if equal : Branch to statement at label's address if $t1 and $t2 are equal
void i_beq(int32_t *rs, int32_t *rt, int32_t label);
//bne $t1,$t2,label       Branch if not equal : Branch to statement at label's address if $t1 and $t2 are not equal
void i_bne(int32_t *rs, int32_t *rt, int16_t label);
//blez $t1,label          Branch if less than or equal to zero : Branch to statement at label's address if $t1 is less than or equal to zero
void i_blez(int32_t *rs, int16_t label);
//bgtz $t1,label          Branch if greater than zero : Branch to statement at label's address if $t1 is greater than zero
void i_bgtz(int32_t *rs, int16_t label);
//addi $t1,$t2,-100       Addition immediate with overflow : set $t1 to ($t2 plus signed 16-bit immediate)
int32_t i_addi(int32_t *rs, int16_t imm);
//slti $t1,$t2,-100       Set less than immediate : If $t2 is less than sign-extended 16-bit immediate, then set $t1 to 1 else set $t1 to 0
int32_t i_slti(int32_t *rs, int16_t imm);
//sltiu $t1,$t2,-100      Set less than immediate unsigned : If $t2 is less than  sign-extended 16-bit immediate using unsigned comparison, then set $t1 to 1 else set $t1 to 0
int32_t i_sltiu(int32_t *rs, int16_t imm);
//andi $t1,$t2,100        Bitwise AND immediate : Set $t1 to bitwise AND of $t2 and zero-extended 16-bit immediate
int32_t i_andi(int32_t *rs, int16_t imm);
//ori $t1,$t2,100         Bitwise OR immediate : Set $t1 to bitwise OR of $t2 and zero-extended 16-bit immediate
int32_t i_ori(int32_t *rs, int16_t imm);
//xori $t1,$t2,100        Bitwise XOR immediate : Set $t1 to bitwise XOR of $t2 and zero-extended 16-bit immediate
int32_t i_xori(int32_t *rs, int16_t imm);
//j target                Jump unconditionally : Jump to statement at target address
void i_j(int32_t label);
//jal target              Jump and link : Set $ra to Program Counter (return address) then jump to statement at target address
void i_jal(int32_t label);



//Intrucoes para OPCODE = 0x000000
//add $t1,$t2,$t3         Addition with overflow : set $t1 to ($t2 plus $t3)
int32_t i_add(int32_t *rs, int32_t *rt);
//sub $t1,$t2,$t3         Subtraction with overflow : set $t1 to ($t2 minus $t3)
int32_t i_sub(int32_t *rs, int32_t *rt);
//mul $t1,$t2,$t3         Multiplication without overflow  : Set HI to high-order 32 bits, LO and $t1 to low-order 32 bits of the product of $t2 and $t3 (use mfhi to access HI, mflo to access LO)
void i_mult(int32_t *rs, int32_t *rt);
//div $t1,$t2             Division with overflow : Divide $t1 by $t2 then set LO to quotient and HI to remainder (use mfhi to access HI, mflo to access LO)
void i_div(int32_t *rs, int32_t *rt);
//and $t1,$t2,$t3         Bitwise AND : Set $t1 to bitwise AND of $t2 and $t3
int32_t i_and(int32_t *rs, int32_t *rt);
//or $t1,$t2,$t3          Bitwise OR : Set $t1 to bitwise OR of $t2 and $t3
int32_t i_or(int32_t *rs, int32_t *rt);
//xor $t1,$t2,$t3         Bitwise XOR (exclusive OR) : Set $t1 to bitwise XOR of $t2 and $t3
int32_t i_xor(int32_t *rs, int32_t *rt);
//nor $t1,$t2,$t3         Bitwise NOR : Set $t1 to bitwise NOR of $t2 and $t3
int32_t i_nor(int32_t *rs, int32_t *rt);
//slt $t1,$t2,$t3         Set less than : If $t2 is less than $t3, then set $t1 to 1 else set $t1 to 0
int32_t i_slt(int32_t *rs, int32_t *rt);
//jr $t1                  Jump register unconditionally : Jump to statement whose address is in $t1
void i_jr(int32_t *rs);
//sll $t1,$t2,10          Shift left logical : Set $t1 to result of shifting $t2 left by number of bits specified by immediate
int32_t i_sll(int32_t *rs, uint16_t imm);
//srl $t1,$t2,10          Shift right logical : Set $t1 to result of shifting $t2 right by number of bits specified by immediate
int32_t i_srl(int32_t *rs, uint16_t imm);
//sra $t1,$t2,10          Shift right arithmetic : Set $t1 to result of sign-extended shifting $t2 right by number of bits specified by immediate
int32_t i_sra(int32_t *rs, uint16_t imm);
//syscall                 Issue a system call : Execute the system call specified by value in $v0
void i_syscall();
//mfhi $t1                Move from HI register : Set $t1 to contents of HI (see multiply and divide operations)
int32_t i_mfhi();
//mflo $t1                Move from LO register : Set $t1 to contents of LO (see multiply and divide operations)
int32_t i_mflo();