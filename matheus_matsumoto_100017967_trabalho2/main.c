/*
 *  OAC - Trabalho 2 - Simulador MIPS - 1/2015
 *  Matheus Yamamoto Matsumoto 10/0017967
 *
 *  Compilador gcc version 4.9.2 20150304
 *
 *  comando de compilacao:
 *      gcc main.c funcoes.c isa.c -std=c99 -o simuladorMIPS
 *
 *  comando de execucao:
 *      ./simuladorMIPS
 *
 *  Sistema Operacional: 
 *      ArchLinux 64-bit
 *
 *  
 *  IDE: 
 *      GNOME Terminal 3.16.0
 *      Sublime Text 2 v 2.0.2 
 *
 */

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

int main(){

    
    mem_mount("code.bin", "data.bin");

    int opcao = 0;
    char fmt;
    int imem, fmem;
    while(1){
        printf("Qual execucao deseja realizar?\n1-RUN\n2-STEP\n3-Mostrar Registradores\n4-Mostrar Memoria\n5-Sair\n");
        scanf("%d",&opcao);
        printf("\n\nSaida do programa:\n");
        //if(!( FLAG_RUN && FLAG_STEP)){
         //   opcao=5;
          //  printf("Execucao Terminada!\n");
        //}
        switch(opcao){
            case 1:
                run();
                printf("\n");
                break;
            case 2:
                step();
                printf("\n");
                break;
            case 3:
                

                printf("Em qual formato deseja? 'h' para base16 'd' para base10\n");
                getchar();
                scanf("%c",&fmt);
                dump_reg(fmt);
                printf("\n");
                break;
            case 4:

                printf("De qual posicao ateh qual posicao deseja?(0-8192)\n");
                scanf("%d",&imem);
                scanf("%d",&fmem);
                getchar();
                printf("Em qual formato deseja? 'h' para base16 'd' para base10\n");
                scanf("%c",&fmt);

                dump_mem(imem,fmem,fmt);
                printf("\n");
                break;
            case 5:
                return 0;
            default:
                printf("Opcao invalida!\n");

        }
        printf("\n");
    }

    return 0;
}