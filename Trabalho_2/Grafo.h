typedef struct grafo {
    int vertices;
    int arestas;
    int *m_adjacencia;
} Grafo;

void iniciaGrafo(Grafo *g){
    g -> vertices = 0;
    g -> arestas = 0;
}

// INICILAIZA MATRIZ DE ADJACENCIA DE GRAFO.
void iniciaMatrizGrafo(Grafo *g){
    int i, j;

    g -> m_adjacencia = malloc(g->vertices * g ->vertices * sizeof(int));
    
    for(i = 0; i < g->vertices; i++)
        for(j = 0; j < g->vertices; j++)
            g -> m_adjacencia[i * g->vertices + j] = 0;
}

// DEFINE NOVA ARESTA EM GRFO PARA VERTICES "v1" e "v2".
void defineArestaGrafo(Grafo *g, int v1, int v2){
    g->m_adjacencia[((v1-1) *g->vertices) + (v2-1)] = 1;
    g->arestas++;
}

// EXECUTA BUSCA EM PROFUNDIDADE PARA "vertice" E VERIFICA SE EXISTE CICLO (RETORNA 1 PARA CICLO, 0 PARA NENHUM CICLO).
int buscaProfundidadeCiclo(Grafo *g, int vertice,int visitados[], int pilhaRetorno[]){
    int i;

    // MARCANDO VISITA
    visitados[vertice] = 1; 
    pilhaRetorno[vertice] = 1;  

    for(i = 0; i < g->vertices; i++){
        
        // VERIFICA SE EXISTE ARCO DE "vertice" PARA "i";
        if(g->m_adjacencia[(vertice * g->vertices) + i]){

            // VERIFICA SE NÃO FOI VISITADO
            if(visitados[i] == 0 && buscaProfundidadeCiclo(g, i,visitados, pilhaRetorno)){
                return 1;
            }
            else  
                if(pilhaRetorno[i])
                    return 1;
        }
    }
    pilhaRetorno[vertice] = 0;
    return 0;
}

// BUSCA POR CICLO EM GRAFO.
int buscaCiclo(Grafo *g){
    int i,
        j,
        visitados[g->vertices],
        pilhaRetorno[g->vertices];

    // ZERA VETOR DE VISITADOS E "PILHA" DE VETORES.
    for(j = 0; j < g->vertices; j++){
        visitados[j] = 0;
        pilhaRetorno[j] = 0;
    }

    // PARA TODOS OS VERTICES DO GRAFO, EXECUTAR BUSCA EM PROFUNDIDADE, VERIFICANDO CICLOS.
    for(i = 0; i < g->vertices; i++){
        if(buscaProfundidadeCiclo(g, i, visitados, pilhaRetorno))
            return 1;
    }

    return 0;
}


/*----------------------------------------------------------*/
/*--------------------     DEBUG     -----------------------*/
/*----------------------------------------------------------*/

// VARIÁVEIS E MATRIZ ADJACENCIA DE GRAFO.
void imprimeGrafo(Grafo *g){
    int i, j;

    printf("GRAFO:\n");
    printf("\tVERTICES: %d\n", g->vertices);
    printf("\tARESTAS: %d\n", g->arestas);

    for(i = 0; i < g->vertices; i++){
        printf("\t");
        for(j = 0; j < g->vertices; j++)
             printf("%d ", g->m_adjacencia[i * g->vertices + j]);
        printf("\n");
    }
}

// LIBERA MATRIZ DE ADJACENCIA DE GRAFO.
void liberaGrafo(Grafo *g){
    free(g->m_adjacencia);
}