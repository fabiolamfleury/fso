#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/prctl.h>
#include "pipe.h"

long int* print_time_stamp(struct timeval initial_time, struct timeval end_time, long int *times){
  times = malloc(sizeof(int)*2);
  times[0] = end_time.tv_sec - initial_time.tv_sec;
  times[1] = (end_time.tv_usec - initial_time.tv_usec) - (times[0] * 60);
  return times;
}

void writing_file(int pipe[], struct timeval initial_time){

  struct timeval tv;
  fd_set rfds;
  FD_ZERO(&rfds);
  FD_SET(pipe[0], &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 5;

  int retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);

  if(retval > 0){
    FILE* stream;
    stream = fdopen (pipe[0], "r");
    close (pipe[0]);

    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    long int *times;
    times = print_time_stamp(initial_time, end_time, times);

    FILE *output = fopen("output.txt", "a");
    reader (stream, output, times);
    fclose(output);
  }
}
