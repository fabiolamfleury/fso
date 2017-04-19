#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "output.h"


void writer(const char* message, long int* times, int i, FILE* stream){
  fprintf(stream, "0:%02ld.%03ld: Mensagem %d do %s", times[0], times[1], i, message);
  fflush(stream);
}

void writing_pipe(int pipe[], long int times[], int i, char *message){
  close (pipe[0]);

  FILE* stream;
  stream = fdopen (pipe[1], "w");
  writer("filho dorminhoco", times, i, stream);
  close (pipe[1]);
}

void reader (FILE* stream){
  char buffer[1024];
  FILE* output = fopen("output.txt", "a");

  while(!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL) {
  	fprintf (output, "0: %s\n", buffer);
  }

  fclose(output);
}


void reading_messages(int pipe[]){
  struct timeval initial_time;
  gettimeofday(&initial_time, NULL);

  while(1){
    writing_file(pipe, initial_time);
  }
}
