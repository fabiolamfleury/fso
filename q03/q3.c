#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Using Shell Sort to put the vector on ascending order
void ShellSort(int * number_vector, int vector_size) {
  int gap = vector_size/2, counter, second_counter, aux;

  while(gap > 0) {
    //Going through the second half of the vector
    for(counter = gap; counter < vector_size; counter++) {
        aux = number_vector[counter];
        second_counter = counter;
        //Enter this only if the second_counter is greater or equal to the gap, and if the number on the first part of the vector is greater than on the second part
        while(second_counter >= gap && number_vector[second_counter - gap] > aux) {
          number_vector[second_counter] = number_vector[second_counter - gap];
          second_counter = second_counter - gap;
        }
        number_vector[second_counter] = aux;
    }
    //Makes the gap longer, to make sure that the while will end
    gap = gap/2;
  }
}

//Print the number in descending order
void descendingOrder(int * number_vector, int vector_size) {
  int counter;

  for(counter = vector_size -1; counter >= 0; counter++)
    printf("%d ", number_vector[counter]);

  printf("\n");
}

void AscendingOrder(int * number_vector, int vector_size){
  int counter;

  for(counter = 0; counter < vector_size; counter++)
    printf("%d ", number_vector[counter]);

  printf("\n");
}

int main (int argc, char const *argv[]) {
  int read_number, * number_vector, vector_size;

  //Allocing vector with size one
  number_vector = (int *) malloc(sizeof(int));
  vector_size = 0;

  //Check if it's a valid number and if it is the function realloc the vector to fit the new number
  do{
    scanf("%d", &read_number);
    if(read_number > 0){
      number_vector = (int *) realloc(number_vector, (vector_size + 1) * sizeof(int));
      number_vector[vector_size++] = read_number;
    }
  } while(read_number != -1);

  //Calls the function to ordenate the vector
  ShellSort(number_vector, vector_size);

  //Check if the user passed an argument on the exectuion of the program
  if(argc > 1){
    //Check the argument passed on the execution of the program
    if(strcmp(argv[1], "-r") == 0)
      descendingOrder(number_vector, vector_size);
    else
      AscendingOrder(number_vector, vector_size);
  }
  else{
    AscendingOrder(number_vector, vector_size);
  }

  return 0;
}
