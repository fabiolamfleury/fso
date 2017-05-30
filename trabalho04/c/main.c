#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char const *argv[]) {
  void* handle = dlopen("./libseno.so",RTLD_LAZY);
  if(!handle)
  {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }
  char *error;

  if(argc > 2){
    double numero = 0;
    sscanf(argv[2], "%lf", &numero);

    if (argv[1][1] == 's') {
      double (*resposta)(double) = dlsym (handle, "seno");
        if((error = dlerror()) != NULL)
        {
          fprintf(stderr,"%s\n", error);
          exit(1);
        } else {
          printf("\nseno(%s) = %lf\n", argv[2], (resposta)(numero));
          dlclose(handle);
        }

    } else if (argv[1][1] == 'a') {
        double (*resposta2)(double) = dlsym (handle, "arc_seno");
        if((error = dlerror()) != NULL)
        {
          fprintf(stderr,"%s\n", error);
          exit(1);
        } else {
          double resultado = (resposta2)(numero);
          printf("\narcseno(%s) = %lf\n", argv[2],resultado);
          dlclose(handle);
        }
    } else {
      printf("Você deve digitar s ou a seguido de um numero");
    }
  }
  else{
    printf("Você deve especificar se quer calcular seno ou arcseno, e o valor de entrada.");
  }
  return 0;
}
