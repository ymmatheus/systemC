#include "systemc.h"

SC_MODULE(decode){

    //entradas
	sc_in<bool> clock;
	sc_rv_in<32> InstD, PCPlus4D;
	sc_rv_out<32> PCBranchD;
	sc_rv_out<16> SignImmD;
	sc_rv_out<5> RsD, RtD, RdD;
	sc_rv_out<32> Rd1,Rd2;
    //Sinais do Controle do Decode
	sc_out<bool> RegWriteD, MemtoRegD, MemWriteD, AluControlD, ALUSrcD;
	sc_out<bool> JumpD, BranchD,BranchND, ShiftD,PCSrcD;
    //saidas

    //funcao
    void proc();


    SC_CTOR(decode){
	SC_METHOD(decodeinst);
	sensitive << clock.pos();
	SC_METHOD(extendeSign);
	sensitive << clock.pos();
	SC_METHOD(somador);
	sensitive << clock.pos();
	SC_METHOD(breg);
	sensitive << clock.pos();

    }

void decodeinst();
void extendeSign();
void somador();
void breg();

}