#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pipe.h"
#include "output.h"
#include "children.h"

void wait_time(pid_t parent, pid_t sleepy, pid_t active) {
    pid_t child;

    child = fork();
    if (child != (pid_t) 0) {
      /* parent process exit from function */
      sleep(5);
      kill(sleepy, SIGKILL);
      kill(active, SIGKILL);
      kill(parent, SIGKILL);
      raise(SIGKILL);
    }
    else {
      /* child proces to wait execution and then kill processes*/
      return;
    }
    return;
}

int spawn () {
  pid_t sleepy_pid;
  pid_t active_pid;

  int sleepy_pipe[2];
  int active_pipe[2];
  pipe (sleepy_pipe);
  pipe (active_pipe);
  sleepy_pid = fork();

  /* parent process */
  if (sleepy_pid != 0){
    active_pid = fork();
    if(active_pid != 0){
      wait_time(getpid(), sleepy_pid, active_pid);
      reading_messages(sleepy_pipe, active_pipe);
    }
    else{
      active_child(active_pipe);
    }

  }
  else {
    /* sleepy child */
    sleepy_child(sleepy_pipe);
  }
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  remove("output.txt");
  spawn();
  return 0;
}
