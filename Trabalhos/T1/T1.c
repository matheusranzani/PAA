#include <stdio.h>

// Função que realiza a ordenação em ordem decrescente do vetor
void merge(float *vetor, int esquerda, int meio, int direita) {
    int i = esquerda;
    int j = meio + 1;
    int k = 0;

    int tamanho_auxiliar = (direita - esquerda) + 1;
    float vetor_auxiliar[tamanho_auxiliar];

    while (i <= meio && j <= direita) {
        if (vetor[i] >= vetor[j]) {
            vetor_auxiliar[k++] = vetor[i++];
        } else {
            vetor_auxiliar[k++] = vetor[j++];
        }
    }

    while (i <= meio) {
        vetor_auxiliar[k++] = vetor[i++];
    }

    while (j <= direita) {
        vetor_auxiliar[k++] = vetor[j++];
    }

    for (i = 0; i < tamanho_auxiliar; i++) {
        vetor[esquerda + i] = vetor_auxiliar[i];
    }
}

// Função recursiva Merge Sort para ordenção de complexidade O(nlog)
void merge_sort(float *vetor, int esquerda, int direita) {
    if (esquerda >= direita) {
        return;
    }

    int meio = (esquerda + direita) / 2;

    merge_sort(vetor, esquerda, meio);
    merge_sort(vetor, meio + 1, direita);
    merge(vetor, esquerda, meio, direita);
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

        merge_sort(vetor, 0, C - 1);

        // Como o vetor é iniciado em 0, a K-ésima maior nota será na realidade a posição anterior (K- 1)
        printf("%.2f\n", vetor[K - 1]);
    }

    return 0;
}
