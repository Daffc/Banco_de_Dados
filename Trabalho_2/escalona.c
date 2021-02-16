/*
    TODO:
        REMOVER TODO O CONTRÚDO ENTRE 
        "!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "grafo.h"

#define LINE_SIZE 50

typedef struct comando{
    int ordem;
    char transicao[5];
    char operacao;
    char atributo;
    
} Comando;

void copiaComando(Comando *destino, Comando *origem){
        strcpy(destino->transicao, origem->transicao);
        destino->ordem = origem->ordem;
        destino->operacao = origem->operacao;
        destino->atributo = origem->atributo;   
}

int verificaVisao(Identificador sequencia_trans[], int num_trans, int ordem[], Comando comandos[], int lin_esc){
    int i,
        j,
        x, 
        y,
        ordem_linha,
        cont_atributos = 0;
    Comando visao[lin_esc];

    Comando lista_ultima_escrita_atributo[lin_esc];

    
    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
    // for (i = 0; i < num_trans; i++){
    //     printf("%s ", sequencia_trans[ordem[i]].id);
    // }
    // printf("\n");
    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/

    ordem_linha = 0;
    for(i = 0; i < num_trans; i++)
    {
        for(j = 0; j < lin_esc; j++){
            if(!strcmp(comandos[j].transicao, sequencia_trans[ordem[i]].id)){                
                copiaComando(&visao[ordem_linha], &comandos[j]);
                ordem_linha ++;
            }
        }
    }
    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
    // for(i = 0; i < lin_esc; i++){
    //     printf("\tORDEM: %d, TRANSIÇÃO: %s, OPERAÇÃO: %c, ATRIBUTO: %c\n", visao[i].ordem, visao[i].transicao, visao[i].operacao, visao[i].atributo);
    // }
    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/

    /* 
    VERIFICAÇÃO DE 1ª REGRA: 
        - Para cada r(x) de Ti, se o valor de x lido for escrito por w(x) de Tj, o mesmo deve permanecer para r(x) de Tiem S’.
    */
    Comando aux_1;
    Comando aux_2;
    // PERCORRE "S" EM ORDEM CRESCENTE.
    for(i = 0; i < lin_esc; i++){
        // BUSCA POR OPERAÇÃO DE LEITURA, E ARMAZENA-A EM "aux_1".
        if((comandos[i].operacao == 'R')){
            copiaComando(&aux_1, &comandos[i]);
            
            // PROCURA POR COMANDO NO MESMO "atributo", SOFRENDO O COMANDO 'W' E QUE PERTENÇA A OUTRA "transição".
            for(j = i - 1; j >= 0; j--){
                if(comandos[j].atributo == aux_1.atributo && comandos[j].operacao == 'W' && strcmp(comandos[j].transicao, aux_1.transicao)){
                    copiaComando(&aux_2, &comandos[j]);

                    // PERCORRE "S'" EM BUSCA DE COMANDO aux_1;
                    for(x = 0; x < lin_esc; x++){
                        if(visao[x].ordem == aux_1.ordem){
                            for(y = x - 1; y >= 0; y--){

                                // PROCURA ESCRITA EM "atributo" DE "aux_1" QUE O PRECEDE.
                                if(visao[y].operacao == 'W' && visao[y].atributo == aux_1.atributo){
                                    // VERIFICA SE ESCRITA ENCONTRADA CORRESPONDE A MESMO COMANDO EM "aux_2".
                                    if(visao[y].ordem == aux_2.ordem){
                                        break;
                                    }
                                    else
                                    {
                                        // CASO COMANDO NÃO SEJA CORRESPONDENTE, VISÃO NÃO É EQUIVALENTE.
                                        /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                                        // printf("\t\tIMCOMPATIVEL ESPERADO(%d, %d), ADQUIRIDO(%d, %d):\n", aux_1.ordem, aux_2.ordem, visao[x].ordem, visao[y].ordem);
                                        /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                                        return 0;
                                    }
                                }
                            }

                            // CASO "aux_2" NÃO PRECEDA "aux_1" EM "S'", VISÃO NÃO É VÁLIDA.
                            if( y < 0){
                                /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                                // printf("\t\t\tFIM LOOP:\n");printf("\t\tORDEM: %d, TRANSIÇÃO: %s, OPERAÇÃO: %c, ATRIBUTO: %c\n", aux_1.ordem, aux_1.transicao, aux_1.operacao, aux_1.atributo);
                                /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                                return 0;
                            }
                        }
                    }

                    // CASO ENCONTRE 'W' E QUE PERTENÇA A OUTRA "transição" PRECEDENDO "aux_1"
                    break;
                }
            }
            // CASO 'aux_1' SEJA UMA LEITURA MAS NÃO É PRECEDIDO DE UMA ESCRITA POR OUTRA TRANSAÇÃO
            if(j < 0){
                // PROCURA POR COMANDO NO MESMO "atributo", SOFRENDO O COMANDO 'W' E QUE PERTENÇA A OUTRA "transição".
                // PERCORRE "S'" EM BUSCA DE COMANDO 'aux_1';
                for(x = 0; x < lin_esc; x++){
                    if(visao[x].ordem == aux_1.ordem){                      
                        for(y = x - 1; y >= 0; y--){
                            // PROCURA ESCRITA EM "atributo" POR UMA "transicao" DIFERENTE DE "aux_1" QUE O PRECEDE.
                            if(visao[y].operacao == 'W' && visao[y].atributo == aux_1.atributo ){
                                /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                                // printf("\t\tESCRITA INAPROPRIADA(R: %d,W: %d):\n", aux_1.ordem, visao[y].ordem);
                                /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                                return 0;
                            }
                        }
                    }
                }
            } 
        }
    }  

    /* 
        VERIFICAÇÃO DE 2ª REGRA: 
            - Se o operador wk(y) em Tké a ultima escrita de y em S, então wk(y)em Tkdeve ser a última escrita em S’
    */
    // PREPARA "lista_ultima_escrita_atributo", CONTENDO ULTIMO COMANDO DE ESCRITA PARA CADA "atributo" ENCONTRADO.
    for(i = 0; i < lin_esc; i++)
    {
        if(visao[i].operacao == 'W'){
            for(j = 0; j < cont_atributos; j++)
                if( lista_ultima_escrita_atributo[j].atributo == visao[i].atributo){
                    // CASO ATRIBUTO SEJA ENCONTRADO, ATUALIZA SUA ULTIMA ESCRITA E PARA LAÇO.
                    copiaComando(&lista_ultima_escrita_atributo[j], &visao[i]);                    
                    break;
                }
            if(j >= cont_atributos){
                // CASO NÃO SEJA ENCONTRADO, CRIA-SE NOVA ENTRADA PARA ATRIBUTO.
                copiaComando(&lista_ultima_escrita_atributo[cont_atributos], &visao[i]);
                cont_atributos++;
            }
        }
    }

    // printf("\tLISTA:\n");
    // for(i = 0; i < cont_atributos; i++)
    //     printf("\t\tORDEM: %d, TRANSIÇÃO: %s, OPERAÇÃO: %c, ATRIBUTO: %c\n", lista_ultima_escrita_atributo[i].ordem, lista_ultima_escrita_atributo[i].transicao, lista_ultima_escrita_atributo[i].operacao, lista_ultima_escrita_atributo[i].atributo);
    // printf("\n");

    // PERCORRRE LISTA DE ULTIMO COMANDO DE ESCRITA POR ATRIBUTO.
    for(j = 0; j < cont_atributos; j++){
        // PERCORRE LISTA DE "comandos" DE FORMA REVERSA.
        for(i = lin_esc -1; i >= 0; i--){
            // VERIFICA SE COMANDO "comandos[i]" É UMA ESCRITA E SE O ATRIBUTO É O MESMO DE "lista_ultima_escrita_atributo[j]".
            if(comandos[i].operacao == 'W' && lista_ultima_escrita_atributo[j].atributo == comandos[i].atributo){
                // VERIFICA SE COMANDOS DE ESCRITA É O MESMO DE VISÃO, CASO VERDADEIRO, PROXIMO "lista_ultima_escrita_atributo[j]"
                if(comandos[i].ordem == lista_ultima_escrita_atributo[j].ordem)
                    break;
                else{

                    // CASO FALSE, "lista_ultima_escrita_atributo[j]" É ULTIMA ESCRITA EM "visao" MAS NÃO EM "comados", RETORNAR 0.
                    // printf("\tERRO ESCRITA:\n");
                    // printf("\t\tORDEM: %d, TRANSIÇÃO: %s, OPERAÇÃO: %c, ATRIBUTO: %c\n", comandos[i].ordem, comandos[i].transicao, comandos[i].operacao, comandos[i].atributo);
                    // return 0;
                }
            }
        }
    }

    // CASO PASSE POR TODAS AS VERIFICAÇÕES, VALIDA VISÃO.
    return 1;
}


int verificaVisoes(Identificador sequencia_trans[], int num_trans, Comando comandos[], int lin_esc){
    int i, 
        j;
    int ordenador[num_trans];
    int ordem[num_trans];
    int tmp;
    int resposta;

    // EFETUA PERMUTAÇÕES NA ORDEM DAS TRANSIÇÕES
    for(i = 0; i < num_trans; i++)
    {   
        // SIMULADOR DE RECURSÃO PARA PERMUTAÇÃO HEAP.
        ordenador[i] = 0;
        // LISTA QUE ARMAZENARA ORDEM EM QUE "sequencia_trans" DEVE SER PERMUTADO.
        ordem[i] = i;
    }

    // VERIFICA PRIMEIRA PERMUTAÇÃO (ORDEM ORIGINAL), CASO SEJA UMA VISÃO VALIDA, RETORNA 1.
    if (verificaVisao(sequencia_trans, num_trans, ordem, comandos, lin_esc)){
        return 1;
    }

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
            
            // VERIFICA PERMUTAÇÃO, CASO SEJA UMA VISÃO VALIDA, RETORNA 1.
            if(verificaVisao(sequencia_trans, num_trans, ordem, comandos, lin_esc)){
                return 1;
            }
            ordenador[i] += 1;
            i = 0;
        }
        else{
            ordenador[i] = 0;
            i += 1;
        }
    }

    // CASO NENHUMA PERMUTAÇÃO APRESENTE UMA VISÃO VÁLIDA, RETORNA-SE 0.
    return 0;
}



void isolanEscalonamento(FILE *f, long int posi_ini, int linhas_esc, int ordem_esc){

    char    linha[LINE_SIZE];
    int     cont_linha,
            i,
            j,
            res_ciclo,
            res_visao;
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
                    
                            defineArcoGrafo(&grafo, comandos[j].transicao, comandos[i].transicao);
                            /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                            // printf("%s -> %s\n", comandos[i].transicao, comandos[j].transicao);
                            /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
                    }              
            }
        }
    }

    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/
    // imprimeGrafo(&grafo);    
    /*!!!!!!!!!! REMOVER AO FINAL !!!!!!!!!!!!!!!!*/

    res_ciclo = buscaCiclo(&grafo);

    //==============================================================================
    //========================== VERIFICAÇÃO POR VISÃO =============================
    //==============================================================================

    // DEFINE VETORES PARA GERAÇÃO DE VISÕES A PARTIR DA QUANTIDADE DE TRANSAÇÕES DO ESCALONAMENTO.
    res_visao = verificaVisoes(grafo.identificadores, grafo.num_vertices, comandos, linhas_esc);
    

    // IMPRIMINDO RESULTADO PARA ESCALONAMENTO ATUAL.

    // IMPRIMINDO ORDEM
    printf("%d ", ordem_esc);

    // IMPRIMINDO TRANSIÇÕES
    printf("%s", grafo.identificadores[0].id);
    for(i = 1; i < grafo.num_vertices; i++){
        printf(",%s", grafo.identificadores[i].id);
    }

    // IMPRIMINDO TESTE DE SERIALIDADE
    if(res_ciclo){
        printf(" NS");        
    }
    else{
        printf(" SS");
    }

    // IMPRIMINDO EQUIVALÊNCIA DE VISÃO
    if(res_visao){
        printf(" SV\n");        
    }
    else{
        printf(" NV\n");
    }

    liberaGrafo(&grafo);
    
}

int main(){

    char    linha[LINE_SIZE], 
            *elemento;    
    
    Identificador transicoes[100];
    
    int i, 
        num_trans,
        ordem_esc,
        linhas_esc,
        cont_commit;

    long int esc_ini;

    // DUPLICANDO PONTEIRO PARA STDIN.
    FILE *copia_stdin = fdopen(dup (fileno(stdin)), "r");

    esc_ini = 0;
    num_trans = 0;
    ordem_esc = 1;
    linhas_esc = 0;
    cont_commit = 0;

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

        // DESCARTANDO OPERAÇÃO
        elemento = strtok(NULL," ");

        // VERIFICA SE OPERAÇÃO É UM COMMIT
        if(!strcmp(elemento, "C")){
            cont_commit++;

            //  VERIFICA SE NÚMERO DE COMITIS É IGUAL AO NUMERO DE TRANSIÇÕES (FIM DO ESCALONAMENTO).
            if(cont_commit == num_trans){
                // TRATANDO DE ESCALONAMENTO ATUAL.
                isolanEscalonamento(copia_stdin, esc_ini, linhas_esc, ordem_esc);
                esc_ini = ftell(stdin);

                num_trans = 0;
                cont_commit = 0;
                linhas_esc = 0;
                ordem_esc++;
            }
        }
    }
}