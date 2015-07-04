/*
 * funcoes.h
 * 
 * principais funcoes utilizadas pelo simulador
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*A função unsigned  int32_t     fetch(uint32_t  pc) lê uma instrução da memória e coloca-
a em ri, atualizando o pc para apontar para a próxima instrução (soma 4).*/
uint32_t fetch(uint32_t pc);
/*Deve extrair todos os campos da instrução:
- opcode: código da operação
- rs: índice do primeiro registrador fonte
- rt: índice do segundo registrador fonte
- rd: índice do registrador destino, que recebe o resultado da operação
- shamnt: quantidade de deslocamento em instruções shift e rotate
- funct: código auxiliar para determinar a instrução a ser executada
- k16: constante de 16 bits, valor imediato em instruções tipo I
- k26: constante de 26 bits, para instruções tipo J*/
void decode();
/*A função void   execute() executa a instrução que foi lida pela função
decodificada por decode()*/
void execute();
/*A função step() executa uma instrução do MIPS:
step() => fecth(), decode(), execute()*/
void step();
/*A função run() executa o programa até encontrar uma chamada de sistema para
encerramento, ou até o pc ultrapassar o limite do segmento de código (4k words).*/
void run();
/*Imprime o conteúdo da memória a partir do endereço start até o endereço end. O
formato pode ser em hexa (‘h’) ou decimal (‘d’).*/
void dump_mem(int start, int end, char format);
/*Imprime o conteúdo dos registradores do MIPS, incluindo o banco de registradores e
os registradores pc, hi e lo. O formato pode ser em hexa (‘h’) ou decimal (‘d’).*/
void dump_reg(char format);
/* Le arquivo com codigo binario do programa e arquivo binario dos dados e insere 
na variavel global memoria*/
void mem_mount(char* filename_text, char* filename_data);