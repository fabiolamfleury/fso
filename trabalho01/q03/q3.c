#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenate.h"
#include "sort.h"

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
      DescendingOrder(number_vector, vector_size);
    else
      AscendingOrder(number_vector, vector_size);
  }
  else{
    AscendingOrder(number_vector, vector_size);
  }

  return 0;
}
