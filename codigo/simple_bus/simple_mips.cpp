#include <iostream>
#include <fstream>
#include <string>

#include "systemc.h"
#include "simple_mips.h"

int BREG[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned int PC;
int RI;
int HI;
int LO;



unsigned int opcode,rs,rt,rd,shamnt,funct,k16,k26;

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
    MTHI=0x11,  MTLO=0x13,  SE_SEH_SEB=0x1F
}; 

enum FUNCT {   
    ADD=0x20,   ADDU=0x21,  SUB=0x22,   MULT=0x18,   DIV=0x1A,     AND=0x24,  
    OR=0x25,    XOR=0x26,   NOR=0x27,   SLT=0x2A,       JR=0x08,  SUBU=0x23,
    SLL=0x00,   SRL=0x02,   SRA=0x03,   SYSCALL=0x0c,   MFHI=0x10, MFLO=0x12,
  
};



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
        //cout << "PC!!!" << dec <<PC << endl;
        //cout << sc_time_stamp() << " Fetch: "<< hex << RI << endl;
        
        // Escreve na fila
        IfId.write(RI);

    }
}



void simple_mips::decode(){
    bool flagEx = false;
    wait();
    while (true){

        

        if (IfId.nb_read(RI)) {
            cout << sc_time_stamp() << " Decode: "<< hex << RI << endl;
           flagEx = true;
        }

        unsigned int funct_mask = 0x3f;//111111
        funct = (unsigned int)RI&funct_mask;

        unsigned int shamnt_shift=6;
        unsigned int shamnt_mask = 0x7c0;//11111000000
        shamnt = (unsigned int)(RI&shamnt_mask)>>shamnt_shift;
        

        unsigned int rd_shift=11;
        unsigned int rd_mask = 0xf800;//1111100000000000
        rd = (unsigned int)(RI&rd_mask)>>rd_shift;

        k16 = (unsigned int)(funct|(shamnt<<shamnt_shift)|(rd<<rd_shift) );
        //printf("%d  %d\n", shamt, shamt_shift);

        unsigned int rt_shift=16;
        unsigned int rt_mask = 0x1f0000;//111110000000000000000
        rt = (unsigned int)(RI&rt_mask)>>rt_shift;
        
        unsigned int rs_shift=21;
        unsigned int rs_mask = 0x3e00000;//11111000000000000000000000
        rs = (unsigned int)(RI&rs_mask)>>rs_shift;

        k26 = (unsigned int)k16|(rt<<rt_shift)|(rs<<rs_shift);
        
        unsigned int opcode_shift=26;
        opcode = (unsigned int)RI>>opcode_shift;

        if(flagEx)  dec_ex.notify();
        wait();
    }

}



void simple_mips::execute(){
    wait();
    int mask = 0x80000000;
    long int res;
    while(true){
        wait(dec_ex);

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
                        res = (BREG[rs])*(BREG[rt]);
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
                        }else{
                            BREG[rd] = ((BREG[rt] << (32-shamnt)) || (BREG[rt]>>shamnt));
                        }
                        break;
                        
                    case SRA:
                        BREG[rd] = ((BREG[rt] >> shamnt)| (BREG[rt] & mask));
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
                break;
            case LW:
        
                //BREG[rt] = i_lw(&BREG[rs], k16);

                bus_port->read(m_unique_priority+1, &BREG[rt],  m_data_address+(BREG[rs] + k16)/4, m_lock);
                while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                            (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
                    wait();
                if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
                    sb_fprintf(stdout, "%g %s : ERROR cannot read from %x\n",
                sc_time_stamp(), name(), (BREG[rs] + k16)/4);

                break;
            case SW:
        
                //i_sw(&BREG[rs], k16, BREG[rt]);
                    bus_port->write(m_unique_priority+2,&BREG[rt], m_data_address+(BREG[rs] + k16)/4, m_lock);
                    while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                           (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
                        wait();
                    if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
                        sb_fprintf(stdout, "%g %s : ERROR cannot write to %x\n",
                                   sc_simulation_time(), name(), (BREG[rs] + k16)/4);
        
                break;
            case BEQ:
            
                if(BREG[rs]== BREG[rt]){
                    PC = PC+k16*4+m_inst_address;
                }

                break;
            case BNE:
                if(BREG[rs]!= BREG[rt]){
                    PC = PC+k16*4+m_inst_address;
                }
                break;          
            case BLTZ:
                if(BREG[rs] < 0){
                    PC = PC+k16*4+m_inst_address;
                }                
                break;      
            case BGEZ:
                 if(BREG[rs] >= 0){
                    PC = PC+k16*4+m_inst_address;
                  }   
                break;  
            case ADDI:
                BREG[rt] = BREG[rs]+ k16;
                break;
            case ADDIU:
                BREG[rt] = BREG[rs] + k16;
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
                PC = ((PC & 0xf0000000) | (k26 << 2))+m_inst_address;
                break;
            case JAL:
                  BREG[ra] = PC; 
                  PC = (PC & 0xf0000000) | (k26 << 2)+m_inst_address;
                break;
            case MUL:
                BREG[rd]= (BREG[rs] *BREG[rt]);
            case SE_SEH_SEB:
                cout << " falta implementar ";
            default:
                printf("Instrucao nao implementada!\n");
                break;
        }
        //for(int i=0; i<32 ; i++) cout << dec << i << ": " << BREG[i]<<endl;

        wait();
        }
        
}

