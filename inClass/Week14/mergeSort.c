#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define threshold 500

typedef struct elm
{
  int key;
}element;

//insertion sort for n < threshold
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

//split array a into to subarrays
void splitArray(element a[], int n, element out1[], element out2[])
{
  int i = (n / 2) + 1, j;
  for (j = 0; j < n; j ++)
    {
      if (j < i)
	out1[j].key = a[j].key;
      else
	out2[j].key = a[j].key;
    }
}

//merge sort an array a of n elements
void mergeSort(element a[], int n)
{
  int g = (n / 2) + 1;
  element e[g];
  element v[n - g];
  if (n < threshold)
    insertSort(a, n);
  else
    {
      splitArray(a, n, e, v); 
    }
}
