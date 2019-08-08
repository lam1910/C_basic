#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Source "phone.dat"
#define lenS 20

//structure for content of a node
//declare element type
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
  node* next;
}node;

//number of elements
int num;

//the beginning, current, previous position respectively
node* root, *cur, *prev;

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

//make a new node using existing contact with *next point to NULL
node* makeNewNode(elementtype elm)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  new->element = elm;
  new->next = NULL;
  return new;
}

//print a single node
void printNode(node* now)
{
  if (now == NULL)
    {
      printf("do not have this node.\n");
      return;
    }
  elementtype tmp = now->element;
  printf("%s\t%s\t%s %p\n", tmp.name, tmp.tel, tmp.email, now->next);
}

//show all node
void traversingList()
{
  node* tmp;
  for (tmp = root; tmp != NULL; tmp = tmp->next)
    printNode(tmp);
  printf("\n\tEnd of list\n");
}

//add node to first
void insertHead(elementtype elm)
{
  node* newNode = makeNewNode(elm);
  newNode->next = root;
  root = newNode;
  cur = root;
  printf("Action completed!\n");
}

//insert after the current position
void insertAfter(elementtype elm)
{
  node* append = makeNewNode(elm);
  if (root == NULL)
    {
      printf("No root detected. Creating new root......");
      root = append;
      cur = root;
      printf("Action Completed!\n");
    }
  else
    {
      append->next = cur->next;
      cur->next = append;
      prev = cur;
      cur = cur->next;
      printf("Action completed!\n");
    }
}

//insert before the current position
void insertBefore(elementtype elm)
{
  node* append = makeNewNode(elm);
  if (root == NULL)
    {
      printf("No root detected. Creating new root......");
      root = append;
      cur = root;
      printf("Action completed\n");
    }
  else if (cur == root)
    insertHead(elm);
  else
    {
      append->next = cur;
      prev->next = append;
      cur = append;
      printf("Action Completed\n");
    }
}

//insert after position n
node* insertAtPosition(node* root, elementtype elm, int n)
{
  int i;
  node* tmp;
  cur = NULL;
  prev = NULL;
  for (tmp = root; tmp != NULL; tmp = tmp->next)
    {
      prev = cur;
      cur = tmp;
      if (i == n)
	{
	  insertAfter(elm);
	  return cur;
	}
      ++ i;
    }
  insertAfter(elm);
  return cur;
}

//delete root
void deleteHead()
{
  node* del = root;
  root = del->next;
  free(del);
  printf("Deletion completed\n");
}

//delete at cur position
void delete()
{
  if (cur == root)
    deleteHead();
  else
    {
      prev->next = cur->next;
      free(cur);
      cur = prev->next;
    }
}

//delete at position n
node* deleteAtPosition(node* root, int n)
{
  int i = 1;
  node* tmp;
  if (n <= 0)
    {
      deleteHead();
      return cur;
    }
  else
    {
      cur = root;
      prev = NULL;
      for(tmp = root->next; tmp != NULL; tmp = tmp->next)
	{
	  prev = cur;
	  cur = tmp;
	  if (i == n)
	    {
	      delete();
	      return cur;
	    }
	  ++ i;
	}
      delete();
      return cur;
    }
}

//delete node with infor satisfied
node* deleteElement(node* root, elementtype elm)
{
  prev = NULL;
  cur = NULL;
  node* tmp;
  for(tmp = root; tmp != NULL; tmp = tmp->next)
    {
      prev = cur;
      cur = tmp;
      if ((tmp->element.name == elm.name) && (tmp->element.tel == elm.tel) && (tmp->element.email == elm.email))
	{
	  delete();
	  return cur;
	}
    }
  printf("Element not found. Will return the root.\n");
  return root;
}

//free list
void freeLinked()
{
  node* to_free = root;
  while (to_free != NULL)
    {
      root = root->next;
      free(to_free);
      to_free = root;
    }
}

//splitList
node* split(int n1, int n2)
{
  node* root2,* tmp;
  int lenList;
  for (tmp = root; tmp != NULL; tmp = tmp->next)
    ++lenList;
  while (n1 < 0)
    {
      printf("Does not recognize this position.\nEnter the start position again: ");
      scanf("%d", &n1);
      getchar();
    }

  while (n2 <= 0)
    {
      printf("Number of elements can not be smaller than 1.\nRenter n2: ");
      scanf("%d", &n2);
      getchar();
    }

  if (n1 > lenList)
    {
      printf("Cannot find the start position. Returning NULL");
      return NULL;
    }
  else
    {
      cur = root;
      for (int i = 0; i < n1; ++i)
	{
	  prev = cur;
	  cur = cur->next;
	}
      root2 = cur->next;
      for (tmp = root2; tmp != NULL; tmp = tmp->next)
	{
	  --n2;
	  if (n2 == 0)
	    {
	      cur->next = tmp->next;
	      tmp->next = NULL;
	      return root2;
	    }
	}
      cur->next = NULL;
      return root2;
    }
}

int main(int argc, char* argv[])
{
  //argc = 3, split n1 n2
  int n1;//start position
  int n2;//elements in first list

  if (argc > 3)
    {
      printf("Too many arguments were given. The correct syntax:\n");
      printf("\tsplit startPosition elementsInsubList1\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc < 3)
    {
      printf("Not enough arguments were given. The correct syntax:\n");
      printf("\tsplit startPosition elementsInsubList1\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      n1 = atoi(argv[1]);
      n2 = atoi(argv[2]);

      //linked content on source file to a list
      elementtype* people;
      people = (elementtype* )malloc(lenS * sizeof(elementtype));
      printf("Completed\n");
      FILE* s;
      s = fopen(Source, "r+b");
      if (s == NULL)
	{
	  printf("Cannot open %s. Exit!\n", Source);
	  exit(1);
	}
      else
	{	  
	  fread(people, sizeof(elementtype), lenS, s);
	  printf("Completed\n");
	  int j;
	  for(j = 0; j < lenS; ++j)
	    {
	      insertAfter(people[j]);
	    }
	  printf("Imported.\n");
	}
      free(people);
      fclose(s);

      node* root2 = split(n1, n2);
      char filename[256];
      printf("Your file name or path: ");
      fgets(filename, 256, stdin);

      //open file for print result
      FILE* fin;
      fin = fopen(filename, "w");

      if (fin == NULL)
	{
	  printf("Cannot open %s. Exit!\n", filename);
	  exit(1);
	}
      else
	{
	  fputs("The contain of first sublist:\n", fin);
	  node* now;
	  for (now = root2; now != NULL; now = now->next)
	    {
	      elementtype tmp = now->element;
	      fprintf(fin, "%s\t%s\t%s %p\n", tmp.name, tmp.tel, tmp.email, now->next);
	    }
	  fputs("\n\tEnd of list\n", fin);

	  fputs("The contain of the second sublist:\n", fin);
	  for (now = root; now != NULL; now = now->next)
	    {
	      elementtype tmp = now->element;
	      fprintf(fin, "%s\t%s\t%s %p\n", tmp.name, tmp.tel, tmp.email, now->next);
	    }
	  fputs("\n\tEnd of list\n", fin);
	}
      fclose(fin);
      freeLinked(root);
      freeLinked(root2);
    }
  return 0;
}
