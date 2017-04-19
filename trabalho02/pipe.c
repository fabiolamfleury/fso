#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "output.h"

void writing_pipe(int pipe[], long int times[], int i, char *message){
  close (pipe[0]);
  FILE *stream;
  stream = fdopen (pipe[1], "w");
  fprintf (stream, "0:%02ld.%03ld: Mensagem %d do %s\n", times[0], times[1], i, message);
  fflush (stream);
  close (pipe[1]);
}

void reader (FILE* stream, FILE* output, long int times[]){
  char buffer[1024];
  /* Read until we hit the end of the stream. fgets reads until
  either a newline or the end-of-file. */
  while (!feof (stream)
         && !ferror (stream)
         && fgets (buffer, sizeof (buffer), stream) != NULL)

         fprintf (output, "0:%02ld.%03ld: %s\n", times[0],times[1], buffer);
}


void reading_messages(int pipe[]){
  close (pipe[1]);
  struct timeval initial_time;
  gettimeofday(&initial_time, NULL);

  while(1){
    writing_file(pipe, initial_time);
  }
}
