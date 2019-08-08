#include <stdio.h>

enum{SUCCESS, FAIL};

int blockReadWrite(FILE* in, FILE* out)
{
  int num;
  char buff[MAX_LEN + 1];
  while (!feof(in))
    {
      num = fread(buff, sizeof(char), MAX_LEN, in);    
      buff[num *sizeof(char)] = '\0';
      printf("%s", buff);
      fwrite(buff, sizeof(char), num, out);
    }
  return num;
}

int main()
{
  char filename[1000];
  int reveal = SUCCESS;
  printf("Enter your file name: \n");
  gets(filename);

  FILE* fp;
  FILE* temp;
  
  fp = fopen(filename, "a+");
  temp = fopen("temp.dat", "w+b");
  
  if (fp == NULL)
    {
      printf("Cannot open file %s", filename);
      reveal = FAIL;
    }
  int size = blockReadWrite(fp, temp);
  fseek(fp, 0, SEEK_SET);
  
  
  fclose(fp);
  fclose(temp);
  return reveal;
}
