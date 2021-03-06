#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define CAPACITY 50

typedef struct node {
  int number;
  struct node *next;
  struct node *previous;
}Node;

typedef struct buffer {
  int capacity;
  int quantity;
  Node *head;
  Node *tail;
}Buffer;

/* handling ctrl c signal*/
static volatile int TRUE = 1;

void sigHandler(int dummy) {
  TRUE = 0;
}

/*linked list representing buffer*/
Buffer *buffer;

/*mutex protecting buffer*/
pthread_mutex_t buffer_queue_mutex = PTHREAD_MUTEX_INITIALIZER;


void initializing_buffer () {
  buffer = malloc(sizeof(Buffer));
  buffer->capacity = CAPACITY;
  buffer->quantity = 0;
  buffer->head = NULL;
  buffer->tail = NULL;
}

void node_insertion (Node *node) {
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

void node_deletion () {
  Node *node;
  node = buffer->tail;
  if (buffer->tail == buffer->head) {
    buffer->tail = NULL;
    buffer->head = NULL;
  }
  else if (buffer->tail != NULL) {
    buffer->tail = buffer->tail->previous;
    buffer->tail->next = NULL;
  }
  buffer->quantity--;
  free (node);
}

void* produce_random (void *arg) {
  char *file_name = (char*) arg;
  int max_buffer = 0;
  /*producing random numbers*/
  while (TRUE) {
    pthread_mutex_lock (&buffer_queue_mutex);
    if(buffer->quantity < CAPACITY) {
      /*inserting new node in buffer */
      Node * node = malloc (sizeof (Node));
      int random = (rand() % 1000000000);
      node->number = random;
      node->next = NULL;
      node->previous = NULL;
      node_insertion (node);

      /*storing max capacity number achieved in buffer*/
      if (max_buffer < buffer->quantity) {
        max_buffer = buffer->quantity;
      }
      else {
        /*do nothing*/
      }

      /*writing insertion on log*/
      FILE* output = fopen(file_name, "a");
      fprintf(output, "[producao]: Numero gerado: %d\n", node->number);
      fclose(output);
    }
    else{
      /*do nothing */
    }
    pthread_mutex_unlock (&buffer_queue_mutex);
    sleep (0.1);
  }

  return (void*) max_buffer;
}

void* consume_number_a (void* parameter) {
  char *file_name = (char*) parameter;
  int *numbers = malloc(sizeof(int)*2);

  numbers[0] = 999999999;
  numbers[1] = 0;
  while (TRUE) {
    pthread_mutex_lock (&buffer_queue_mutex);
    if (buffer->quantity > 0) {
      if ((buffer->tail)->number < numbers[0]) {
        numbers[0] = (buffer->tail)->number;
      }
      else if ((buffer->tail)->number > numbers[1]) {
        numbers[1] = (buffer->tail)->number;
      }

      /*writing reading on log*/
      FILE *output = fopen(file_name, "a");
      fprintf(output, "[consumo a]: Numero lido: %d\n", (buffer->tail)->number);
      fclose(output);
      node_deletion ();
    }
    else {
      /*do nothing*/
    }
    pthread_mutex_unlock (&buffer_queue_mutex);
    sleep (0.15);
  }
  return (void*) numbers;
}

void* consume_number_b (void* parameter) {
  char *file_name = (char*) parameter;
  int *numbers = malloc(sizeof(int)*2);

  numbers[0] = 999999999;
  numbers[1] = 0;
  while (TRUE) {
    pthread_mutex_lock (&buffer_queue_mutex);
    if (buffer->quantity > 0) {
      if ((buffer->tail)->number < numbers[0]) {
        numbers[0] = (buffer->tail)->number;
      }
      else if ((buffer->tail)->number > numbers[1]) {
        numbers[1] = (buffer->tail)->number;
      }

      /*writing reading on log*/
      FILE* output = fopen(file_name, "a");
      fprintf(output, "[consumo b]: Numero lido: %d\n", (buffer->tail)->number);
      fclose(output);
      node_deletion ();
    }
    else {
      /*do nothing*/
    }
    pthread_mutex_unlock (&buffer_queue_mutex);
    sleep (0.15);
  }
  return (void*) numbers;
}

int* comparing_numbers(int *array_a, int *array_b){

  int *result = malloc (sizeof(int)*2);

  /*picking smallest*/
  if(array_a[0] < array_b[0]){
    result[0] = array_a[0];
  }
  else{
    result[0] = array_b[0];
  }

  /*picking highest*/
  if(array_a[1] > array_b[1]){
    result[1] = array_a[1];
  }
  else{
    result[1] = array_b[1];
  }

  return result;
}


int main(int argc, char const *argv[]) {
  /*initializing buffer*/
  initializing_buffer ();
  srand(time(NULL));
  signal(SIGINT, sigHandler);
  char *string = malloc(sizeof(char)*100);
  if(argc == 2){
    strcpy (string, argv[1]);

    /*creating producer thread */
    pthread_t producer_id;
    pthread_create(&producer_id, NULL, &produce_random, string);

    /*creating consumers threads */
    pthread_t consumer1_id;
    pthread_create(&consumer1_id, NULL, &consume_number_a, string);
    pthread_t consumer2_id;
    pthread_create(&consumer2_id, NULL, &consume_number_b, string);

    while (TRUE) {
      /*do nothing*/
    }

    /*finishing program*/
    printf("\n[aviso]: Termino solicitado. Aguardando threads...");
    int *numbers_consumer1;
    int *numbers_consumer2;
    int max_buffer;
    /*waiting for others threads to finish*/
    pthread_join(producer_id, (void*) &max_buffer);
    pthread_join (consumer1_id, (void*) &numbers_consumer1);
    pthread_join (consumer2_id, (void*) &numbers_consumer2);

    /*comparing smallest and highest numbers from both consumers*/
    int *result = malloc (sizeof(int)*2);
    result = comparing_numbers (numbers_consumer1, numbers_consumer2);

    printf("\n[aviso]: Maior numero gerado: %d",result[1]);
    printf("\n[aviso]: Menor numero gerado: %d", result[0]);
    printf("\n[aviso]: Maior ocupacao de buffer: %d", max_buffer);
    printf("\n[aviso]: Aplicacao encerrada.");
    printf("\n");
    FILE* output = fopen(string, "a");
    fprintf(output, "\n[aviso]: Maior numero gerado: %d",result[1]);
    fprintf(output, "\n[aviso]: Menor numero gerado: %d", result[0]);
    fprintf(output, "\n[aviso]: Maior ocupacao de buffer: %d", max_buffer);
    fprintf(output, "\n[aviso]: Aplicacao encerrada.");
    fclose(output);
  }
  else{
    printf("O nome do arquivo deve ser passado como parametro \n");
  }

  return 0;
}
