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
  writer(message, times, i, stream);
  close (pipe[1]);
}

void reader (FILE* stream, long int times[]){
  char buffer[1024];
  FILE* output = fopen("output.txt", "a");

  while(!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL) {
  	fprintf (output, "0:%02ld.%03ld: %s\n", times[0], times[1], buffer);
  }

  fclose(output);
}


void reading_messages(int sleepy_pipe[], int active_pipe[]){
  struct timeval initial_time;
  struct timeval end_time;
  long int running_time = -1;
  gettimeofday(&initial_time, NULL);

  close (sleepy_pipe[1]);
  close (active_pipe[1]);

  while(running_time < 10){
    writing_file(active_pipe, initial_time);
    writing_file(sleepy_pipe, initial_time);
    gettimeofday(&end_time, NULL);
    running_time = end_time.tv_sec - initial_time.tv_sec;
  }
}
