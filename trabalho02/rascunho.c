#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/prctl.h>

long int* print_time_stamp(struct timeval initial_time, struct timeval end_time, long int *times){
  times = malloc(sizeof(int)*2);
  times[0] = end_time.tv_sec - initial_time.tv_sec;
  times[1] = (end_time.tv_usec - initial_time.tv_usec) - (times[0] * 60);
  return times;
}


void writer(const char* message, long int* times, int i, FILE* stream){
  fprintf(stream, "0:%02ld.%03ld: Mensagem %d do %s", times[0], times[1], i, message);
  fflush(stream);
}

void reader(FILE* stream){
  char buffer[1024];
  FILE* output = fopen("output.txt", "a");

  while(!feof(stream) && !ferror(stream)&& fgets(buffer, sizeof(buffer), stream) != NULL) {
  	fprintf (output, "0: %s\n", buffer);
  }

  fclose(output);
}

int main(){
  int sleepy_process_pipe[2];
  pipe (sleepy_process_pipe);
  srand(time(NULL));
  pid_t sleepy_process;
  sleepy_process = fork();

  /* Active child process */
  if (sleepy_process == (pid_t)0) {
    int i =1;

    struct timeval elapsed_time;
    struct timeval initial_time;
    gettimeofday(&initial_time,NULL);
    while(1) {
      close (sleepy_process_pipe[0]); // close read

      FILE* stream;
      stream = fdopen (sleepy_process_pipe[1], "w");
      int randNum = (rand() % 3);
      sleep(randNum);
      gettimeofday(&elapsed_time, NULL);
      long int *times = print_time_stamp(initial_time, elapsed_time, times);


      writer("filho dorminhoco", times, i, stream);
      close (sleepy_process_pipe[1]);
      i++;
    }

  }
  /* Parent process */
  else {
    close (sleepy_process_pipe[1]); // close write
    FILE* stream;
    stream = fdopen (sleepy_process_pipe[0], "r");
    reader (stream);

    close(sleepy_process_pipe[0]);
  }

  return 0;
}
