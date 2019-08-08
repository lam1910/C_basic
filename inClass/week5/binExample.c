#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 80

void blockReadWrite(FILE* in, FILE* out)
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
}
int main()
{
  char fin[] = "lab1.txt";
  char fout[] = "lab1a.txt";

  FILE* fp1;
  fp1 = fopen(fin, "r");
  FILE* fp2;
  fp2 = fopen(fout, "w");

  blockReadWrite(fp1, fp2);

  fclose(fp1);
  fclose(fp2);
  return 0;
}
