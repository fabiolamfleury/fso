#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "output.h"


void writer(const char* message, long int* times, int i, FILE* stream){
  fprintf(stream, "0:%02ld.%03ld: Mensagem %d do %s\n", times[0], times[1], i, message);
  fflush(stream);
}

void reader (FILE* stream, long int times[], struct timeval initial_time){
  char buffer[1024];
  FILE* output = fopen("output.txt", "a");
  struct timeval end_time;

  if(fgets(buffer, sizeof(buffer), stream) != NULL) {
    gettimeofday(&end_time, NULL);
    times = print_time_stamp(initial_time, end_time, times);
  	fprintf (output, "0:%02ld.%03ld: %s\n", times[0], times[1], buffer);
  }

  fclose(output);
}


void reading_messages(int sleepy_pipe[], int active_pipe[]){
  struct timeval initial_time;
  struct timeval end_time;
  gettimeofday(&initial_time, NULL);

  close (active_pipe[1]);
  close (sleepy_pipe[1]);

  while(1){
    writing_file(sleepy_pipe, initial_time, end_time);
    writing_file(active_pipe, initial_time, end_time);
    gettimeofday(&end_time, NULL);
  }
}
