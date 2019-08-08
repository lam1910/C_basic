#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//number of contacts
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
  //argc = 4, filemerge nameofFirstFile nameofSecondFile nameofOutFile
  char fileIn1[256], fileIn2[256], fileOut[256];

  if (argc < 4)
    {
      printf("Not enough argument given.\nThe correct syntax:\n");
      printf("\tfilemerge nameofFirstFile nameofSecondFile nameofOutFile\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc > 4)
    {
      printf("Too many argument given.\nThe correct syntax:\n");
      printf("\tfilemerge nameofFirstFile nameofSecondFile nameofOutFile\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      strcpy(fileIn1, argv[1]);
      strcpy(fileIn2, argv[2]);
      strcpy(fileOut, argv[3]);
      printf("Names of 2 input files and an output files is noted.\nRemember this program only merge file, we do not input anything here. If you want to write data to the file, run \"filesplit nameofOriginalFile numberOfLineInFirstFile nameofFirstFile nameofFileContainTheRest\" or enter data in file your self.\n");
    }
  FILE* fin1, * fin2, * fout;
  //open for filemerge
  fin1 = fopen(fileIn1, "r+b");
  fin2 = fopen(fileIn2, "r+b");
  fout = fopen(fileOut, "w+b");

  if (fin1 == NULL)
    {
      printf("Cannot open %s. Check your filename(path).\n", fileIn1);
      exit(1);
    }
  else if (fin2 == NULL)
    {
      printf("Cannot open %s. Check your filename(path).\n", fileIn2);
      exit(1);
    }
  else if (fout == NULL)
    {
      printf("Cannot open %s. Check your permission to create file in the path entered here.\n", fileOut);
      exit(1);
    }
  else
    {
      address list1, list2;
      
      //read data in fin1
      while (1)
	{
	  if (feof(fin1))
	    break;
	  fread(&list1, sizeof(address), 1, fin1);
	  fwrite(&list1, sizeof(address), 1, fout);
	}
      
      //read data in fin2
      while (1)
	{
	  if (feof(fin2))
	    break;
	  fread(&list2, sizeof(address), 1, fin2);
	  fwrite(&list2, sizeof(address), 1, fout);
	}
      
      printf("%s created at binary form. Run \"fileread\" to see result.\n", fileOut);

    }
   //close file pointer
   fclose(fin1);
   fclose(fin2);
   fclose(fout);
  return 0;
}
