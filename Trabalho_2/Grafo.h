
typedef struct identificador {
    char id[20];
} Identificador;

typedef struct grafo {
    int num_vertices;
    Identificador *identificadores;
    int arestas;
    int *m_adjacencia;
} Grafo;



void iniciaGrafo(Grafo *g){
    g -> num_vertices = 0;
    g -> arestas = 0;
}




// INICILAIZA MATRIZ DE ADJACENCIA DE GRAFO.
void iniciaMatrizGrafo(Grafo *g){
    int i, j;

    g -> m_adjacencia = malloc(g->num_vertices * g ->num_vertices * sizeof(int));
    
    for(i = 0; i < g->num_vertices; i++)
        for(j = 0; j < g->num_vertices; j++)
            g -> m_adjacencia[i * g->num_vertices + j] = 0;
}

// DEFINE NOVA ARESTA EM GRFO PARA num_vertices "v1" e "v2".
void defineArestaGrafo(Grafo *g, char *v1, char *v2){
    int i, linha, coluna;

    
    for(i = 0; i < g->num_vertices; i++)
    {
        if(!strcmp(v1, g->identificadores[i].id))
            linha = i;
        if(!strcmp(v2, g->identificadores[i].id))
            coluna = i;
    }
    
    g->m_adjacencia[(linha *g->num_vertices) + coluna] = 1;
    g->arestas++;
}

void verificaNovoVertice(Grafo *g, char *entrada){
    int i;

    for(i = 0; i < g->num_vertices; i++)
        if(!strcmp(g->identificadores[i].id, entrada))
            return;
    
    g->num_vertices ++;  

    if (g->num_vertices  == 1)
        g -> identificadores = malloc(sizeof(Identificador));  
    else
        g->identificadores = realloc(g->identificadores, g->num_vertices * sizeof(Identificador));
    
    
    strcpy(g->identificadores[i].id, entrada);     
}

// EXECUTA BUSCA EM PROFUNDIDADE PARA "vertice" E VERIFICA SE EXISTE CICLO (RETORNA 1 PARA CICLO, 0 PARA NENHUM CICLO).
int buscaProfundidadeCiclo(Grafo *g, int vertice,int visitados[], int pilhaRetorno[]){
    int i;

    // MARCANDO VISITA
    visitados[vertice] = 1; 
    pilhaRetorno[vertice] = 1;  

    for(i = 0; i < g->num_vertices; i++){
        
        // VERIFICA SE EXISTE ARCO DE "vertice" PARA "i";
        if(g->m_adjacencia[(vertice * g->num_vertices) + i]){

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
        visitados[g->num_vertices],
        pilhaRetorno[g->num_vertices];

    // ZERA VETOR DE VISITADOS E "PILHA" DE VETORES.
    for(j = 0; j < g->num_vertices; j++){
        visitados[j] = 0;
        pilhaRetorno[j] = 0;
    }

    // PARA TODOS OS VERTICES DO GRAFO, EXECUTAR BUSCA EM PROFUNDIDADE, VERIFICANDO CICLOS.
    for(i = 0; i < g->num_vertices; i++){
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
    printf("\tNUM_VERTICES: %d\n", g->num_vertices);
    printf("\tIDENTIFICADORES: %d\n", g->num_vertices);
    for(i = 0; i < g->num_vertices; i++){
        printf("\t\t%d - %s\n", i, g->identificadores[i].id);
    }
    
    printf("\tARESTAS: %d\n", g->arestas);

    for(i = 0; i < g->num_vertices; i++){
        printf("\t\t");
        for(j = 0; j < g->num_vertices; j++)
             printf("%d ", g->m_adjacencia[i * g->num_vertices + j]);
        printf("\n");
    }
}

// LIBERA MATRIZ DE ADJACENCIA DE GRAFO E LISTA DE IDENTIFICADORES.
void liberaGrafo(Grafo *g){
    free(g->m_adjacencia);
    free(g->identificadores);
}