
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

#define LINE_SIZE 50

int main(){

    char    linha[LINE_SIZE], 
            *elemento;
    Grafo   grafo;
    int     status;
    int     t_atual;


    iniciaGrafo(&grafo);

    // RECUPERANDO TODAS AS TRANSIÇÕES PARA CRIAÇÃO DO GRAFO
    while(fgets(linha, LINE_SIZE, stdin) != NULL){
        
        // DESCARTANDO TEMPO
        elemento = strtok(linha," ");

        // RECUPERANDO TRANSIÇÃO
        elemento = strtok(NULL," ");      
        verificaNovoVertice(&grafo, elemento);        
    }

    iniciaMatrizGrafo(&grafo);
    imprimeGrafo(&grafo);

    // REPOSICIONANDO PONTEIRO DE stdin AO INÍCIO.

    // rewind(stdin);
    // // RECUPERANDO TODAS AS TRANSIÇÕES PARA CRIAÇÃO DO GRAFO

    // int v1, v2;
    // FILE p_aux_1, p_aux_2;

    // p_aux_1 = p_aux_2 = stdin;

    // while(fgets(linha, LINE_SIZE, stdin) != NULL){
    //     // DESCARTANDO TEMPO
    //     elemento = strtok(linha," ");
    //     printf("TEMPO: %d\n", atoi(elemento));

    //     // RECUPERANDO TRANSIÇÃO
    //     elemento = strtok(NULL," ");
    //     v1 = atoi(elemento);

    //     // RECUPERANDO OPERAÇÃO
    //     elemento = strtok(NULL," ");
    //     printf("OPERAÇÃO: %s\n", elemento);

    //     if(! strcmpelemento = )
        
    //     // RECUPERANDO ALVO
    //     elemento = strtok(NULL," ");
    //     printf("ALVO: %s\n", elemento);       
        
    // }
    // imprimeGrafo(&grafo);    



    defineArestaGrafo(&grafo, "1", "2");
    defineArestaGrafo(&grafo, "2", "3");
    defineArestaGrafo(&grafo, "1", "3");
    defineArestaGrafo(&grafo, "3", "4");


    imprimeGrafo(&grafo);

    printf("CICLO: %d\n", buscaCiclo(&grafo));

}