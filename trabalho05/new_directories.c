#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct path_node{
  const char *path;
  struct path_node *next;
  int level;
}path_node;

typedef struct path_list{
  path_node *first;
  path_node *last;
  int quantity;
}path_list;

path_node* initialize_node(char *path, int level){
  path_node *new_node = malloc(sizeof(path_node));
  new_node->path = path;
  new_node->level = level + 1;
  new_node->next = NULL;
  return new_node;
}

void insert_list(path_node *new_node, path_list *list){
  if(list->first == NULL){
    list->first = new_node;
    list->last = new_node;
  }
  else{
    list->last->next = new_node;
    list->last = new_node;
  }
  list->quantity++;
}

void listdir(const char *name, int level, path_list *list){
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while (entry = readdir(dir)) {
        if (entry->d_type != DT_DIR) {
          printf("%*s- %s\n", level*2, "", entry->d_name);
        }
        else{
          char path[1024];
          int len = snprintf(path, sizeof(path)-1, "%s/%s/", name, entry->d_name);
          path[len] = 0;
          if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            /* ignore*/
          }
          else{
            insert_list(initialize_node(path,level), list);
            printf("\t\tfirst in list: %s\n", list->first->path);
          }
        }
        if(list->first != NULL)
          printf("\t\tWTF in list: %s\n", list->first->path);
    }
    closedir(dir);
    printf("\t\treturning in list: %s\n", list->first->path);
}

int main(int argc, char const *argv[]) {
  int max_level = 3;
  path_list *list = malloc(sizeof(path_list));
  list->quantity = 0;
  list->first = NULL;
  list->last = NULL;
  listdir("/home/fabiola/Desktop/fso/trabalho05", 0, list);
  printf("%d", list->quantity);
  // while(list->first != NULL && list->first->level < max_level){
  //   path_node *next_node = list->first;
  //   list->first = list->first->next;
  //   printf("Next path: %s\n", next_node->path);
  //   listdir(next_node->path, list->first->level, list);
  //   free(next_node);
  // }
  return 0;
}
