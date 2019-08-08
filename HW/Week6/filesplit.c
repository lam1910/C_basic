#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//number of contacts other than root
int num;

//struct for content of a node
typedef struct address_t
{
  char name[20];
  char tel[12];
  char email[25];
}address;

//struct for a node
struct list_el
{
  address addr;
  struct list_el *next;
};
typedef struct list_el node_addr;

//the beginning, current position and previous positon respectively
node_addr *root, *cur, *prev;

//get data from user input as a contact
address addContact()
{
  address new;
  printf("Name: (please enter less than 19 character, for name that longer than 19 character use acronym for middle name)\n\t");
  fgets(new.name, 20, stdin);
  printf("Telephone number: \n\t");
  fgets(new.tel, 12, stdin);
  printf("Email: (support maximum 24 characters)\n\t");
  fgets(new.email, 25, stdin);
  return new;
}

//make a node using existing contact with next point to NULL
node_addr* makeNewNode(address addr)
{
  node_addr* new;
  new = (node_addr* )malloc(sizeof(node_addr));
  new->addr = addr;
  new->next = NULL;
  return new;
}

//print single node
void printNode(node_addr* now)
{
  if (now == NULL)
    {
      printf("Do not have this node.\n");
      return;
    }
  address tmp = now->addr;
  printf("%s\t%s\t%s %p\n", tmp.name, tmp.tel, tmp.email, now->next); 
}

//show all node
void traversingList()
{
  node_addr* tmp;
  for(tmp = root; tmp != NULL; tmp = tmp->next)
    printNode(tmp);
}

//insert after current position
//function work similar to insert typing mode. New node will appear behind curent position of cur
void insert(address person)
{
  node_addr* append = makeNewNode(person);
  if (root == NULL)
  {
    root = append;
    cur = root;
    prev = NULL;
  }
  else
    {
      append->next = cur->next;
      cur->next = append;
      prev = cur;
      cur = cur->next;
    }
}

//free list
void freeLinked()
{
  node_addr* to_free = root;
  while (to_free != NULL)
    {
      root = root->next;
      free(to_free);
      to_free = root;
    }
}

int main(int argc, char* argv[])
{
  //argc = 5, filesplit nameofOriginalFile numberOfLineInFirstFile nameofFirstFile nameofFileContainTheRest
  char fileIn[256];
  int numLine;
  char fileOut1[256], fileOut2[256];

  if (argc < 5)
    {
      printf("Not enough argument given.\nThe correct syntax:\n");
      printf("\tfilesplit nameofOriginalFile numberOfLineInFirstFile nameofFirstFile nameofFileContainTheRest\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc > 5)
    {
      printf("Too many argument given.\nThe correct syntax:\n");
      printf("\tfilesplit nameofOriginalFile numberOfLineInFirstFile nameofFirstFile nameofFileContainTheRest\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      strcpy(fileIn, argv[1]);
      numLine = atoi(argv[2]);
      strcpy(fileOut1, argv[3]);
      strcpy(fileOut2, argv[4]);
    }

  FILE* fin, * fout1, * fout2;
  //open fin for write data file
  fin = fopen(fileIn, "w+b");
  if (fin == NULL)
    {
      printf("Cannot open %s\n", fileIn);
      exit(1);
    }
  else
    {
      address mine;
      address* people;
      mine = addContact();
      root = makeNewNode(mine);
      cur = root;
      int i;
      printf("How many contact in the file (do not count yourself): ");
      scanf("%d", &num);
      getchar();
      people = (address* )malloc(num * sizeof(address));
      for (i = 0; i < num; i ++)
	{
	  people[i] = addContact();
	  insert(people[i]);
	}
      traversingList();
      fwrite(&mine, sizeof(address), 1, fin);
      fwrite(people, sizeof(address), num, fin);
      free(people);
    }
  
  fclose(fin);
  //open for filesplit
  fin = fopen(fileIn, "r+b");
  fout1 = fopen(fileOut1, "w+b");
  fout2 = fopen(fileOut2, "w+b");
  if (fin == NULL)
    {
      printf("Cannot open %s\n", fileIn);
      exit(1);
    }
  else if (fout1 == NULL)
    {
      printf("Cannot open %s\n", fileOut1);
      exit(1);
    }
  else if (fout2 == NULL)
    {
      printf("Cannot open %s\n", fileOut2);
      exit(1);
    }
  else
    {
      int irc;
      address* record;
      address* rest;
      record = (address* )malloc(numLine * sizeof(address));
      rest = (address* )malloc((num + 1 - numLine) * sizeof(address));
      irc = fread(record, sizeof(address), numLine, fin);
      printf("fread return code: %d\n", irc);
      fwrite(record, sizeof(address), numLine, fout1);
      irc = fread(rest, sizeof(address), ((num + 1) - numLine), fin);
      printf("fread return code: %d\n", irc);
      fwrite(rest, sizeof(address), ((num + 1) - numLine), fout2);
      free(record);
      free(rest);
    }
  fclose(fin);
  fclose(fout1);
  fclose(fout2);
  return 0;
}
