#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define CAPACITY 50

typedef struct node {
  int number;
  struct node * next;
  struct node * previous;
}Node;

typedef struct buffer {
  int capacity;
  int quantity;
  Node * head;
  Node * tail;
}Buffer;

/*linked list representing buffer*/
Buffer * buffer;

/*mutex protecting buffer*/
pthread_mutex_t buffer_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void node_insertion (Node * node) {
  if (buffer->head == NULL) {
      buffer->head = node;
      buffer->tail = node;
  }
  else{
    buffer->tail->next = node;
    node->previous = buffer->tail;
    buffer->tail = node;
  }
  buffer->quantity++;
}

void* produce_random (void * arg) {
  pthread_mutex_lock (&buffer_queue_mutex);
  char * file_name = (char *) arg;
  /*initializing buffer*/
  buffer = malloc(sizeof(Buffer));
  buffer->capacity = CAPACITY;
  buffer->quantity = 0;
  buffer->head = NULL;
  buffer->tail = NULL;

  /*producing random numbers*/
  while (TRUE) {
    if(buffer->quantity < CAPACITY) {
      /*inserting new node in buffer */
      Node * node = malloc (sizeof (Node));
      int random = (rand() % 1000000000);
      node->number = random;
      node->next = NULL;
      node->previous = NULL;
      node_insertion (node);

      /*writing insertion on log*/
      FILE* output = fopen(file_name, "a");
      fprintf(output, "[producao]: Numero gerado: %d\n", node->number);
      fclose(output);
    }
    else{
      /*do nothing */
      FILE* output = fopen(file_name, "a");
      fprintf(output, "CARAI\n");
      fclose(output);
    }
    pthread_mutex_unlock (&buffer_queue_mutex);
    sleep (0.1);
  }
  return NULL;
}

void* consume_number (void* parameters)
{
  /*PÁGINA 102 DO PDF DO LIVRO TEM SOBRE IMPLEMENTAÇÃO DE SEÇÃO CRÍTICA*/
  return NULL;
}


int main(int argc, char const *argv[]) {
  pthread_t consumer2_id;
  pthread_t consumer1_id;
  char *string;
  strcpy (string, argv[1]);
  srand(time(NULL));
  void *parameters;
  if(argc == 2){
    /*creating producer thread */
    pthread_t producer_id;
    pthread_create(&producer_id, NULL, &produce_random, string);




    pthread_join(producer_id, NULL);
  }
  else{
    printf("O nome do arquivo deve ser passado como parametro \n");
  }

  return 0;
}
