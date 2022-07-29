#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char parentId[5];
char proc[] = "/proc/";
char task[] = "/task/";
char children[] = "/children";
char fileName[25];
char indent[50];

#define MAX 1000

int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

int main( int argc, char *argv[] ) {

  if (argc < 2) {
    printf ("You must supply a parent ID\n");
    exit(1);
  }
  insert(atoi(argv[1]));
  insert(-1);

  while (itemCount != 0) {
    int num = removeData();
    //printf("Element removed: %d\n",num);
    if (num == -1) {
      strcat(indent, "\t");
      insert(-1);
      num = removeData();
    }
    char snum[6];
    sprintf(snum, "%d", num);
    setParentId(snum);
    //printf("Filepath is %s", fileName);
    
    FILE* file = fopen (fileName, "r");
    int i = 0;

    printf("\n%sChildren of %s: ", indent, parentId);
    fscanf (file, "%d", &i);    
    while (!feof (file))
    {  
      insert(i);
      printf ("%d ", i);
      fscanf (file, "%d", &i);
    }
    fclose (file);
  }
}

void setParentId(char * id) {
  strcpy(parentId, id);
  setProcPath();
}

void setProcPath() {
  sprintf(fileName, "%s", "");
  strcat(fileName, proc);
  strcat(fileName, parentId);
  strcat(fileName, task);
  strcat(fileName, parentId);
  strcat(fileName, children);
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int size() {
   return itemCount;
}  

void insert(int data) {

   if(!isFull()) {
	
      if(rear == MAX-1) {
         rear = -1;            
      }       

      intArray[++rear] = data;
      itemCount++;
   }
}

int removeData() {
   int data = intArray[front++];
	
   if(front == MAX) {
      front = 0;
   }
	
   itemCount--;
   return data;  
}