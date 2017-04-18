#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int spawn (char* program, char** arg_list)
{
  pid_t child_pid;
  int process_id;
  /* Duplicate this process. */
  child_pid = fork ();
  if (child_pid != 0){
    sleep(10000); // 30 seconds
    kill(child_pid, SIGKILL);
    return child_pid;
  }
  else {
    /* Now execute PROGRAM, searching for it in the path. */
    execvp (program, arg_list);
    /* The execvp function returns only if an error occurs. */
    fprintf (stderr, "an error occurred in execvp\n");
    abort ();
  }
}



int main(int argc, char const *argv[]) {
  int i;
  char* child1_list[] = {
    "./c1", /* argv[0], the name of the program. */
    NULL /* The argument list must end with a NULL. */
    };
  i = spawn("./c1", child1_list);
  printf("VAMO CARAI: %d", i);

  return 0;
}
