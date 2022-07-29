/*
Author: Reis Ciaramitaro
Assignment Number: 1
Date of Submission: 7/30/2022
Name of this file: mypstree.c
Short Description of contents:
   This program outputs the whole process tree
   from a provided parent process.
*/

//include necessary C libs
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//define queue size
#define MAX 1000

//declare all used functions
void traverseParent();
void setParentId(char * id);
void setProcPath();
void insert(int data);
int removeData();

//declare global variables used for traversal
char parentId[5];
char fileName[25];
char indent[50];

//declare global variables used for queue
int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

/*
Function Name: main
Input to the method: The input of a single parent id is required
Output(Return value): This method doesnt return anything as it is main
Brief description of the task:
   This main method makes all the required function calls necessary to 
   traverse an existing inputted parent
*/
void main( int argc, char *argv[] ) {
   int MARKER = -1;

  if (argc < 2) {
    printf ("You must supply a parent ID\n");
    exit(1);
  }
  insert(atoi(argv[1])); //insert the root parent into queue as an integer
  insert(MARKER); 
  traverseParent();

}

/*
Function Name: traverseParent
Input to the method: This method doesn't take any input as args
Output(Return value): This method doesnt return anything
Brief description of the task:
   This method traverses through the inputted process tree
   printing out the children of each parent.
*/
void traverseParent() {
   int MARKER = -1;

   while (itemCount != 0) {
      //declare necessary vars
      int num = removeData();
      char snum[6];
      int i = 0;
      
      printf("\n"); //print new line

      //if MARKER is dequed add new MARKER to queue
      if (num == MARKER) {
         strcat(indent, "\t");
         insert(MARKER);
         num = removeData();
         if (itemCount == 0) { //if nothing is queue at this point then queue is done.
            exit(1);
         }
      }

      //convert dequed int to string, update the file path, and children file.
      sprintf(snum, "%d", num);
      setParentId(snum);
      FILE* file = fopen (fileName, "r");

      printf("%sChildren of %s: ", indent, parentId);

      //scan and add every existing child to queue
      fscanf (file, "%d", &i);    
      while (!feof (file))
      {  
         insert(i); //add to queue
         printf ("%d ", i);
         fscanf (file, "%d", &i); //scan next int
      }
      fclose (file); //close the file when done
   }
}

/*
Function Name: setParentId
Input to the method: The id as string to be set as the current parent id
Output(Return value): Sets the global parentId variable
Brief description of the task:
   Sets the global parent id variable to the inputted id. It then 
   updates the filepath in respect to the new parent id.
*/
void setParentId(char * id) {
  strcpy(parentId, id);
  setProcPath();
}

/*
Function Name: setProcPath
Input to the method: This method takes no arguments and only uses global variables
Output(Return value): This method only sets global variables
Brief description of the task:
   This method updates the global file path to access a parents children.
*/
void setProcPath() {
   char proc[] = "/proc/";
   char task[] = "/task/";
   char children[] = "/children";

   sprintf(fileName, "%s", ""); //reset file name

   //concatenate that file path in the appropriate order
   strcat(fileName, proc);
   strcat(fileName, parentId);
   strcat(fileName, task);
   strcat(fileName, parentId);
   strcat(fileName, children);
}

/*
Function Name: insert
Input to the method: This method takes a single integer data as an arg
Output(Return value): This method returns nothing
Brief description of the task:
   This method inserts the given data to the queue
*/
void insert(int data) {

   if(itemCount != MAX) {
	
      if(rear == MAX-1) {
         rear = -1;            
      }       

      intArray[++rear] = data;
      itemCount++;
   }
}

/*
Function Name: removeData
Input to the method: This method doesnt take any args
Output(Return value): This method returns the data that was removed from the queue
Brief description of the task:
   This method removes a single piece of data from the front
   of the queue and returns it.
*/
int removeData() {
   int data = intArray[front++];
	
   if(front == MAX) {
      front = 0;
   }
	
   itemCount--;
   return data;  
}