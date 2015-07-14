/*
 *      Implementacao das instrucoes MIPS
 */

#include <stdio.h>
#include <stdlib.h>
#include "simple_mips.h"

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
//blez $t1,label          Branch if less than zero : Branch to statement at label's address if $t1 is less than or equal to zero
void i_bltz(int32_t *rs, int16_t label){
    if(*rs < 0){
        PC = PC+label*4;
    }
    return;
}
//bgtz $t1,label          Branch if greater or equal than zero : Branch to statement at label's address if $t1 is greater than zero
void i_bgez(int32_t *rs, int16_t label){
    if(*rs >= 0){
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
int32_t i_sll(int32_t *rt, int32_t shamnt){
    return *rt<<shamnt;
}
//srl $t1,$t2,10          Shift right logical : Set $t1 to result of shifting $t2 right by number of bits specified by immediate
int32_t i_srl(int32_t *rt, int32_t shamnt, int32_t *rs){
    if(*rs==0){
	return *rt>>shamnt;
    }
    else{
	return ((*rt<<(32 - shamnt)) || (*rt >> shamnt));
    }
}
//sra $t1,$t2,10          Shift right arithmetic : Set $t1 to result of sign-extended shifting $t2 right by number of bits specified by immediate
int32_t i_sra(int32_t *rt, int32_t shamnt){
    int32_t mask = 0x80000000;
    return (*rt>>shamnt)|(*rt&mask);
}

//mfhi $t1                Move from HI register : Set $t1 to contents of HI (see multiply and divide operations)
int32_t i_mfhi(){
    return HI;
}
//mflo $t1                Move from LO register : Set $t1 to contents of LO (see multiply and divide operations)
int32_t i_mflo(){
    return LO;
}

// mul $t1,$t2,$t3
int32_t i_mul(int32_t *rs, int32_t *rt){
	return (*rs)*(*rt);
}

int32_t i_mthi(int32_t *rs){
	return *rs;
}
int32_t i_mtlo(int32_t *rs){
	return *rs;
}
int32_t i_se(int32_t *rt, int32_t shamnt){

	if(shamnt==00000000000000000000000000010000){
		if(((*rt <<24)>>31)==1){
			return (*rt || 0xFFFF0000);
		}
		else {
			return (*rt || 0x00000000);
		}
	}
	else{	
		if(((*rt <<16)>>31)==1){
			return (*rt || 0xFFFF0000);
		}
		else {
			return (*rt || 0x00000000);
		}
	}
}

