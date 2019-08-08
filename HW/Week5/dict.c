#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 80
#define in "VNDict.txt"
#define out "VNDict.dat"
#define DIV ':'

typedef struct word
{
  char vietW[MAX_LEN];
  char trans[MAX_LEN];
}dict;

dict line(FILE* ptr)
{
  dict ph;
  char *line = (char *)malloc(MAX_LEN * sizeof(char));
  if (line == NULL)
    {
      printf("Memory allocation failed\n");
      strcpy(ph.trans, "|");
      return ph;
    }
  if (fgets(line, MAX_LEN, ptr) == NULL)
    {
      strcpy(ph.trans, "|");
      return ph;
    }
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, DIV)) != NULL)
    {
      *p_end = '\0';

      // get vietW from the string p_start
      strcpy(ph.vietW, p_start);
      p_start = p_end + 1;
  }
  //work with p_start
  *(p_start + strlen(p_start) - 1) = '\0';
  strcpy(ph.trans, p_start);

  //done
  free(line);
  return ph;
}

int main(int argc, char* argv[])
{
  // argc == 3, *argv[1] is starting position(line), *argv[2] is ending position(line)
  int start, end;

  if (argc < 3)
    {
      printf("Not enough arguments. Please enter starting position (line) and ending position (line) respectively.\nExit!\n");
      exit(1);
    }
  else if (argc > 3)
    {
      printf("Too many arguments. Please enter starting position (line) and ending position (line) respectively.\nExit!\n");
      exit(1);
    }
  else
    {
      start = atoi(argv[1]);
      end = atoi(argv[2]);
      if (start > end)
	{
	  printf("Wrong input type. Starting position must be less than ending position.\n");
	  exit(1);
	}
    }

  int irc, i;                   //irc return code for fread and fwrite
  //open file
  FILE* fin;
  FILE* fout;

  fin = fopen(in, "r");
  fout = fopen(out, "w+b");

  if (fin == NULL)
    {
      printf("Cannot open %s.\n", in);
      exit(1);
    }
  else if (fout == NULL)
    {
      printf("Cannot open %s.\n", out);
      exit(1);
    }
  else
    {
      printf("We are now transfer the cotain from line %d to line %d to binary form\n", start, end);
      int n = end - start + 1;
      int l;
      dict* list;
      list = (dict* )malloc(n * sizeof(dict));
      irc = fread(list, sizeof(dict), n, fin);
      
      //close in file
      fclose(fin);

      //change to .dat
      irc = fwrite(list, sizeof(dict), n, fout);
      printf("fwrite return code = %d\n", irc);
      printf("Done. %s is created.\n", out);
      //close out file
      fclose(fout);

      //free list
      free(list);
    }
  
  
  return 0;
}
