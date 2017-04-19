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
#include "output.h"
#include "children.h"

void wait_time(pid_t parent, pid_t sleepy);

void wait_time(pid_t parent, pid_t sleepy) {
    pid_t child;

    child = fork();
    if (child != (pid_t) 0) {
      /* parent process exit from function */
      sleep(10);
      kill(sleepy, SIGKILL);
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
  pid_t child_pid;
  int sleepy_pipe[2];
  pipe (sleepy_pipe);

  child_pid = fork();

  /* parent process */
  if (child_pid != 0){
    /* process to wait execution */

    wait_time(getpid(), child_pid);
    printf("acorda carai");
    reading_messages(sleepy_pipe);

  }
  else {
    /* sleepy child */
    sleepy_child(sleepy_pipe);
  }
}

int main(int argc, char const *argv[]) {

  spawn();
  return 0;
}
