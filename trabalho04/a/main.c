#include <stdio.h>
#include <stdlib.h>
#include "libseno.h"

int main(int argc, char const *argv[]) {
  if(argc > 2){
    double numero = 0;
    sscanf(argv[2], "%lf", &numero);

    if (argv[1][1] == 's') {
      double resposta = seno(numero);
      printf("\nseno(%s) = %lf\n", argv[2],resposta);
    } else if (argv[1][1] == 'a') {
      double resposta = arc_seno(numero);
      printf("\narcseno(%s) = %lf\n", argv[2],resposta);
    } else {
      printf("Você deve digitar s ou a seguido de um numero");
    }
  }

  else{
    printf("Você deve especificar se quer calcular seno ou arcseno, e o valor de entrada.");
  }
  return 0;
}
