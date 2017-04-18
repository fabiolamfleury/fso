#include <stdio.h>

int main(int argc, char const *argv[]) {
  int counter = 0;
  printf("# de parametros: %d\n",argc-1);
  printf("Nome do executavel: %s\n",argv[0]);
  if(argc > 1){
    for(counter = 1; counter < argc; counter++){
      printf("Parametro #%d: %s\n", counter, argv[counter]);
    }
  }
  return 0;
}
