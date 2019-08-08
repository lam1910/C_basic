#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct for elementtype
typedef struct address
{
  char name[20];
  char tel[12];
  char email[255];
}elementtype;

//declare 1 node
typedef struct node node;

//struct for 1 node
typedef struct node
{
  elementtype element;
  node* prev;
  node* next;
};

//declare 1 pointer
typedef node* doublelist;

//pointer to first, last, current position
doublelist head, tail, cur;

//make a new list
void MakeNull_List(doublelist* root, doublelist* tail, doublelist* cur)
{
  (*root) = NULL;
  (*tail) = NULL;
  (*cur) = NULL;
}

//check if the node is empty
int isEmpty(doublelist root)
{
  return (root == NULL);
}

//get data from user input as elementtype
elementtype readNode()
{
  elementtype new;
  printf("Please note that there are instructions on how to type in each component. Do not follow these rules will result in a lost of information\n\n\n"); 
  printf("Name: (Please enter less than 19 characters, for name that longer than 19 characters use acronym for middle name)\n\t");
  fgets(new.name, 20, stdin);
  printf("Telephone number: (Supported 11 numbers at most) \n\t");
  fgets(new.tel, 12, stdin);
  printf("Email: (Supported 254 characters at most)\n\t");
  fgets(new.email, 255, stdin);
  return new;
}

//make a new double linked node
doublelist makeNewNode(elementtype elm)
{
  doublelist new;
  new = (doublelist)malloc(sizeof(node));
  new->element = elm;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

//print a single node
void printNode(doublelist now)
{
  if (now == NULL)
    {
      printf("Do not have this node.\n");
      return;
    }
  elementtype tmp = now->element;
  printf("%p\n%s\t%s\t%s %p\n", now->prev, tmp.name, tmp.tel, tmp.email, now->next);
}

//show all node
void traversingList()
{
  doublelist tmp;
  for (tmp = root; tmp != NULL; tmp = tmp->next)
    printNode(tmp);
  printf("\n\tEnd of list.\n");
}

//insert after current position
void insertAfter(elementtype elm)
{
  doublelist append = makeNewNode(elm);
  if (root == NULL)
    {
      printf("No root detected. Creating new root.......");
      root = append;
      cur = root;
      printf("Action completed!\n");
    }
  else if (cur == tail)
    insertTail(elm);
  else
    {
      append->next = cur->next;
      append->prev = cur;
      cur->next = append;
      cur = cur->next;
      cur->next->prev = append;
      printf("Action completed!\n");
    }
}

//insert at the first position (0-th)
void insertHead(elementtype elm);
{
  node* newNode = makeNewNode(elm);
  newNode->next = root;
  root = newNode;
  cur = root;
  printf("Action Completed!\n");
}

//insert at the last position (tail-th)
void insertTail(elementtype elm)
{
  node* newNode = makeNewNode(elm);
  newNode->prev = tail;
  tail = newNode;
  cur = tail;
  printf("Action Completed!\n");
}

//insert before the current position
void insertBefore(elementtype elm)
{
  doublelist append = makeNewNode(elm);
  if (root == NULL)
    {
      printf("No root detected. Creating new root.......");
      root = append;
      cur = root;
      printf("Action completed!\n");
    }
  else if (cur == root)
    insertHead(elm);
  else
    {
      append->next = cur;
      append->prev = cur->prev;
      cur->prev = append;
      cur = cur->prev;
      cur->prev->next = append;
      printf("Action completed!\n");
    }
}

//insert after a pre-defined position p
doublelist insert
