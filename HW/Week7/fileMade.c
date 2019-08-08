#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  printf("Please note that there are instructions on how to type in each component. Do not follow these rules will result in a lost of information\n"); 
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
}

//insert after current position
void insertAfter(elementtype elm)
{
  node* append = makeNewNode(elm);
  if (root == NULL)
    {
      printf("No root detected. Creating new root...\t");
      root = append;
      cur = root;
      prev = NULL;
      printf("New root has been created.\n");
    }
  else
    {
      append->next = cur->next;
      cur->next = append;
      prev = cur;
      cur = cur->next;
      printf("Action completed. Adding new node successfully.\n");
    }
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

int main(int argc, char* argv[])
{
  //argc = 3, filemade modeOfWriting((t)ext or (b)inary) nameOfOutFile

  char mode;
  char fileOut[256];

  if (argc < 3)
    {
      printf("Not enough arguments were given.\nThe correct syntax:\n");
      printf("\tfilemade modeOfWriting((t)ext or (b)inary) nameOfOutFile\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc > 3)
    {
      printf("Too many arguments were given.\nThe correct syntax:\n");
      printf("\tfilemade modeOfWriting((t)ext or (b)sinary) nameOfOutFile\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      char dump[3];
      strncpy(dump, argv[1], 3);
      mode = dump[0];
      strcpy(fileOut, argv[2]);

      int i;
      elementtype* addresses;
      printf("How many elements in the file: ");
      scanf("%d", &num);
      getchar();
      addresses = (elementtype* ) malloc(num * sizeof(elementtype));
      for (i = 0; i < num; i ++)
	{
	  addresses[i] = readNode();
	  insertAfter(addresses[i]);
	}
      printf("What you just type in (for comparison with the content of file below)\n");
      traversingList();
      free(addresses);
      
      //handle mode
      if ((mode == 'b') || (mode == 'B'))
	{
	  //open file for binary writing
	  FILE* ptr;
	  ptr = fopen(fileOut, "w+b");

	  if (ptr == NULL)
	    {
	      printf("Cannot open %s.\n", fileOut);
	      exit(1);
	    }
	  else
	    {
	      node* tmp = root;
	      while(tmp != NULL)
		{
		  fwrite(&(tmp->element), sizeof(elementtype), 1, ptr);
		  tmp = tmp->next;
		}
	      fclose(ptr);
	    }
	  
	  //print out content of the written file
	  elementtype* people;
	  people = (elementtype* )malloc(num* sizeof(elementtype));
	  ptr = fopen(fileOut, "r+b");
	  if (ptr == NULL)
	    {
	      printf("Cannot open %s.\n", fileOut);
	      exit(1);
	    }
	  else
	    {
	      printf("Content of the file:\n");
	      fread(people, sizeof(elementtype), num, ptr);
	      for(i = 0; i < num; ++i)
		{
		  printf("%s\t%s\t%s\n", people[i].name, people[i].tel, people[i].email);
		}
	    }
	  printf("End of File.\n");
	  free(people);
	  fclose(ptr);
	}
      else if ((mode == 't') || (mode == 'T'))
	{
	  //open file for normal writing
	  FILE* ptr;
	  ptr = fopen(fileOut, "w+");

	  if (ptr == NULL)
	    {
	      printf("Cannot open %s.\n", fileOut);
	      exit(1);
	    }
	  else
	    {
	      node* tmp;
	      for (tmp = root; tmp != NULL; tmp = tmp->next)
		{
		  fwrite(&(tmp->element), sizeof(elementtype), 1, ptr);
		}
	      fclose(ptr);
	    }
	  
	  //print out content of the written file
	  elementtype* people;
	  people = (elementtype* )malloc(num* sizeof(elementtype));
	  ptr = fopen(fileOut, "r+");
	  if (ptr == NULL)
	    {
	      printf("Cannot open %s.\n", fileOut);
	      exit(1);
	    }
	  else
	    {
	      printf("Content of the file:\n");
	      fread(people, sizeof(elementtype), num, ptr);
	      for (i = 0; i < num; ++i)
		{
		  printf("%s\t%s\t%s\n", people[i].name, people[i].tel, people[i].email);
		}
	    }
	  printf("End of File.\n");
	  free(people);
	  fclose(ptr);
	}
      else
	{
	  printf("Undefined mode of writing./nThere only 2 mode t or T for text and b or B for binary.\nExit now!\n");
	  exit(1);
	}
    }

  freeLinked(root);
  return 0;
}
