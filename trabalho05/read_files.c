#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int printed_number = 0;

void listdir(const char *name, int level,const char *search, int maxlvl){
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
      return;
    else {
      /*do nothing*/
    }
    if (!(entry = readdir(dir)))
      return;
    else {
      /*do nothing*/
    }
    if(level > maxlvl)
      return;
    else if(printed_number == maxlvl){
      return;
    }
    while ((entry = readdir(dir)) && printed_number < maxlvl && level <= maxlvl){
      if (entry->d_type == DT_DIR) {
        char path[1024];
        int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
        path[len] = 0;
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
          continue;
        }
        listdir(path, level + 1, search, maxlvl);
      }
      else{
        if(strstr(entry->d_name, search) != NULL) {
          printed_number++;
          printf("%d.%s%s --\n", printed_number, name, entry->d_name);
        }
        else {
          /*do nothing*/
        }
      }
    }
    closedir(dir);
}


int main(int argc, char const *argv[])
{
    int max_prints;
    sscanf(argv[3], "%d", &max_prints);
    listdir(argv[1], 1, argv[2], max_prints);

}
