/**
 * Nome: Matheus Goulart Ranzani
 * RA: 800278
 * Curso: Ciência da Computação
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct noh Noh;
struct noh {
    int rotulo;
    float distancia;
    Noh *proximo;
};

typedef struct Grafo {
    int V;
    int A;
    Noh **lista;
} Grafo;

Grafo *inicializa(int N) {
    Grafo *G = (Grafo *)malloc(sizeof(Grafo));
    G->V = N;
    G->A = 0;
    G->lista = (Noh **)malloc(N * sizeof(Noh *));

    for (int i = 0; i < N; i++) {
        G->lista[i] = NULL;
    }

    return G;
}

Noh *cria_noh(int v, float distancia) {
    Noh *novo_noh = (Noh *)malloc(sizeof(Noh));
    novo_noh->rotulo = v;
    novo_noh->distancia = distancia;
    novo_noh->proximo = NULL;

    return novo_noh;
}

void insere_aresta(Grafo *G, int v, int w, float distancia) {
    Noh *novo_noh = cria_noh(w, distancia);
    novo_noh->proximo = G->lista[v];
    G->lista[v] = novo_noh;

    novo_noh = cria_noh(v, distancia);
    novo_noh->proximo = G->lista[w];
    G->lista[w] = novo_noh;

    G->A++;
}

void imprime_grafo(Grafo *G, FILE *saida) {
    Noh *p;

    fprintf(saida, "%d %d\n", G->V, G->A);
    for (int i = 0; i < G->V; i++) {
        for (p = G->lista[i]; p != NULL; p = p->proximo) {
            fprintf(saida, "%2d ", p->rotulo);
        }
        fprintf(saida, "-1\n");
    }

    fprintf(saida, "\n");

    for (int i = 0; i < G->V; i++) {
        Noh* current = G->lista[i];
        fprintf(saida, "Lista de adjacência do vértice %d\n", i);
        while (current != NULL) {
            fprintf(saida, "-> Vértice %d (peso: %.2f)", current->rotulo, current->distancia);
            current = current->proximo;
        }
        fprintf(saida, "\n");
    }
}

void dijkstra(Grafo *G, int origem, int *distancias, int *predecessor, int eh_impostor) {
    if (eh_impostor) {

    }
}

int main() {
    FILE *arquivo1 = fopen("grafo1.txt", "w");
    FILE *arquivo2 = fopen("grafo2.txt", "w");
    int M, E, N, C;

    /**
     * M = número de salas
     * E = número de ligações entre as salas por meio de corredores
     * N = número de ligações entre as salar por meio de tubulações
     * C = número de consultas
    */

    scanf("%d %d %d %d", &M, &E, &N, &C);

    Grafo *grafo_salas = inicializa(M + 1);
    Grafo *grafo_tubulacoes = inicializa(N);

    for (int i = 0; i < E; i++) {
        int U, V;
        float D;

        scanf("%d %d %f", &U, &V, &D);
        insere_aresta(grafo_salas, U, V, D);
    }

    for (int i = 0; i < N; i++) {
        int U, V;

        scanf("%d %d", &U, &V);
        insere_aresta(grafo_tubulacoes, U, V, 0);
    }

    for (int i = 0; i < C; i++) {
        int consulta;

        scanf("%d", &consulta);

        // dijkstra();
    }

    imprime_grafo(grafo_salas, arquivo1);
    imprime_grafo(grafo_tubulacoes, arquivo2);

    fclose(arquivo1);
    fclose(arquivo2);

    return 0;
}
