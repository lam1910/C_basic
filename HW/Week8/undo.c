#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//for int stack
#include "stackA.h"
//for monory stack
#include "stackL.h"

//convert from int to string
char* convertToStr(int num)
{
  char *result;
  result = (char *)malloc(7 * sizeof(char));
  sprintf(result, "%d", num);
  return result;
}

int main()
{
  int choice;
  int val;
  int reVal;
  //declare the int stack
  stackType numList;
  initialize(numList);

  //declare the memory stack
  node* undoList;
  initializeL(undoList);
  
  do
    {
      printf("Remember: While the number stack can only hold at most 50 numbers, the undo operation can take you to wherever you want, but it is not advised to do more than 49 undoes in the row.\n");
      printf("****************\nMenu:\n");
      printf("\t1: Adding new integer.\n");
      printf("\t2: Peaking at the top element.\n");
      printf("\t3: Taking the top element.\n");
      printf("\t4: Undo.\n");
      printf("\t5: Quit.\n");
      printf("\t\tYour choice: ");
      scanf("%d", &choice);
      getchar();
      switch(choice)
	{
	case 1:
	  if (!isFull(numList))
	    {
	      printf("What number would you like to be added to the list: ");
	      scanf("%d", &val);
	      push(val, numList);
	      //'P' for push
	      pushHead(undoList, "P");
	    }
	  else
	    {
	      printf("Stack is full. Suggest to take a litle numbers of integer out or undo.\n");
	    }
	  break;
	case 2:
	  printf("This option does not affect the content of the stack.\n");
	  showTop(numList);
	  break;
	case 3:
	  if (!isEmpty(numList))
	    {
	      reVal = pop(numList);
	      printf("The number has been popped out: %d.\n", reVal);
	      //'p' for pop
	      char p[10];
	      strcat(p, "p");
	      pushHead(undoList, p);
	    }
	  else
	    {
	      printf("Stack is empty. Suggest to add some numbers of integer in or undo.\n");
	    }
	  break;
	case 4:
	  printf("Will begin to undo last action. \n");
	  char un[10];
	  strcpy(un, popHead(undoList));
	  printf("%s.\n", un);
	  if (strcmp(un,"P") == 0)
	    {
	      int i = pop(numList);
	      printf("Undo completed. New top:\n");
	      showTop(numList);
	    }
	  else
	    {
	      push(reVal, numList);
	      printf("Undo completed. New top:\n");
	      showTop(numList);
	    }
	  break;
	case 5:
	  printf("Thank you for chossing us. Good bye!\n");
	  break;
	default:
	  printf("Do not have that operation. It is advised that you follow the instructions. The menu will show again.\n");
	  break;
	}
    }while (choice != 5);
  return 0;
}
