#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queueL.h"

//number of maximum processes that can run parallely
#define MAXPARALLEL 5

//number of maximum amount of memory can be used
#define MAXMEMORY 128

//add last
void addLast(node** p, elmtypeL id, elmtypeL value)
{
  if (p == NULL)
    {
      node* tmp = makeNewNode(id, value);
      p = &tmp;
    }
  else
    {
      node* append = makeNewNode(id, value);
      node* tmp;
      for (tmp = *p; tmp != NULL; tmp = tmp->toRear);
      append->toFront = tmp;
      tmp->toRear = append;
    }
}

//search id of node with p is the front
node* searchID(node** p, elmtypeL id)
{
  node* tmp;
  for (tmp = *p; tmp != NULL; tmp = tmp->toRear)
    {
      if (id == tmp->id)
	{
	  return tmp;
	}
    }
  return tmp->toRear;
}
int main()
{
  printf("****************\n");
  printf("Welcome!\n Recognizing your computer.........\n");
  printf("\tMaximum number of lanes for parallel process: %d.\n", MAXPARALLEL);
  printf("\tMAximum number of free memory: %d.\n\nBooting completed........\n", MAXMEMORY);
  int choice;

  //number of porcesses left
  int processL = MAXPARALLEL;
  //amount of free memory left
  int memoryL = MAXMEMORY;

  //ID of a program
  int id = 1;
  //amount of memory a program took
  int memoryT;

  //list of running processes
  node* runProc;
  
  //queue of waiting processes
  queueType* waitProc;
  

  do
    {
      printf("****************\n");
      printf("Menu:\n");
      printf("\t1: Run a new program.\n");
      printf("\t2: Status of your computer.\n");
      printf("\t3: Kill the program.\n");
      printf("\t4: Shutdown.\n");
      printf("Your Choice: ");
      scanf("%d", &choice);
      getchar();
      switch(choice)
	{
	case 1:
	  printf("Program's ID will be automatically designated.\n\tNew program's ID: %d.\n", id);
	  printf("How much memory will you assign to this program: ");
	  scanf("%d", &memoryT);
	  getchar();
	  if (memoryT > MAXMEMORY)
	    {
	      printf("This process will take too much memory. Terminating process %d.\n", id);
	      printf("Cannot assign process ID. Taking back ID(s).\n");
	    }
	  else
	    {
	      if (processL > 0)
		{
		  if (memoryT <= memoryL)
		    {
		      printf("Executing process %d.\n", id);
		      addLast(&runProc, id, memoryT);
		      memoryL -= memoryT;
		    }
		  else
		    {
		      printf("System is busy. Process %d will be put in waitng queue.\n", id);
		      enQueue(waitProc, id, memoryT);
		    }
		}
	      else
		{
		  printf("System is busy. Process %d will be put in witing queue.\n", id);
		  enQueue(waitProc, id, memoryT);
		}
	      id ++;
	    }
	  break;
	case 2:
	  printf("Type 3 to exit.\n");
	  int c;
	  node* tmp;
	  do
	    {
	      printf("What do you want to see?\n");
	      printf("\t1: Memory status.\n");
	      printf("\t2: Program running.\n");
	      printf("\t3: Nothing(exit).\n");
	      printf("\tYour choice (Type 3 to exit): ");
	      scanf("%d", &c);
	      getchar();
	      switch(c)
		{
		case 1:
		  printf("Memory already allocated to running process: %d.\n", MAXMEMORY - memoryL);
		  printf("Free memory: %d.\n", memoryL);
		  if (memoryL <= 10)
		    printf("Low memory. Killing some unnecessary process is recommended.\n");
		  else if (memoryL == 0)
		    printf("Memory is full. Killing some process is strongly recommended.\n");
		  else
		    printf("System is healthy. Nothing important regarding memory status.\n"); 
		  break;
		case 2:
		  printf("\tPrograms are running in the system.\n");
		  if (runProc == NULL)
		    printf("Empty. There is nothing running in your system.\n");
		  else
		    {
		      printf("\tID\t\tMemory\n");
		      for (tmp = runProc; tmp != NULL; tmp = tmp->toRear)
			{
			  printf("%10.4d\t%d\n", tmp->id, tmp->data);
			}
		      printf("End of running list.\n");
		    }
		  printf("\tNext in line.\n");
		  tmp = waitProc->Front;
		  printf("\tID\t\tMemory\n");
		  printf("%10.4d\t%d\n", tmp->id, tmp->data);
		  break;
		case 3:
		  printf("Main menu will appear shortly.\n");
		  break;
		default:
		  printf("Cannot recognize that function.\nTry entering number from 1 to 3 next time. The status menu will be shown again.\n");
		  break;
		}
	    }while (c != 3);
	  break;
	case 3:
	  printf("\tPrograms are running in the system.\n");
	  node* m;
	  int sel;
	  if (runProc == NULL)
	    printf("Empty. There is nothing running in your system.\n");
	  else
	    {
	      printf("\tID\t\tMemory\n");
	      for (tmp = runProc; tmp != NULL; tmp = tmp->toRear)
		{
		  printf("%10.4d\t%d\n", tmp->id, tmp->data);
		}
	      printf("End of running list.\n");
	      printf("Which program you want to kill (type in program ID): ");
	      scanf("%d", &sel);
	      getchar();
	      m = searchID(&runProc, sel);
	      if (m == NULL)
		printf("Do not have this program or it is not running.\n");
	      else if (m->toFront == NULL)
		{
		  runProc = runProc->toRear;
		  runProc->toFront = NULL;
		  m->toRear = NULL;
		  memoryL += m->data;
		  free(m);
		  printf("Process %d killed.\n", sel);
		}
	      else if (m->toRear == NULL)
		{
		  m->toFront->toRear = NULL;
		  m->toFront = NULL;
		  memoryL += m->data;
		  free(m);
		  printf("Process %d killed.\n", sel);
		}
	      else
		{
		  m->toFront->toRear = m->toRear;
		  m->toRear->toFront = m->toFront;
		  m->toFront = NULL;
		  m->toRear = NULL;
		  memoryL += m->data;
		  free(m);
		  printf("Process %d killed.\n", sel);
		}
	    }
	  tmp = waitProc->Front;
	  if (tmp->data <= memoryL)
	    {
	      node* append = deQueue(waitProc);
	      addLast(&runProc, append->id, append->data);
	    }
	  break;
	case 4:
	  printf("Goodbye. See you next time.\n");
	  break;
	default:
	  printf("Cannot recognize that function.\nTry entering number from 1 to 4 next time. The menu will be shown again.\n\n");
	  break;
	}
    }while(choice != 4);
  return 0;
}
