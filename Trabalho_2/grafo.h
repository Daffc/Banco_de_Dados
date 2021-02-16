#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct identificador {
    char id[20];
} Identificador;

typedef struct grafo {
    int num_vertices;
    Identificador *identificadores;
    int arcos;
    int *m_adjacencia;
} Grafo;

// INICIA VARIÁVEIS "num_vertices" E "arcos" DE GRAFO.
void iniciaGrafo(Grafo *g);

// INICILAIZA MATRIZ DE ADJACENCIA DE GRAFO.
void iniciaMatrizGrafo(Grafo *g);

// DEFINE NOVA ARCO EM GRFO PARA num_vertices "v1" e "v2".
void defineArcoGrafo(Grafo *g, char *v1, char *v2);

void verificaNovoVertice(Grafo *g, char *entrada);

// EXECUTA BUSCA EM PROFUNDIDADE PARA "vertice" E VERIFICA SE EXISTE CICLO (RETORNA 1 PARA CICLO, 0 PARA NENHUM CICLO).
int buscaProfundidadeCiclo(Grafo *g, int vertice,int visitados[], int pilhaRetorno[]);

// BUSCA POR CICLO EM GRAFO.
int buscaCiclo(Grafo *g);

// LIBERA MATRIZ DE ADJACENCIA DE GRAFO E LISTA DE IDENTIFICADORES.
void liberaGrafo(Grafo *g);

/*----------------------------------------------------------*/
/*--------------------     DEBUG     -----------------------*/
/*----------------------------------------------------------*/

// VARIÁVEIS E MATRIZ ADJACENCIA DE GRAFO.
void imprimeGrafo(Grafo *g);

