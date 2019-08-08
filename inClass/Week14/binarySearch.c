#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct elm
{
  int key;
}element;

//swap two element
void swap(element a, element b)
{
  element tmp;
  tmp = a;
  a = b;
  b = tmp;
}

//adjust from bottom
void adjust(element list[], int root, int n)
{
  int child, rootkey;
  element tmp;
  tmp = list[root];
  rootkey = list[root].key;
  child = 2 * root;
  while (child <= n)
    {
      if ((child < n) && (list[child].key < list[child + 1].key))
	child ++;
      if (rootkey > list[child].key)
	break;
      else
	{
	  list[child / 2] = list[child];
	  child *= 2;
	}
    }
  list[child / 2] = tmp;
}

void heapSort(element list[], int n)
{
  int i, j;
  //build from bottom
  for (i = n / 2; i > 0; i --)
    adjust(list, i, n);
  for (i = n - 1; i > 0; i --)
    {
      swap(list[1], list[i + 1]);
      adjust(list, 1, i);
    }
}

//binary search element has key x 
element binSearch(element arr[], int x)
{
  
}
