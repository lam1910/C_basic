#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 200000

typedef struct elm
{
  int key;
}element;

void swap(element* a, element* b)
{
  element tmp = *a;
  *a = *b;
  *b = tmp;
}

void quickSort(element list[], int left, int right)
{
  int pivot, i, j;
  element tmp;
  if (left < right)
    {
      i = left;
      j = right + 1;
      pivot = list[left].key;
      do
	{
	  do i ++; while (list[i].key < pivot);
	  do j --; while (list[j].key > pivot);
	  if (i < j)
	    swap(&list[i], &list[j]);
	}while (i < j);
      swap(&list[left], &list[j]);
      quickSort(list, left, j - 1);
      quickSort(list, j + 1, right);
    }
}



//reset the elements of an array
void reset(element a[])
{
  int i;
  int r;
  for (i = 0; i < LEN; ++i)
    {
      r = rand() % 5000000;
      a[i].key = r;
    }
}

//print n elements
void printArray(element a[], int n)
{
  int i;
  if (n > LEN)
    {
      printf("Out of Range!\n");
    }
  else
    {
      for (i = 0; i < n; ++i)
	printf("%d\t", a[i].key);
      printf("\n");
    }
}

int main()
{
  element arr[LEN];
  reset(arr);
  printArray(arr, LEN);
  clock_t begin = clock();
  quickSort(arr, 0, LEN);
  clock_t end = clock();
  printf("\n\nArray after sorted: \n");
  printArray(arr, LEN);
  printf("Time Execution: %lf.\n", (double)(end - begin) / CLOCKS_PER_SEC);
  return 0;
}
