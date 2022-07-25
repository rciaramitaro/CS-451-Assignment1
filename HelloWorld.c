#include<stdio.h>
#include <string.h>

char parentId[5];
char proc[] = "/proc/";
char task[] = "/task/";
char children[] = "/children";
char fileName[25];

int main() {
  setParentId("1");
  setProcPath();
 
  FILE* file = fopen (fileName, "r");
  int i = 0;
  //add 1 as root to queue

  //while (queue is not empty) {
    //deqeue parent
    printf("Children of %s: ", parentId);
    fscanf (file, "%d", &i);    
    while (!feof (file))
    {  
      printf ("%d ", i);
      fscanf (file, "%d", &i);
      //add child to queue     
    }
    fclose (file);
  //}
}

void setParentId(char * id) {
  strcpy(parentId, id);
}

void setProcPath(char * parentId) {
  strcat(fileName, proc);
  strcat(fileName, parentId);
  strcat(fileName, task);
  strcat(fileName, parentId);
  strcat(fileName, children);
}