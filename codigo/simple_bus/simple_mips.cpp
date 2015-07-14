#include <iostream>
#include <fstream>
#include <string>

#include "systemc.h"
#include "simple_mips.h"
#include "isa.h"

void simple_mips::fetch(){
    wait(mem_init);
    pipeline_sigs instr;
    int RI;
    PC = m_inst_address;

    wait(); // ... for the next rising clock edge
    while (true){

/*        bus_port->read(m_unique_priority, &RI, PC, m_lock);
        while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                    (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
            wait();
        if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
            sb_fprintf(stdout, "%g %s : ERROR cannot read from %x\n",
        sc_time_stamp(), name(), PC);*/
        data_init_mem[PC/4];

        
        
        PC+=4; // next word (byte addressing)
        if (PC > (m_inst_address+0x80)) {
            PC = m_inst_address;
        }
        
        cout << sc_time_stamp() << " Fetch: " << RI << endl;
        
        // Escreve na fila
        IfId.write(RI);

    }
}



void simple_mips::decode(){
    wait(mem_init);

    pipeline_sigs instr;
    int RI;
    wait();
    while (true){

        

        if (IfId.nb_read(RI)) {
            cout << sc_time_stamp() << " Decode: " << RI << endl;
        } else {
            std::cout << sc_time_stamp() << " Decode: Fila vazia! " << std::endl;
        }

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



void simple_mips::init_mem_file(){
    std::string line;
    int dado;
    ifstream datafile ("data.hex");
    int addr = 0;
    if (datafile.is_open()){
        while ( getline (datafile,line) ){
            
            dado = strtol(line.c_str(), NULL, 1nstnstnst6);
            //cout <<"222 " << dado << '\n';
            data_init_mem[addr] = dado;
            addr+=1;

        }
        datafile.close();
    }else 
        cout << "Unable to open file";

    addr=0;
    ifstream textfile ("text.hex");
    if (textfile.is_open()){
        while ( getline (textfile,line) ){
            dado = strtol(line.c_str(), NULL, 16);
            //cout <<"222 " << dado << '\n';
            text_init_mem[addr] = dado;
            addr+=1;
        }
        textfile.close();
    }else 
        cout << "Unable to open file";


    
}

void simple_mips::init_mem(){
    int mydata;
    int cnt = 0;
    unsigned int addr = m_data_address;

    wait(); // ... for the next rising clock edge
    while (true)
    {

        mydata = data_init_mem[cnt];

        bus_port->write(m_unique_priority, &mydata, addr, m_lock);
        while ((bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
               (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
            wait();
        if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
            sb_fprintf(stdout, "%g %s : ERROR cannot write to %x\n",
                       sc_simulation_time(), name(), addr);
        addr += 4;
        cnt++;
        
        if( cnt == 30) break;

    }
    mem_init.notify();
}