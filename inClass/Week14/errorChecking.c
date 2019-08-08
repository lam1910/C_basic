#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//improved ver of showHead return char
#include "stackL.h"

#define in "test.txt"

//compare 2 chars return code like strcmp (-1 when c1 < c2, 0 when c1 == c2, 1 otherwise. 
int chrcmp(elmtypeL c1, elmtypeL c2)
{
  if (c1 == c2)
    return 0;
  else if (c1 < c2)
    return -1;
  else
    return 1;
}

//find the opening (closing) bracket for an given closing (opening) one
char symmetricChar(char c)
{
  switch(c)
    {
    case '(':
      return ')'; 
    case '[':
      return ']';
    case '{':
      return '}';
    case ')':
      return '(';
    case ']':
      return '[';
    case '}':
      return '{';
    default:
      printf("Wrong input. Must be a bracket.\n"); 
    }
}

//check whether brackets are symmetrical or not return 0 if not
int bracketCheck(FILE* ins)
{
  //stack of brackets
  node* stack;
  initializeL(stack);

  char* t;
  char c = fgetc(ins);
  while (c != EOF)
    {
      printf("%c", c);
      if ((c == '(') || (c == '[') || (c == '{'))
	{
	  pushHead(stack, &c);
	}
      else if ((c == ')') || (c == ']') || (c == '}'))
	{
	  //don't have open bracket
	  if (isEmptyL(stack))
	    return 0;
	  //close bracket is not corresponding the nearest open bracket
	  else
	    {
	      t = popHead(stack);
	    }
	}
      c = fgetc(ins);
    }
  if (!isEmptyL(stack))
    return 0;
  return 1;
}

int main()
{
  //open file
  FILE* str;
  str = fopen(in, "r+");
  if (bracketCheck(str))
    printf("There is not any error in this file\n");
  else
  printf("The brackets are not symmetrical, check again!\n");
  fclose(str);
  return 0;
}
