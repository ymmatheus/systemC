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
                        BREG[rd] = i_add(&BREG[rs], &BREG[rt]);
                        break;
                    case ADDU:
                        BREG[rd] = i_add(&BREG[rs], &BREG[rt]);
                        break;
                    case SUB:
                        BREG[rd] = i_sub(&BREG[rs], &BREG[rt]);
                        break;
                    case SUBU:
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
                        BREG[rd] = i_sll(&BREG[rt], shamnt);
                        break;
                    case SRL:
                        BREG[rd] = i_srl(&BREG[rt], shamnt,&BREG[rs]);
                        break;
                    case SRA:
                        BREG[rd] = i_sra(&BREG[rt], shamnt);
                        break;
                    case SYSCALL:
                        i_syscall();
                        break;
                    case MFHI:
                        BREG[rd] = i_mfhi();
                        break;
                    case MFLO:
                        BREG[rd] = i_mflo();
                        break;
                    case MTHI:
                        HI = i_mthi(&BREG[rs]);
                        break;
                    case MTLO:
                        LO = i_mtlo(&BREG[rs]);
                        break;
            }

            case LW:
                //BREG[rt] = i_lw(&BREG[rs], k16);
                bus_port->read(m_unique_priority, &BREG[rt], (BREG[rs] + k16)/4, m_lock);
                while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                            (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
                    wait();
                if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
                    sb_fprintf(stdout, "%g %s : ERROR cannot read from %x\n",
                sc_time_stamp(), name(), (BREG[rs] + k16)/4);

                break;
            case SW:
                //i_sw(&BREG[rs], k16, BREG[rt]);
                    bus_port->write(m_unique_priority, &BREG[rt], (BREG[rs] + k16)/4, m_lock);
                    while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                           (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
                        wait();
                    if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
                        sb_fprintf(stdout, "%g %s : ERROR cannot write to %x\n",
                                   sc_simulation_time(), name(), (BREG[rs] + k16)/4);

                break;
            case BEQ:
                i_beq(&BREG[rs], &BREG[rt], k16);
                break;
            case BNE:
                i_bne(&BREG[rs], &BREG[rt], k16);
                break;          
            case BLTZ:
                i_bltz(&BREG[rs], k16);
                break;      
            case BGEZ:
                i_bgez(&BREG[rs], k16);
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
            case MUL:
                BREG[rd]= i_mul(&BREG[rs], &BREG[rt]);
            case SE:
                BREG[rd]= i_se(&BREG[rt], shamnt);
                default:
                    printf("Instrucao nao implementada!");
                    break;
        }

    }
}