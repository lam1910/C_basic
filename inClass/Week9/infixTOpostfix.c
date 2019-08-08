#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackL.h"

//assume that all number has just 1 number

int main()
{
  char exp[100], result[100];
  printf("What is your infix expression: ");
  fgets(exp, 99, stdin);
  node* stack;
  initializeL(stack);
  int len = strlen(exp);
  for (int i = 0; i < len; ++i)
    {
      if (('0' <= exp[i]) || (exp[i] <= '9'))
	{
	  strcat(result, &exp[i]);
	}
      if ((exp[i] == '+') || (exp[i] == '-'))
	{
	  while(!isEmptyL())
	}
    }
  return 0;
}
