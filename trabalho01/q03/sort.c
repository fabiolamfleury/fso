#include "sort.h"

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
