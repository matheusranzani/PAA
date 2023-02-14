#include <stdio.h>

void merge(int *v, int esq, int meio, int dir) {
    int i = esq, j = meio + 1, k = 0;

    int aux_tam = dir - esq + 1;
    int w[aux_tam];

    while (i <= meio && j <= dir) {
        if (v[i] <= v[j]) {
            w[k++] = v[i++];
        } else {
            w[k++] = v[j++];
        }
    }

    while (i <= meio) {
        w[k++] = v[i++];
    }

    while (j <= dir) {
        w[k++] = v[j++];
    }

    for (i = 0; i < aux_tam; i++) {
        v[esq + i] = w[i];
    }
}

void merge_sort(int *v, int esq, int dir) {
    if (esq >= dir) { return; }

    int meio = (esq + dir) / 2;

    merge_sort(v, esq, meio);
    merge_sort(v, meio + 1, dir);
    merge(v, esq, meio, dir);
}

void printa(int *v, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", v[i]);
    }
}

int main() {
    int v[16] = {-11, 7, 9, 9, -4, -2, 7, 13, -12, -6, -6, -13, -8, -15, 8, -2};
    int tam = sizeof(v) / sizeof(v[16]);

    merge_sort(v, 0, tam - 1);

    printa(v, tam);
    printf("\n");

    return 0;
}
