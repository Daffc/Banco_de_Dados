
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "Grafo.h"

#define LINE_SIZE 50



void isolanEscalonamento(FILE *f, long int ini,long int fim){

    char    linha[LINE_SIZE];

    // REDEFINE POSIÇÃO PARA LINHA INICIAL DO ESCALONAMENTO.
    fseek(f, ini, SEEK_SET);

    // PERCORRE TODAS AS LINHAS DO ESCALONAMENTO.
    while(fgets(linha, LINE_SIZE, f) != NULL && (ftell(f) <= fim + 1))
    {
        printf("%s", linha);
    } 
    rewind(f);
    
}

int main(){

    char    linha[LINE_SIZE], 
            *elemento;
    Grafo   grafo;
    int     status;
    int     t_atual;

    


    iniciaGrafo(&grafo);

    int cont_commit = 0;
    
    FILE *copia_stdin = fdopen (dup (fileno (stdin)), "r");

    long int esc_ini, esc_fim;
    esc_ini = 0;

    // RECUPERANDO TODAS AS TRANSIÇÕES PARA CRIAÇÃO DO GRAFO
    while(fgets(linha, LINE_SIZE, stdin) != NULL){
        
        // DESCARTANDO TEMPO
        elemento = strtok(linha," ");

        // RECUPERANDO TRANSIÇÃO
        elemento = strtok(NULL," ");      
        verificaNovoVertice(&grafo, elemento);        

        // RECUPERANDO OPERAÇÃO
        elemento = strtok(NULL," ");

        // VERIFICA SE É UM COMMIT
        if(!strcmp(elemento, "C")){
            cont_commit++;

            // ISOLANDO ESCALONAMENTO ATUAL.
            if(cont_commit == grafo.num_vertices){
                esc_fim = ftell(stdin);
                // TRATANDO DE ESCALONAMENTO ATUAL.
                isolanEscalonamento(copia_stdin, esc_ini, esc_fim);
                esc_ini = esc_fim;
            }
        }
    }

    iniciaMatrizGrafo(&grafo);
    imprimeGrafo(&grafo);


    defineArestaGrafo(&grafo, "1", "2");
    defineArestaGrafo(&grafo, "2", "3");
    defineArestaGrafo(&grafo, "1", "3");
    defineArestaGrafo(&grafo, "3", "4");


    imprimeGrafo(&grafo);

    printf("CICLO: %d\n", buscaCiclo(&grafo));

}