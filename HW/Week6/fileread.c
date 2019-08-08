#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct for content
typedef struct address_t
{
  char name[20];
  char tel[12];
  char email[25];
}address;

int main(int argc, char* argv[])
{
  //argc = 2, fileread nameofFile
  char fileIn[256];
  
  if (argc > 2)
    {
      printf("Too many argument given.\nThe correct syntax:\n");
      printf("\tfileread nameofFile\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc < 2)
    {
      printf("Not enough argument given.\nThe correct syntax:\n");
      printf("\tfileread nameofFile\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      strcpy(fileIn, argv[1]);
    }

  //open file for read
  FILE* fin;
  address person;
  fin = fopen(fileIn, "r+b");
  printf("Content of the file %s.\n", fileIn);
  while (1)
  {
    if (feof(fin))
      break;
    fread(&person, sizeof(address), 1, fin);
    printf("%s\t%s\t%s\n", person.name, person.tel, person.email);
  }
  printf("End of File.\n");
  return 0;
}


