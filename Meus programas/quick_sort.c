#include <stdio.h>

void troca(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int separa(int *v, int esq, int dir) {
    int i, j;
    i = j = esq;
    int pivo = v[dir];

    for (; j < dir; j++) {
        if (v[j] <= pivo) {
            troca(&v[i], &v[j]);
            i++;
        }
    }

    troca(&v[i], &v[dir]);

    return i;
}

void quick_sort(int *v, int esq, int dir) {
    int i;

    if (esq < dir) {
        i = separa(v, esq, dir);
        quick_sort(v, esq, i - 1);
        quick_sort(v, i + 1, dir);
    }
}

void printa(int *v, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", v[i]);
    }
}

int main() {
    int v[] = {-11, 7, 9, 9, -4, -2, 7, 13, -12, -6, -6, -13, -8, -15, 8, -2};
    int tam = sizeof(v) / sizeof(v[16]);

    quick_sort(v, 0, tam - 1);

    printa(v, tam);
    printf("\n");

    return 0;
}
