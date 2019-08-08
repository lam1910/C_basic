#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define source "american-english"
#define MAX_LEN 80

typedef char elmtypeL;
typedef struct node node;
typedef struct node
{
  elmtypeL character;
  node* toFront;
  node* toRear;
}node;

typedef struct queue
{
  node* Front;
  node* Rear;
}queueType;

//create an empty queue
queueType* initializeQ()
{
  queueType* q = (queueType* )malloc(sizeof(queueType));
  q->Front = q->Rear = NULL;
  return q;
}

//make a new node
node* makeNewNode(elmtypeL character)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  new->character = character;
  new->toFront = NULL;
  new->toRear = NULL;
  return new;
}

void enQueue(queueType* q, elmtypeL k)
{
  node* append = makeNewNode(k);

  //check if queue is empty, then both Front and Rear is the new node
  if (q->Rear == NULL)
    {
      q->Front = q->Rear = append;
      return;
    }

  //else add new node to the queue and change pointer Rear
  q->Rear->toRear = append;
  append->toFront = q->Rear;
  q->Rear = append;
}

node* deQueue(queueType* q)
{
  //check if que is empty, return NULL.
  if (q->Front = NULL)
    return NULL;

  //move Front one node toRear
  node* tmp = q->Front;
  q->Front = q->Front->toRear;
  tmp->toRear = NULL;
  q->Front->toFront = NULL;

  //check if Front become NULL, if so then change Rear to NULL
  if (q->Front == NULL)
    q->Rear = NULL;
  return tmp;
}

int wordcmp(char word[], char key[])
{
  if (strcmp(word, key) == 0)
    return 1;
  else
    {
      int i = strlen(key);
      char tmp[20];
      strncpy(tmp, word, i);
      if (strcmp(tmp, key) == 0)
	return 1;
    }
  return 0;
}

int main(int argc, char* argv[])
{
  //argc = 2, look yourWord
  char key[20];

  if (argc < 2)
    {
      printf("Not enough argument was given. The correct syntax:\n");
      printf("\tlock yourWord\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc > 2)
    {
      printf("Too many arguments were given. The correct syntax:\n");
      printf("\tlock yourWord\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      strcpy(key, argv[1]);
            
      //open file
      FILE* in;
      in = fopen(source, "r+");
      if (in == NULL)
	{
	  printf("Cannot reach source file. Exit!\n");
	  exit(1);
	}
      else
	{
	  char line[MAX_LEN];
	  while (fgets(line, sizeof(line), in) != NULL)
	    {
	      if (wordcmp(line, key) == 1)
		printf("%s\n", line);
	    }
	}

      fclose(in);
    }
  return 0;
}
