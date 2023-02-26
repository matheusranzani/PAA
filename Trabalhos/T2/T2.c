/**
 * Nome: Matheus Goulart Ranzani
 * RA: 800278
 * Curso: Ciência da Computação
*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

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
            fprintf(saida, "%3d ", p->rotulo);
        }
        fprintf(saida, "-1\n");
    }

    fprintf(saida, "\n");

    for (int i = 0; i < G->V; i++) {
        Noh* p = G->lista[i];
        fprintf(saida, "Lista de adjacência do vértice %d\n", i);
        while (p != NULL) {
            fprintf(saida, "-> Vértice %d (peso: %.2f)", p->rotulo, p->distancia);
            p = p->proximo;
        }
        fprintf(saida, "\n");
    }
}

int distancia_minima(float *distancias, int *visitados, int N) {
    float minima = FLT_MAX;
    int indice_minima = 0;

    for (int i = 0; i < N; i++) {
        if (!visitados[i] && distancias[i] <= minima) {
            minima = distancias[i];
            indice_minima = i;
        }
    }

    return indice_minima;
}

void printa_distancias(float *distancias, int N) {
    printf("Vértice\t\tDistância da origem\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t\t%.1f\n", i, distancias[i]);
    }
}

void printa_predecessores(int *predecessores, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", predecessores[i]);
    }
    printf("\n");
}

void dijkstra(Grafo *G, int origem, int *tubulacoes, int M) {
    int N = G->V;
    float distancias[N];
    int visitados[N];
    int predecessores[N];

    for (int i = 0; i < N; i++) {
        distancias[i] = FLT_MAX;
        visitados[i] = 0;
        predecessores[i] = -1;
    }

    distancias[origem] = .0;

    for (int i = 0; i < N - 1; i++) {
        int v = distancia_minima(distancias, visitados, N);
        visitados[v] = 1;

        Noh *p = G->lista[v];

        while (p != NULL) {
            int w = p->rotulo;

            if (!visitados[w] && distancias[v] != FLT_MAX && (distancias[v] + p->distancia) < distancias[w]) {
                distancias[w] = distancias[v] + p->distancia;
                predecessores[w] = v;
            }

            p = p->proximo;
        }
    }

    int *caminho = (int *)malloc(sizeof(int));
    int i = 0;
    int auxiliar = -1;

    while (predecessores[auxiliar] != -1) {
        auxiliar = predecessores[auxiliar];

        if (i == 0) {
            auxiliar = 0;
        }

        if (predecessores[auxiliar] != -1) {
            caminho = (int *)realloc(caminho, sizeof(int) * (i + 1));
            caminho[i++] = predecessores[auxiliar];
        }
    }

    // printa_distancias(distancias, N);
    // printa_predecessores(predecessores, N);

    int tamanho_caminho = i;
    // printa_predecessores(caminho, tamanho_caminho);

    float distancia_impostor = FLT_MAX;

    for (int i = tamanho_caminho - 1; i >= 0; i--) {
        for (int j = 0; j < M; j++) {
            if (caminho[i] == tubulacoes[j]) {
                // printf("c=%d t=%d i=%d j=%d\n", caminho[i], tubulacoes[j], i, j);
                if (j % 2 == 0) {
                    int eh_caminho = 0;
                    for (int k = 0; k < tamanho_caminho; k++) {
                        if (caminho[k] != 0 && caminho[k] == tubulacoes[j + 1]) eh_caminho = 1;
                    }
                    if (eh_caminho && abs(distancias[tubulacoes[j]] - distancias[tubulacoes[j + 1]]) >= 1 && distancia_impostor > distancias[0] - distancias[tubulacoes[j + 1]] + 1) {
                        distancia_impostor = distancias[0] - distancias[tubulacoes[j + 1]] + 1;
                        // printf("\nc=%.1f d=%.1f\n", distancias[tubulacoes[j + 1]], distancia_impostor);
                    }
                } else {
                    int eh_caminho = 0;
                    for (int k = 0; k < tamanho_caminho; k++) {
                        if (caminho[k] != 0 && caminho[k] == tubulacoes[j - 1]) eh_caminho = 1;
                    }
                    if (eh_caminho && abs(distancias[tubulacoes[j]] - distancias[tubulacoes[j - 1]]) >= 1 && distancia_impostor > distancias[0] - distancias[tubulacoes[j - 1]] + 1) {
                        distancia_impostor = distancias[0] - distancias[tubulacoes[j - 1]] + 1;
                        // printf("\nc=%.1f d=%.1f\n", distancias[tubulacoes[j - 1]], distancia_impostor);
                    }
                }
            }
        }
    }

    if (distancia_impostor == FLT_MAX) distancia_impostor = distancias[0];

    // printf("%.1f %.1f\n", distancia_impostor, distancias[0]);
    distancia_impostor >= distancias[0] ? printf("victory\n") : printf("defeat\n");
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

    Grafo *grafo_salas = inicializa(M);
    int *tubulacoes = (int *)calloc(N * 2, sizeof(int));
    // Grafo *grafo_tubulacoes = inicializa(N);

    for (int i = 0; i < E; i++) {
        int U, V;
        float D;

        scanf("%d %d %f", &U, &V, &D);
        insere_aresta(grafo_salas, U, V, D);
    }

    int j = 0;
    for (int i = 0; i < N; i++) {
        int U, V;

        scanf("%d %d", &U, &V);

        tubulacoes[j++] = U;
        tubulacoes[j++] = V;

        // insere_aresta(grafo_tubulacoes, U, V, 0);
    }

    for (int i = 0; i < 2 * N; i++) {
        // printf("%d ", tubulacoes[i]);
    }

    // printf("\n");

    for (int i = 0; i < C; i++) {
        int consulta;

        scanf("%d", &consulta);

        dijkstra(grafo_salas, consulta, tubulacoes, 2 * N);
        // printf("--------------------------------------------------------\n");
    }

    imprime_grafo(grafo_salas, arquivo1);
    // imprime_grafo(tubulacoes, arquivo2);

    fclose(arquivo1);
    fclose(arquivo2);

    return 0;
}
