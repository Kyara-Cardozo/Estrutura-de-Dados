#include <stdio.h>
//  troca de  elementos
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;}
  //encontrar a posição
int partition(int array[], int low, int high) {
  //selecionar o elemento mais à direita como pivô
  int pivot = array[high];
  // ponteiro para maior elemento
  int i = (low - 1);
  // percorre cada elemento da matriz e compara com o pivô
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
  // se o elemento menor que o pivô for encontrado troca com o elemento maior apontado por i
      i++;
      // trocar elemento em i com elemento em j
      swap(&array[i], &array[j]);}
  }
  // troque o elemento pivô pelo elemento maior em i
  swap(&array[i + 1], &array[high]);
  //retornar o ponto de partição
  return (i + 1);}
void quickSort(int array[], int low, int high) {
  if (low < high) {
    //encontre o elemento pivô tal que e os elementos menores que o pivô estão à esquerda e os maiores estão à direita
    int pi = partition(array, low, high);
    //chamada recursiva à esquerda do pivô
    quickSort(array, low, pi - 1);
    // chamada recursiva à direita do pivô
    quickSort(array, pi + 1, high);
  }
}
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}
int main() {
  int data[] = {645,122,36,2,5,9};
  int n = sizeof(data) / sizeof(data[0]);
  printf("Array:\n");
  printArray(data, n);
  quickSort(data, 0, n - 1);
  printf("Array ordenado em ordem crescente: \n");
  printArray(data, n);
}
