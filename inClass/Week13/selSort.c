#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct elm
{
  int key;
}element;

void selectSort(element a[], int n)
{
  int i, j, min;
  element tmp;
  for (i = 0; i < n - 1; i ++)
    {
      min = i;
      for (j = i + 1; j <= n - 1; j++)
	if (a[j].key < a[min].key)
	  min = j;
      tmp = a[i];
      a[i] = a[min];
      a[min] = tmp;
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
      int r = rand() % 500000;
      arr[i].key = r;
    }
  for (i = 0; i < len; i++)
    printf("%d\t", arr[i].key);
  printf("\n");
  clock_t begin = clock();
  selectSort(arr, len);
  clock_t end = clock();
  printf("New list: ");
  for (i = 0; i < len; i++)
    printf("%d\t", arr[i].key);
  printf("\n");
  printf("Time execution: %lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
  return 0;
}
