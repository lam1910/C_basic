#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct elm
{
  int key;
}element;

void insertSort(element arr[], int n)
{
  int i = 1;
  int j = 0;
  element next;
  for (i = 1; i < n; i ++)
    {
      next = arr[i];
      for (j = i - 1; (j >= 0) && (next.key < arr[j].key); j --)
	  arr[j + 1] = arr[j];
      arr[j + 1] = next;
    }
}

int main()
{
  element arr[200000];
  int len = 200000;
  int i;
  srand(time(NULL));
  for (i = 0; i < len; i++)
    {
      int r = rand() % 1000000;
      arr[i].key = r;
    }
  for (i = 0; i < len; i++)
    printf("%d\t", arr[i].key);
  printf("\n");
  clock_t begin = clock();
  insertSort(arr, len);
  clock_t end = clock();
  printf("New list: ");
  for (i = 0; i < len; i++)
    printf("%d\t", arr[i].key);
  printf("\n");
  printf("Time execution: %lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
  return 0;
}
