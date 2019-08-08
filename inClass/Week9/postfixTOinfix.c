#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackL.h"
//each number has 1 digit
#define space ' '
int main(int argc, char* argv[])
{
  //posteval expression
  if (argc > 2)
    {
      printf("Too much arguments were given. The correct syntax:\n");
      printf("\tposteval expression\n");
      printf("Exit now!");
      exit(1);
    }
  else if (argc < 2)
    {
      printf("Not enough arguments were given. The correct syntax:\n");
      printf("\tposteval expression\n");
      printf("Exit now!");
      exit(1);
    }
  else
    {
      node* stack;
      initializeL(stack);
      char c;
      int len = strlen(argv[1]);
      for(int i = 0; i < len; ++i)
	{
	  strncpy(&c, &argv[1][i], 1);
	  if (('0' <= c) && (c <= '9'))
	    {
	      pushHead(stack, &c);
	    }
	  else if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
	    {
	      int b = popHead(stack);
	      int a = popHead(stack);
	      double result;
	      if ((b == -1) || (a == -1))
		{
		  printf("Expression is wrong.\n");
		  exit(1);
		}
	      else
		{
		  switch(c)
		    {
		    case '+':
		      result = a + b;
		      break;
		    case '-':
		      result = a - b;
		      break;
		    case '*':
		      result = a * b;
		      break;
		    default:
		      result = a / b;
		      break;
		    }
		  pushHead(stack, &result);
		}
	    }
	}
      int final = popHead(stack);
      printf("%d.\n", final);
    }
  return 0;
}
