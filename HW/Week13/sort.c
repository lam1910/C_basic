#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 200000
//create a structure to work
typedef struct elm
{
  int key;
}element;

//reset the array
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

//selection sort of array a of n elements element
void selectSort(element arr[], int n)
{
  clock_t begin = clock();
  int i, j, min;
  element tmp;
  for (i = 0; i < n - 1; i ++)
    {
      min = i;
      for (j = i + 1; j <= n - 1; j++)
	if (arr[j].key < arr[min].key)
	  min = j;
      tmp = arr[i];
      arr[i] = arr[min];
      arr[min] = tmp;
    }
  clock_t end = clock();
  printf("Array after sorted:\n");
  printArray(arr, n);
  printf("Time Execution: %lf second(s)\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

//insertion sort of array a of n elements element
void insertSort(element arr[], int n)
{
  clock_t begin = clock();
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
  clock_t end = clock();
  printf("Array after sorted:\n");
  printArray(arr, n);
  printf("Time Execution: %lf second(s)\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

//bubble sort of array a of n elements element
void bubbleSort(element arr[], int n)
{
  clock_t begin = clock();
  int i, j;
  element tmp;
  for (i = 0; i < n-1; i++)               
    for (j = 0; j < n-i-1; j++) 
      if (arr[j].key > arr[j+1].key)
	{
	  tmp = arr[j];
	  arr[j] = arr[j + 1];
	  arr[j + 1] = tmp; 
	}
  clock_t end = clock();
  printf("Array after sorted:\n");
  printArray(arr, n);
  printf("Time Execution: %lf second(s)\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

void Heapify(element A[], int k)
{
  int heapSize = LEN - 1;
  int l = 2 * k + 1;
  int r = 2 * k + 2;
  int largest;

  if(l <= heapSize && A[l].key > A[k].key)
    largest = l;
  else
    largest = k;
  if(r <= heapSize && A[r].key > A[largest].key)
    largest = r;
  if(largest != k)
    {
      int tmp = A[k].key;
      A[k].key = A[largest].key;
      A[largest].key = tmp;
      Heapify(A, largest);
    }
}

void BuildHeap(element* A)
{
  int heapSize = LEN - 1;
  int i;
  for(i = heapSize / 2; i >= 0; i--)
    Heapify(A, i);
}

//heap sort of array a of n elements element
void heapSort(element* a, int n)
{
  clock_t begin = clock();
  int heapSize = n - 1;
  BuildHeap(a);
  int i;
  for (i = heapSize; i >= 0; i --)
    {
      element tmp = a[heapSize];
      a[heapSize] = a[0];
      a[0] = tmp;
      heapSize --;
      Heapify(a, 0);
    }
  clock_t end = clock();
  printf("Array after sorted:\n");
  printArray(a, n);
  printf("Time Execution: %lf second(s)\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

int main()
{
  element arr[LEN];
  element tmp[20000];
  srand(time(NULL));
  char c;
  printf("\n____________________\n\n");
  printf("Starting........Taking initial array of number........Done!\n");
  reset(arr);
  printArray(arr, LEN);
  int choice, i;
  do
    {
      printf("____________________\n\n");
      printf("Menu:\n");
      printf("\t1: Reset data.\n");
      printf("\t2: Insertion sort.\n");
      printf("\t3: Selection sort.\n");
      printf("\t4: Bubble sort.\n");
      printf("\t5: Heap sort.\n");
      printf("\t6: Exit.\n");
      printf("Your choice: ");
      scanf("%d", &choice);
      getchar();
      switch (choice)
	{
	case 1:
	  reset(arr);
	  printArray(arr, LEN);
	  break;
	case 2:
	  printf("Will take too much time sort all %d elements. Suggest cutting the number of elements to 200000. Proceed?(Type y or Y to proceed):", LEN);
	  scanf("%c", &c);
	  getchar();	  
	  if ((c == 'y') && (c == 'Y'))
	    {
	      for (i = 0; i < 20000; ++i)
		tmp[i].key = arr[i].key;
	      insertSort(tmp, 20000);
	    }
	  else
	    insertSort(arr, LEN);
	  break;
	case 3:
	  printf("Will take too much time sort all %d elements. Suggest cutting the number of elements to 200000. Proceed?(Type y or Y to proceed):", LEN);
	  scanf("%c", &c);
	  getchar();	  
	  if ((c == 'y') && (c == 'Y'))
	    {
	      for (i = 0; i < 20000; ++i)
	        tmp[i].key = arr[i].key;;
	      selectSort(tmp, 20000);
	    }
	  else
	    selectSort(arr, LEN);
	  break;
	case 4:
	  printf("Will take too much time sort all %d elements. Suggest cutting the number of elements to 200000. Proceed?(Type y or Y to proceed):", LEN);
	  scanf("%c", &c);
	  getchar();	  
	  if ((c == 'y') && (c == 'Y'))
	    {
	      for (i = 0; i < 20000; ++i)
		tmp[i].key = arr[i].key;;
	      bubbleSort(tmp, 20000);
	    }
	  else
	    bubbleSort(arr, LEN);
	  break;
	case 5:
	  heapSort(arr, LEN);
	  break;
	case 6:
	  printf("Goodbye. See you again!\n");
	  break;
	default:
	  printf("Wrong command. Please choose the number between 1 and 6.\nThe menu will be shown again.");
	  break;
	}
      printf("\n\n");
    }while (choice != 6);
  return 0;
}
