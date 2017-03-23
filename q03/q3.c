#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const *argv[]) {
  int readNumber, * numberVector, vectorSize, counter;

  numberVector = (int *) malloc(sizeof(int));
  vectorSize = 0;

  do{
    scanf("%d", &readNumber);
    if(readNumber == -1){
      for(counter = 0; counter < vectorSize; counter++){
        printf("%d ", numberVector[counter]);
      }
    }
    else {
      numberVector = (int *) realloc(numberVector, (vectorSize + 1) * sizeof(int));
      numberVector[vectorSize++] = readNumber;
    }
  } while(readNumber != -1);


  return 0;
}
