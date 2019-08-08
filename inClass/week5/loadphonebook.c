#include <stdio.h>
#include <stdlib.h>

enum {SUCCESS, FAIL, MAX_ELEMENT = 20};

typedef struct phoneaddress_t
{
  char name[20];
  char tel[11];
  char email[25];
}phoneaddress;

int main()
{
  FILE* fp;
  phoneaddress *phonearr;
  int i, n, irc;
  int reveal = SUCCESS;
  printf("Read data from second to third element.\n");
  
  fp = fopen("testphone.dat", "r+b");

  if (fp == NULL)
    {
      printf("Cannot open the file!\n");
      reveal = FAIL;
    }
  phonearr = (phoneaddress* )malloc(2 * sizeof(phoneaddress));
  if (phonearr == NULL)
    {
      printf("Memory allocation failed!\n");
      return FAIL;
    }
  if (fseek(fp, 1 * sizeof(phoneaddress), SEEK_SET) != 0)
    {
      printf("Fseek failed!\n");
      return FAIL;
    }
  irc =fread(phonearr, sizeof(phoneaddress), 2, fp);

  for (i = 0; i < 2; i ++)
    {
      printf("%s-",phonearr[i].name);
      printf("%s-",phonearr[i].tel);
      printf("%s/n",phonearr[i].email);
    }
  // modfying data
  strcpy(phonearr[1].name, "Lan Hoa");
  strcpy(phonearr[1].tel, "0344466");
  strcpy(phonearr[1].email, "yu.rt@gmail.com");
  fseek (fp, 1*sizeof(phoneaddress), SEEK_SET);
  irc = fwrite(phonearr, sizeof(phoneaddress), 2, fp);
  printf("Fwrite return code = %d\n", irc);
  fclose(fp);
  free(phonearr);
  return reveal;
}
  
