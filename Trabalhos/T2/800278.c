/**
 * Nome: Matheus Goulart Ranzani
 * RA: 800278
 * Curso: Ciência da Computação
*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct grafo* Grafo;
struct grafo {
    float** M; // Matriz de Adjacência
    int V; // Número de Vértices
    int A; // Número de Arestas
};

Grafo inicializaGrafo(int V) {
    int i, j;

    Grafo G = malloc(sizeof * G);
    G->V = V;
    G->A = 0;
    G->M = malloc(V * sizeof(float*));

    for (i = 0; i < V; i++) {
        G->M[i] = malloc(V * sizeof(float));
    }

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            G->M[i][j] = 0;
        }
    }

    return G;
}

void insere_aresta(Grafo G, int v, int w, float distancia) {
        G->M[v][w] = distancia;
        G->M[w][v] = distancia;

        G->A++;
}

void insere_tubulacao(Grafo G, int v, int w) {
    G->M[v][w] = 1;
    G->M[w][v] = 1;
}

int distancia_minima(float *distancias, int *visitados, int V) {
    float distancia_minima = FLT_MAX;
    int indice_minima = -1;

    for (int i = 0; i < V; i++) {
        if (visitados[i] == 0 && distancias[i] <= distancia_minima) {
            distancia_minima = distancias[i];
            indice_minima = i;
        }
    }

    return indice_minima;
}

void dijkstra(Grafo G, int origem, float *distancias) {
    int *visitados = malloc(G->V * sizeof(int));

    for (int i = 0; i < G->V; i++) {
        distancias[i] = FLT_MAX;
        visitados[i] = 0;
    }

    distancias[origem] = 0;

    for (int i = 0; i < G->V - 1; i++) {
        int u = distancia_minima(distancias, visitados, G->V);
        visitados[u] = 1;

        for (int v = 0; v < G->V; v++) {
            if (G->M[u][v] && visitados[v] == 0 && distancias[u] != FLT_MAX && distancias[u] + G->M[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + G->M[u][v];
            }
        }
    }
}

int main() {
    int M, E, N, C;

    /**
     * M = número de salas
     * E = número de ligações entre as salas por meio de corredores
     * N = número de ligações entre as salar por meio de tubulações
     * C = número de consultas
    */

    scanf("%d %d %d %d", &M, &E, &N, &C);

    Grafo grafo_salas = inicializaGrafo(M);
    Grafo grafo_salas_impostor = inicializaGrafo(M);

    for (int i = 0; i < E; i++) {
        int U, V;
        float D;

        scanf("%d %d %f", &U, &V, &D);
        insere_aresta(grafo_salas, U, V, D);
        insere_aresta(grafo_salas_impostor, U, V, D);
    }

    for (int i = 0; i < N; i++) {
        int U, V;

        scanf("%d %d", &U, &V);

        if (grafo_salas_impostor->M[U][V] == 0) {
            insere_tubulacao(grafo_salas_impostor, U, V);
        } else if (grafo_salas_impostor->M[U][V] != 0 && grafo_salas_impostor->M[U][V] > 1) {
            insere_tubulacao(grafo_salas_impostor, U, V);
        }
    }

    for (int i = 0; i < C; i++) {
        int consulta;

        scanf("%d", &consulta);

        float *distancias = calloc(M - 1, sizeof(float));
        float *distancias_impostor = calloc(M - 1, sizeof(float));

        dijkstra(grafo_salas, consulta, distancias);
        dijkstra(grafo_salas_impostor, consulta, distancias_impostor);

        // Para evitar problemas na comparação de números do tipo float
        distancias[0] = roundf(distancias[0] * 100) / 100;
        distancias_impostor[0] = roundf(distancias_impostor[0] * 100) / 100;

        distancias_impostor[0] >= distancias[0] ? printf("victory\n") : printf("defeat\n");
    }

    return 0;
}
