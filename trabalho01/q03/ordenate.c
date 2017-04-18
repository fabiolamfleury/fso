#include "ordenate.h"
#include <stdio.h>

//Print the number in descending order
void DescendingOrder(int * number_vector, int vector_size) {
  int counter;
  if(vector_size > 0){
    printf("Saida decrescente: \n");
  }
  for(counter = vector_size -1; counter >= 0; counter--){
    printf("%d ", number_vector[counter]);
  }

  printf("\n");
}

//Print the number in ascending order
void AscendingOrder(int * number_vector, int vector_size){
  int counter;

  if(vector_size > 0){
    printf("Saida crescente: \n");
  }
  for(counter = 0; counter < vector_size; counter++)
    printf("%d ", number_vector[counter]);

  printf("\n");
}
