/*
    TODO:
        REMOVER TODO O CONTRÚDO ENTRE 
        "!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "Grafo.h"

#define LINE_SIZE 50

typedef struct comando{
    int ordem;
    char transicao[5];
    char operacao;
    char atributo;
    
} Comando;

int verificaVisao(Identificador sequencia_trans[], int num_trans, int ordem[]){
    int i;

    
    for(i = 0; i < num_trans; i++)
    {
        for (i = 0; i < num_trans; i++){
            printf("%s ", sequencia_trans[ordem[i]].id);
        }
        printf("\n");
    }
    
}


void permutaTransicoes(Identificador sequencia_trans[], int num_trans){
    int i, 
        j;
    int ordenador[num_trans];
    int ordem[num_trans];
    int tmp;

    //=========================================
    //========== VERIFICAÇÃO POR VISÃO ========
    //=========================================
    for(i = 0; i < num_trans; i++)
    {
        ordenador[i] = 0;
        ordem[i] = i;
    }

    verificaVisao(sequencia_trans, num_trans, ordem);

    i = 0;
    while(i < num_trans){
        if (ordenador[i] < i){
            if(i%2 == 0){
                tmp = ordem[0];
                ordem[0] = ordem[i];
                ordem[i] = tmp;
            }
            else{
                tmp = ordem[ordenador[i]];
                ordem[ordenador[i]] = ordem[i];
                ordem[i] = tmp;
            }
            verificaVisao(sequencia_trans, num_trans, ordem);
            ordenador[i] += 1;
            i = 0;
        }
        else{
            ordenador[i] = 0;
            i += 1;
        }
    }
}



void isolanEscalonamento(FILE *f, long int posi_ini, int linhas_esc){

    char    linha[LINE_SIZE];
    int     cont_linha,
            i,
            j;
    Grafo   grafo;

    Comando comandos[linhas_esc];

    // REDEFINE POSIÇÃO PARA LINHA INICIAL DO ESCALONAMENTO.
    fseek(f, posi_ini, SEEK_SET);
    iniciaGrafo(&grafo);

    
    cont_linha = 0;
    // PERCORRE TODAS AS LINHAS DO ESCALONAMENTO.
    while(fgets(linha, LINE_SIZE, f) != NULL && (cont_linha < linhas_esc))
    {
        /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
        // printf("%s", linha);
        /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/

        // DESCARTANDO TEMPO
        comandos[cont_linha].ordem = atoi(strtok(linha," "));

        // RECUPERANDO  TRANSIÇÃO
        strcpy(comandos[cont_linha].transicao, strtok(NULL," "));

        // RECUPERANDO OPERAÇÃO
        comandos[cont_linha].operacao = * strtok(NULL," ");

        // RECUPERANDO ATRIBUTO
        comandos[cont_linha].atributo = * strtok(NULL," ");;
        
        // VERIFICA SE "transicao" JÁ CONSTA COMO UM DOS VÉRTICES DO GRAFO, ADICIONANDO CASO NÃO CONSTE.
        verificaNovoVertice(&grafo, comandos[cont_linha].transicao);
        cont_linha++;                
    } 

    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
    // for(int i = 0; i < linhas_esc; i++)
    // {
    //     printf("ORDEM: %d, TRANSIÇÃO: %s, OPERAÇÃO: %c, ATRIBUTO: %c\n", comandos[i].ordem, comandos[i].transicao, comandos[i].operacao, comandos[i].atributo);
    // }
    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
    iniciaMatrizGrafo(&grafo);
    
    //  PERCORRE TODAS AS LINHAS DO ESCALONAMENTO.
    for(i = 0; i < linhas_esc; i++)
    {
        for(j = i + 1; j < linhas_esc; j++){
            //   VERIFICA SE OPERAÇÕ DE Ti E DE Tj SÃO SOBRE O MESMO ATRIBUTO.
            if(comandos[i].atributo == comandos[j].atributo){
                // VERIFICA SE Ti != Tj
                if(strcmp(comandos[i].transicao, comandos[j].transicao))
                    // EFETUA VERIFICAÇOES QUANTO ORDEM DE LEITURA E ESCRITA (ALGORITMO DE CONFLITO POR SERIALIDADE)
                    if( (comandos[j].operacao == 'R') && (comandos[i].operacao == 'W') || 
                        (comandos[j].operacao == 'W') && (comandos[i].operacao == 'R') ||
                        (comandos[j].operacao == 'W') && (comandos[i].operacao == 'W')){
                    
                            defineArcoGrafo(&grafo, comandos[i].transicao, comandos[j].transicao);
                            /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                            // printf("%s -> %s\n", comandos[i].transicao, comandos[j].transicao);
                            /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                    }              
            }
        }
    }

    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
    imprimeGrafo(&grafo);    
    printf("CICLO: %d\n", buscaCiclo(&grafo));
    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/

    //==============================================================================
    //========================== VERIFICAÇÃO POR VISÃO =============================
    //==============================================================================

    // DEFINE VETORES PARA GERAÇÃO DE VISÕES A PARTIR DA QUANTIDADE DE TRANSAÇÕES DO ESCALONAMENTO.
    permutaTransicoes(grafo.identificadores, grafo.num_vertices);

    liberaGrafo(&grafo);
    
}

int main(){

    char    linha[LINE_SIZE], 
            *elemento;    
    
    Identificador transicoes[100];
    
    int i, 
        num_trans,
        ordem_esc,
        linhas_esc;

    // DUPLICANDO PONTEIRO PARA STDIN.
    FILE *copia_stdin = fdopen (dup (fileno (stdin)), "r");

    int cont_commit = 0;
    long int esc_ini;

    esc_ini = 0;
    num_trans = 0;
    ordem_esc = 1;
    linhas_esc = 0;

    // RECUPERANDO TODAS AS TRANSIÇÕES PARA CRIAÇÃO DO GRAFO
    while(fgets(linha, LINE_SIZE, stdin) != NULL){
        
        //  CONTABILIZA UMA NOVA LINHA DO ESCALONAMENTO ATUAL.
        linhas_esc ++;
        // DESCARTANDO TEMPO
        elemento = strtok(linha," ");

        // DESCARTANTO TRANSIÇÃO
        elemento = strtok(NULL," ");    
        
        // VERIFICA SE TRANSIÇÂO ATUAL JÁ FOI CONTABILIZADA NO ESCALONAMENTO ATUAL
        for(i = 0; i < num_trans; i++)
        {
            if (!strcmp(transicoes[i].id, elemento))
                break;
        }
        // CASO NÃO TENHA SIDO, CONTABILIZÁ-LA.
        if(i == num_trans){
            strcpy(transicoes[num_trans].id, elemento);
            num_trans ++;
        }

        // for(i = 0; i < num_trans; i++)
        // {
        //     printf("%s ", transicoes[i].id);
        // }
        // printf("\n");
          

        // DESCARTANDO OPERAÇÃO
        elemento = strtok(NULL," ");

        // VERIFICA SE OPERAÇÃO É UM COMMIT
        if(!strcmp(elemento, "C")){
            cont_commit++;

            //  VERIFICA SE NÚMERO DE COMITIS É IGUAL AO NUMERO DE TRANSIÇÕES (FIM DO ESCALONAMENTO).
            if(cont_commit == num_trans){
                // TRATANDO DE ESCALONAMENTO ATUAL.
                isolanEscalonamento(copia_stdin, esc_ini, linhas_esc);
                esc_ini = ftell(stdin);

                num_trans = 0;
                cont_commit = 0;
                linhas_esc = 0;
            }
        }
    }
}