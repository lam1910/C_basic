#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cursedWord
{
  char word[20];
  int size;
  struct cursedWord* next;
}cursedWord_L;
typedef cursedWord_L* cursedWord_LPtr;
void addToList(cursedWord_LPtr* hd, int size)
{
  char word[20];
  cursedWord_LPtr ptr = (cursedWord_LPtr) malloc (sizeof(cursedWord_L));
  printf("Enter your word here: ");
  scanf("%s", word);
  strcpy(ptr->word, word);
  ptr->size = size;
  if (*hd == NULL)
    ptr->next = NULL;
  else
    ptr->next = *hd;
  *hd = ptr;
}
  
char *replace(const char *s, const char *repl) //replace a char in s with length len with repl
{
  size_t rlen = strlen(repl);
  char *res = malloc(strlen(s) + (rlen - 1) * strlen(s) + 1);
  char *ptr = res;
  const char *t;
  for(t = s; *t; t++)
   {
     memcpy(ptr, repl, rlen);
     ptr += rlen;
   }
   *ptr = 0;
   return res;
}

void detectBadWord(cursedWord_LPtr hd, char* word, char* repl)
{
  cursedWord_LPtr ptr = hd;
  while(ptr != NULL)
    {
      if(strcmp(ptr->word, word) != 0)
	{
	  word = replace(word, repl);
	}
    }
  free(word);
 }
  
int main(int argc, char *argv[])
{
  char filename[100];
  char rep;
  if (argc < 3)
    {
      printf("Not enough arguments. Exit!");
      exit(1);
    }
  else if (argc > 3)
    {
      printf("Too many arguments. Exit!");
      exit(1);
    }
  else
    {
      strcpy(filename,  argv[1]);
      strcpy(rep, argv[2]);
    }

  cursedWord_LPtr list;
  int size;
  printf("How many words ar there in your blacklist?");
  scanf("%d", &size);
  do
    {
      printf("The size of your black list cannot be negative. Enter a positive integer.\n");
      printf("How many words ar there in your blacklist?");
      scanf("%d", &size);
    }while (size < 0);
  addToList(list, size); 
  FILE * fp; 
  fp = fopen (filename, "a");
  if(fp == NULL)
    {
      perror("Error in opening file");
      return(-1);
    }
  char *e;
  e = (char *)malloc(20 * sizeof(char));
  int n = 1;
  do
    {
      char c = fgetc(fp);
      if(feof(fp))
	{
          break ;
        }
      else if (c != ' ')
	{
	  n ++;
 	}
      else if (c == ' ')
	{
	  fgets(e, n, fp);
	  detectBadWord(list, e, rep);
	  n = 1;
	}
    } while(1);
      free(e);
      fclose(fp);
      return 0;
 }
