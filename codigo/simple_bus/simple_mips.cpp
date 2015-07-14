#include <iostream>
#include <fstream>
#include <string>

#include "systemc.h"
#include "simple_mips.h"

unsigned int BREG[32];
unsigned int PC;
int RI;
int HI;
int LO;

unsigned int opcode,rs,rt,rd,shamnt,funct,k16,k26;


void simple_mips::fetch(){

    PC = m_inst_address;

    wait(); // ... for the next rising clock edge
    while (true){

        bus_port->read(m_unique_priority, &RI, PC, m_lock);
        while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                    (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
            wait();
        if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
            sb_fprintf(stdout, "%g %s : ERROR cannot read from %x\n",
        sc_time_stamp(), name(), PC);
 
        
        PC+=4; // next word (byte addressing)
        if (PC > (m_inst_address+0x80)) {
            PC = m_inst_address;
        }
        
        cout << sc_time_stamp() << " Fetch: "<< hex << RI << endl;
        
        // Escreve na fila
        IfId.write(RI);

    }
}



void simple_mips::decode(){

    pipeline_sigs instr;

    wait();
    while (true){

        

        if (IfId.nb_read(RI)) {
            cout << sc_time_stamp() << " Decode: "<< hex << RI << endl;
        } else {
            std::cout << sc_time_stamp() << " Decode: Fila vazia! " << std::endl;
        }

        unsigned int funct_mask = 0x3f;//111111
        funct = RI&funct_mask;

        unsigned int shamnt_shift=6;
        unsigned int shamnt_mask = 0x7c0;//11111000000
        shamnt = (RI&shamnt_mask)>>shamnt_shift;
        

        unsigned int rd_shift=11;
        unsigned int rd_mask = 0xf800;//1111100000000000
        rd = (RI&rd_mask)>>rd_shift;

        k16 = (funct|(shamnt<<shamnt_shift)|(rd<<rd_shift) );
        //printf("%d  %d\n", shamt, shamt_shift);

        unsigned int rt_shift=16;
        unsigned int rt_mask = 0x1f0000;//111110000000000000000
        rt = (RI&rt_mask)>>rt_shift;
        
        unsigned int rs_shift=21;
        unsigned int rs_mask = 0x3e00000;//11111000000000000000000000
        rs = (RI&rs_mask)>>rs_shift;

        k26 = k16|(rt<<rt_shift)|(rs<<rs_shift);
        
        unsigned int opcode_shift=26;
        opcode = RI>>opcode_shift;



        wait();
    }

}



void simple_mips::execute(){

    wait();
    while(true){

        switch(opcode){

            case EXT:
                switch(funct){
                    case ADD:
                        BREG[rd] = (BREG[rs] + BREG[rt]);
                        break;
                    case ADDU:
                        BREG[rd] = (BREG[rs] + BREG[rt]);
                        break;
                    case SUB:
                        BREG[rd] = (BREG[rs] - BREG[rt]);
                        break;
                    case SUBU:
                        BREG[rd] = (BREG[rs] - BREG[rt]);
                        break;
                    case MULT:
			long res = (BREG[rs])*(BREG[rt]);
			HI = (0xffffffff00000000&res)>>32;
			LO = 0xffffffff&res;
                        break;
                    case DIV:
			HI = (BREG[rs])/(BREG[rt]);
    			LO = (BREG[rs])%(BREG[rt]);
                        break;
                    case AND:
                        BREG[rd] = (BREG[rs] & BREG[rt]);
                        break;
                    case OR:
                        BREG[rd] = (BREG[rs] | BREG[rt]);
                        break;
                    case XOR:
                        BREG[rd] = (BREG[rs] ^ BREG[rt]);
                        break;
                    case NOR:
                        BREG[rd] = 0xffffffff-(BREG[rs] | BREG[rt]);
                        break;
                    case SLT:
                        if(BREG[rs]< BREG[rt]){
				BREG[rd] =1;
			}			
			else{
				BREG[rd]=0;
			}
                        break;
                    case JR:
                        PC=BREG[rs];
                        break;
                    case SLL:
                        BREG[rd] = (BREG[rt] << shamnt);
                        break;
                    case SRL:
			if(BREG[rs]==0){
	                        BREG[rd] = (BREG[rt] >> shamnt);
			}
			else{
				BREG[rd] = ((BREG[rt] << (32-shamnt)) || (BREG[rt]>>shamnt));
                        break;
                    case SRA:
			int mask = 0x80000000;
                        BREG[rd] = ((BREG[rt] >> shamnt)| (BREG[rt] & mask));
                        break;
                    case SYSCALL:
                        i_syscall();
                        break;
                    case MFHI:
                        BREG[rd] = HI;
                        break;
                    case MFLO:
                        BREG[rd] = LO;
                        break;
                    case MTHI:
                        HI = BREG[rs];
                        break;
                    case MTLO:
                        LO = BREG[rs];
                        break;
            }

            case LW:
		/*unsigned int aux= ((unsigned int) BREG[rt]);
                //BREG[rt] = i_lw(&BREG[rs], k16);
                bus_port->read(m_unique_priority,&aux, (BREG[rs] + k16)/4, m_lock);
                while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                            (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
                    wait();
                if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
                    sb_fprintf(stdout, "%g %s : ERROR cannot read from %x\n",
                sc_time_stamp(), name(), (BREG[rs] + k16)/4);
		*/
                break;
            case SW:
		/*
                //i_sw(&BREG[rs], k16, BREG[rt]);
                    bus_port->write(m_unique_priority, &((unsigned int)BREG[rt]), (BREG[rs] + k16)/4, m_lock);
                    while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                           (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
                        wait();
                    if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
                        sb_fprintf(stdout, "%g %s : ERROR cannot write to %x\n",
                                   sc_simulation_time(), name(), (BREG[rs] + k16)/4);
		*/
                break;
            case BEQ:
                if(BREG[rs]== BREG[rt]){
			PC = PC+k16*4;
		}
                break;
            case BNE:
		if(BREG[rs]!= BREG[rt]){
			PC = PC+k16*4;
		}
                break;          
            case BLTZ:
                if(BREG[rs] < 0){
		        PC = PC+k16*4;
		}                
		break;      
            case BGEZ:
                 if(BREG[rs] >= 0){
		        PC = PC+k16*4;
		}   
                break;  
            case ADDI:
                BREG[rt] = BREG[rs]+ k16;
                break;
            case ADDIU:
                BREG[rt] = BREG[rs] + k16);
                break;      
            case SLTI:
		if(BREG[rs]< k16){
			BREG[rt] = 1;
		}
		else{
			BREG[rt]=0;
		}
               
                break; 
            case SLTIU:
		if(k16 <0){
			BREG[rt]=0;
		}
		else{
			if(BREG[rs]< k16){
				BREG[rt] = 1;
			}
			else{
				BREG[rt]=0;
			}
		}
                break; 
            case ANDI:
                BREG[rt] = (BREG[rs] & k16);
                break;  
            case ORI:
                BREG[rt] = (BREG[rs] | k16);
                break;
            case XORI:
                BREG[rt] = (BREG[rs] ^ k16);
                break; 
            case J:
		PC = ((PC & 0xf0000000) | (k26 << 2));
                break;
            case JAL:
		BREG[ra] = PC; 
    		PC = (PC & 0xf0000000) | (k26 << 2);
                break;
            case MUL:
                BREG[rd]= (BREG[rs] *BREG[rt]);
            case SE:
		if(shamnt==00000000000000000000000000010000){
			if(((BREG[rt] <<24)>>31)==1){
				return (BREG[rt] || 0xFFFF0000);
			}
			else {
				return (BREG[rt] || 0x00000000);
			}
		}
		else{	
			if(((BREG[rt] <<16)>>31)==1){
				return (BREG[rt] || 0xFFFF0000);
			}
			else {
				return (BREG[rt] || 0x00000000);
			}
		}
		
                default:
                    printf("Instrucao nao implementada!");
                    break;
        }
        wait();
    }

}
