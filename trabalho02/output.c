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
  long int elapsed_time = (end_time.tv_usec + 1000 * end_time.tv_sec)
  - (initial_time.tv_usec + 1000 * initial_time.tv_sec);

  times[0] = end_time.tv_sec - initial_time.tv_sec;
  times[1] = (unsigned) elapsed_time % 1000;
  return times;
}


void writing_file(int pipe[], struct timeval initial_time, struct timeval finish_time){

  struct timeval tv;
  fd_set rfds;
  FD_ZERO(&rfds);
  FD_SET(pipe[0], &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  int retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);

  if(retval > 0){

    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    long int * times, * parent_time;
    times = print_time_stamp(initial_time, end_time, times);
    parent_time = print_time_stamp(initial_time, finish_time, parent_time);
    FILE* stream;
    stream = fdopen (pipe[0], "r");
    reader (stream, parent_time, initial_time);
    close(pipe[0]);

  }

}
