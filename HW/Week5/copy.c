#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {SUCCESS, FAIL, MAX_LEN = 80};

void characterReadWrite(FILE* in, FILE* out)//function number 1
{
  clock_t begin = clock();

  char c;
  c = fgetc(in);
  while (c != EOF)
    {
      fputc(c, out);
      c = fgetc(in);
    }
  printf("Character copy is completed. Output file ready to be open!\n");
  
  clock_t end = clock();
  double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent on operation: %lf second.\n", timeSpent);
}

void lineReadWrite(FILE* in, FILE* out) // function number 2
{
  clock_t begin = clock();
  
  char line[MAX_LEN];
  while (fgets(line, sizeof(line), in) != NULL)
    {
      fputs(line, out);
    }
  printf("Line copy is completed. Output file ready to be open!\n");

  clock_t end = clock();
  double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent on operation: %lf second.\n", timeSpent);
}
void blockReadWrite(FILE* in, FILE* out)// function number 3
{
  clock_t begin = clock();
  
  int num, mem;
  char* buff;

  printf("Block size or number of member you wish to copy in 1 go: ");
  scanf("%d", &mem);                                     //enter block size
  while (mem < 0 || mem > 80)                            //handle wrong input
    {
      printf("Block size must be between 1 and 80.\n");
      printf("Block size or numbers of member you wish to copy in 1 go: ");
      scanf("%d", &mem);
    }
  buff = (char* )malloc((mem + 1) * sizeof(char));       //allocate memory
  while (!feof(in))
    {
      num = fread(buff, sizeof(char), mem, in);    
      buff[mem * sizeof(char)] = '\0';
      fwrite(buff, sizeof(char), num, out);
    }
  printf("Block copy is completed. Output file ready to be open!\n");
  free(buff);

  clock_t end = clock();
  double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent on operation: %lf second.\n", timeSpent);
}

int main(int argc, char* argv[])
{
  char fin[256], fout[256];

  if (argc < 3)
    {
      printf("Not enough arguments. Please enter filename or direction for the original file and destination file respectively.\nExit!\n");
      exit(1);
    }
  else if (argc > 3)
    {
      printf("Too many arguments. Please enter filename or direction for the original file and destination file respectively.\nExit!\n");
      exit(1);
    }
  else
    {
      strcpy(fin,  argv[1]);
      strcpy(fout, argv[2]);
    }

  FILE* in;
  FILE* out;
  int reveal = SUCCESS;
  
  in = fopen(fin, "r+");
  out = fopen(fout, "w+"); 

  if (in == NULL)
    {
      printf("Cannot open %s!\n", fin);
      reveal = FAIL;
    }
  else if (out == NULL)
    {
      printf("Cannot open %s!\n", fout);
      reveal = FAIL;
    }
  else
    {
      int choice;
      do
	{
	  printf("Choose your preference mode of copy.\n");
	  printf("\t1: Character Copy.\n\t2: Line Copy.\n\t3: Block Copy with user-defined block size.\n");
	  printf("Your choice: ");
	  scanf("%d", &choice);
	  switch(choice)
	    {
	    case 1:
	      characterReadWrite(in, out);
	      break;
	    case 2:
	      lineReadWrite(in, out);
	      break;
	    case 3:
	      blockReadWrite(in, out);
	      break;
	    default:
	      printf("Wrong input. Choice must be between 1 and 3. The menu wil be shown again.\n");
	      break;
	    }
	}while ((choice <= 0) || (choice >= 4));
    }

  fclose(in);                            //close file in
  fclose(out);                           //close file out
  return reveal;
}
