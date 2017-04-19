#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "output.h"
#include "pipe.h"

void sleepy_child(int *fds){
  int i = 1;
  long int seconds;
  long int miliseconds;
  struct timeval elapsed_time;
  struct timeval initial_time;

  gettimeofday(&initial_time,NULL);

  while(1){
    int randNum = (rand() % 3);
    sleep(randNum);
    gettimeofday(&elapsed_time, NULL);
    long int *times = print_time_stamp(initial_time, elapsed_time, times);
    writing_pipe(fds, times, i, "filho dorminhoco");
    i++;
  }

}
