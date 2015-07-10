#include <stdio.h>

#ifndef ISA
#include "isa.h"
#define ISA
#endif


#ifndef MIPS
#include "mips.h"
#define MIPS
#endif

#ifndef FUNCOES
#include "funcoes.h"
#define FUNCOES
#endif


int main(int argc, const char * argv[]) {
 
    int8_t b0, b1, b2, b3;
    int16_t h0, h1;
    int32_t w, s0;
 
 //mem[0] = 0x01020304;
 
    s0 = 0;
 
    i_sb((uint32_t *)&s0, 0, 0x04);
    i_sb((uint32_t *)&s0, 1, 0x03);
    i_sb((uint32_t *)&s0, 2, 0x02);
    i_sb((uint32_t *)&s0, 3, 0x01);
 
 //mem[100] = 0x00100020;
 
    s0 = 400;
    i_sh((uint32_t *)&s0, 0, 0x20);
    i_sh((uint32_t *)&s0, 2, 0x10);
 
 //mem[120] = 0x00010001;
 
    i_sw((uint32_t *)&s0, 80, 0xACABADA0);
 
    w = i_lw((uint32_t *)&s0, 80);
 
    s0 = 400;
 
    h0 = i_lh((uint32_t *)&s0, 0);
    h1 = i_lh((uint32_t *)&s0, 2);
 
    s0 = 0;
 
    b0 = i_lb((uint32_t *)&s0, 0);
    b1 = i_lb((uint32_t *)&s0, 1);
    b2 = i_lb((uint32_t *)&s0, 2);
    b3 = i_lb((uint32_t *)&s0, 3);
 
    s0 = 1;
    i_lw((uint32_t *)&s0, 0);
    i_lh((uint32_t *)&s0, 0);
 
 /*cout << "\n\nX=========== Inicio Teste =====X";
 
    cout << "\nByte 0 = " << (int)b0;
    cout << "\nByte 1 = " << (int)b1;
    cout << "\nByte 2 = " << (int)b2;
    cout << "\nByte 3 = " << (int)b3;
 
    cout << "\nShort 0 = " << hex << (int)h0;
    cout << "\nShort 1 = " << hex << (int)h1;
 
    cout << "\nWord = " << hex << w;
 
    cout << endl;
 */
 printf("\n\nX=========== Inicio Teste =====X");

printf("\nByte 0 = %d\n", (int)b0);
printf("\nByte 1 = %d\n", (int)b1);
printf("\nByte 2 = %d\n", (int)b2);
printf("\nByte 3 = %d\n", (int)b3);


printf("\nshort 0 = %x\n", (int)h0);
printf("\nshort 1 = %x\n", (int)h1);

printf("\nWord = %x\n", w);




    return 0;
}