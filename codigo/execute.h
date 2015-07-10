#include "systemc.h"

SC_MODULE(execute){

    //entradas
	sc_in<bool> clock, RegWriteE, MemtoRegE, MemWriteE,ALUControlE, ALUSrcE;
	sc_in<bool> RegDstE, ShiftD;
	sc_in_rv<32> RD1,RD2, SignImmE;
	sc_in_rv<5> RsE, RtE, RdE;
    //saidas
	sc_out_rv<32> AluOutE, WriteDataE;
	sc_out<bool> RegWriteEs, MemtoRegEs, MemWriteEs;
	sc_out_rv<5> WriteRegE;
    //funcao
    void proc();


    SC_CTOR(execute){

    }

}



int sc_main(){

    printf("Hello World!");

    return 0;
}
