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

void wait_time(pid_t parent);

void wait_time(pid_t parent) {
    pid_t child = fork();

    if (child != 0) {
        return;
    } else {
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        sleep(20);
        kill(parent, SIGKILL);
    }
}

int spawn ()
{
  pid_t child_pid;
  int fds[2];
  pipe (fds);
  /* Duplicate this process. */
  child_pid = fork ();
  if (child_pid != 0){
    wait_time(getpid());
    reading_messages(fds);
  }
  else {
    prctl(PR_SET_PDEATHSIG, SIGHUP);
    sleepy_child(fds);
    /* The execvp function returns only if an error occurs. */
    fprintf (stderr, "an error occurred in execvp\n");
    abort ();
  }
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int i;
  i = spawn();
  printf("PROCESSO PAI: %d", i);

  return 0;
}
