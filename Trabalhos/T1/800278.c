#include <stdio.h>

// Função que troca os elementos do vetor
void troca(float *a, float *b) {
    float auxiliar = *a;
    *a = *b;
    *b = auxiliar;
}

// Função que separa o vetor em duas partes ordenadas em relação a um pivô e retorna a posição desse pivô
int separa(float *vetor, int esquerda, int direita) {
    int i, j;
    i = j = esquerda;
    float pivo = vetor[direita]; // Pivô é o último elemento do vetor

    for (; j < direita; j++) {
        if (vetor[j] >= pivo) {
            troca(&vetor[i++], &vetor[j]);
        }
    }

    troca(&vetor[i], &vetor[direita]);

    return i;
}

// Função recursiva Quick Sort para ordenção de complexidade O(nlog)
void quick_sort(float *vetor, int esquerda, int direita) {
    if (esquerda < direita) {
        int i = separa(vetor, esquerda, direita);
        quick_sort(vetor, esquerda, i - 1);
        quick_sort(vetor, i + 1, direita);
    }
}

int main() {
    int N;
    int K;
    int C;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &K, &C);
        float vetor[C];

        for (int j = 0; j < C; j++) {
            scanf("%f", &vetor[j]);
        }

        // Ordena o vetor em ordem decrescente
        quick_sort(vetor, 0, C - 1);

        // Como o vetor é iniciado em 0, a K-ésima maior nota será na realidade a posição anterior (K- 1)
        printf("%.2f\n", vetor[K - 1]);
    }

    return 0;
}
