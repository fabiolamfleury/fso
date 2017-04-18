#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(){
  int i = 1;
  srand(time(NULL));
  struct timeval elapsed_time;
  struct timeval initial_time;

  gettimeofday(&initial_time,NULL);

  while(1){
    int randNum = (rand() % 4);
    printf("\nrandnum: %d", randNum);
    sleep(randNum);
    gettimeofday(&elapsed_time,NULL);
    printf("\n0:%02ld :%ld: Mensagem %d do filho dorminhoco\n",
           (elapsed_time.tv_sec - initial_time.tv_sec), elapsed_time.tv_usec - initial_time.tv_usec,i);
    i++;
  }

  return 0;

}
