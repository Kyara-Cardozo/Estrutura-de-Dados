#include <stdio.h>

int buscaSeqRecursiva(int vetor[], int i, int buscado, int size) {
    
    if (i == size)
    {
        return -1;
    } 
    else if (vetor[i] == buscado)
    {
        return i;
    }
    else
    {
        return buscaSeqRecursiva(vetor, i+1, buscado, size);
    }
}

int main(){

    int vetor[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof(vetor) / sizeof(vetor[0]);
    printf("O valor %d esta no índice %d\n", 1, buscaSeqRecursiva(vetor, 0, 1, n));
    printf("O valor %d esta no índice %d\n", 10, buscaSeqRecursiva(vetor, 0, 10, n));
}