#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 50
typedef int elmtype;
typedef elmtype stackType[Max];

//position that can be added new element in the near future
int top;

//make a new stack
void initialize(stackType stack)
{
  top = 0;
}

int isEmpty(stackType stack)
{
  return (top == 0);
}

int isFull(stackType stack)
{
  return (top == Max);
}

void push(elmtype elm, stackType stack)
{
  if (isFull(stack))
    printf("Stack overflow.\n");
  else
    {
      stack[top] = elm;
      top ++;
    }
}

elmtype pop(stackType stack)
{
  if (isEmpty(stack))
    printf("Stack underflow.\n");
  else
    {
      return stack[-- top];
    }
}

void showTop(stackType stack)
{
  if (isEmpty(stack))
    printf("Stack is empty.\n");
  else
    {
      int i;
      i = top - 1;
      printf("The value of top: %d.\n", stack[i]);
    }
}


int main(int argc, char* argv[])
{
  //argc = 3, addlarge stringFornum1 stringFornum2
  if (argc < 3)
    {
      printf("Not enough arguments were given. The correct syntax:\n");
      printf("\taddlarge stringFornum1 stringFornum2\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc > 3)
    {
      printf("Too many arguments were given. The correct syntax:\n");
      printf("\taddlarge stringFornum1 stringFornum2\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      int test = 0;
      int r = 0;
      stackType num1, num2;
      int i;
      int minLen = 0;
      char result[51];
      if ((strlen(argv[1]) > 50) || (strlen(argv[2]) > 50))
	{
	  printf("Too many character. The stack will be overflow.\n");
	  exit(1);
	}
      else
	{
	  printf("%s \t %s\n", argv[1], argv[2]);
	  for (i = 0; i < strlen(argv[1]); ++i)
	    {
	      if ((('a' <= argv[1][i]) && ('z' >= argv[1][i])) ||  (('A' <= argv[1][i]) && ('Z' >= argv[1][i])))
		{
		  printf("Cannot recognize the input number.\n\tAll character in the input must be number.\nExit!");
		  exit(1);
		}
	      else
		{
		  test = atoi(&argv[1][i]);
		  printf("%d", test);
		  push(test, num1);
		}
	    }
	  for (i = 0; i < strlen(argv[2]); ++i)
	    {
	      if ((('a' <= argv[2][i]) && ('z' >= argv[2][i])) ||  (('A' <= argv[2][i]) && ('Z' >= argv[2][i])))
		{
		  printf("Cannot recognize the input number.\n\tAll character in the input must be number.\nExit!");
		  exit(1);
		}
	      else
		{
		  test = atoi(&argv[2][i]);
		  push(test, num2);
		}
	    }
	  if (strlen(argv[1]) < strlen(argv[2]))
	    {
	      minLen = strlen(argv[1]);
	      for (i = 0; i < minLen; ++i)
		{
		  int Num1 = pop(num1);
		  int Num2 = pop(num2);
		  printf("%d \t %d\n", Num1, Num2);
		  if (Num1 + Num2 + r < 10)
		    {
		      char tmp = Num1 + Num2 + r + 48;
		      strcat(result, &tmp);
		      r = 0;
		    }
		  else
		    {
		      char tmp = (Num1 + Num2 + r) - 10 + 48;
		      strcat(result, &tmp);
		      r = 1;
		    }
		}
	      while (!isEmpty(num2))
		{
		  int Num2 = pop(num2);
		  if (Num2 + r < 10)
		    {
		      char tmp = Num2 + r + 48;
		      strcat(result, &tmp);
		      r = 0;
		    }
		  else
		    {
		      char tmp = (Num2 + r) - 10 + 48;
		      strcat(result, &tmp);
		      r = 1;
		    }
		}
	    }
	  else
	    {
	      minLen = strlen(argv[2]);
	      for (i = 0; i < minLen; ++i)
		{
		  int Num1 = pop(num1);
		  int Num2 = pop(num2);
		  if (Num1 + Num2 + r < 10)
		    {
		      char tmp = Num1 + Num2 + r + 48;
		      strcat(result, &tmp);
		      r = 0;
		    }
		  else
		    {
		      char tmp = (Num1 + Num2 + r) - 10 + 48;
		      strcat(result, &tmp);
		      r = 1;
		    }
		}
	      while (!isEmpty(num1))
		{
		  int Num1 = pop(num1);
		  if (Num1 + r < 10)
		    {
		      char tmp = Num1 + r + 48;
		      strcat(result, &tmp);
		      r = 0;
		    }
		  else
		    {
		      char tmp = (Num1 + r) - 10 + 48;
		      strcat(result, &tmp);
		      r = 1;
		    }
		}
	    }
	}
      printf("The result of %s + %s is %s.\n", argv[1], argv[2], result);
    }
  return 0;
}
