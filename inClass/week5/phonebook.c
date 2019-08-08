#include <stdio.h>
#include <stdlib.h>

enum {SUCCESS, FAIL, MAX_ELEMENT = 20};

typedef struct phoneaddress_t
{
  char name[20];
  char tel[11];
  char email[25];
}phoneaddress;


int main(void)
{
  FILE* fp;
  phoneaddress phonearr[MAX_ELEMENT];
  int i, n, irc;
  int reveal = SUCCESS;
  
  fp = fopen("testphone.txt", "w");

  if (fp == NULL)
    {
      printf("Cannot open the file!\n");
      reveal = FAIL;
    }
  else
    {
      printf("How many (<20)? ");
      scanf("%d", &n);
      for (i = 0; i < n; i++)
	{
	  printf("Name: \n");
	  scanf("%s", phonearr[i].name);
	  printf("Telephone Number: \n");
	  scanf("%s", phonearr[i].tel);
	  printf("Email: \n");
	  scanf("%s", phonearr[i].email);
	  
	}
      irc = fwrite(phonearr, sizeof(phoneaddress), n, fp);
      
      printf("fwrite return code = %d\n", irc);
      fclose(fp);
    }

  fp = fopen("testphone.txt", "r");
  
  if (fp == NULL)
    {
      printf("Cannot open the file!\n");
      reveal = FAIL;
      exit(1);
    }
  else
    {
      irc = fread(phonearr, sizeof(phoneaddress), n, fp);
      printf("fread return code = %d\n", irc);
      for(i = 0; i < n; i ++)
	{
	  printf("%s-", phonearr[i].name);
	  printf("%s-", phonearr[i].tel);
	  printf("%s-", phonearr[i].email);
	}
      fclose(fp);
    }
  return reveal;
}
  
