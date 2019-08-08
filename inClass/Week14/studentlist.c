#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define file "list.txt"
#define MAX_LEN 80
#define numS 32
#define sp ' '

typedef struct std
{
  char fullname[MAX_LEN];
  char name[30];
  char middlename[30];
}student;

student name[numS];

//compare names
int namecmp(student a, student b);
void swap(student* a, student* b)
{
  student tmp = *a;
  *a = *b;
  *b = tmp;
}

void heapify(student arr[], int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && namecmp(arr[l],  arr[largest]) == 1)
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && namecmp(arr[r], arr[largest]) == 1)
        largest = r;
 
    // If largest is not root
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
 
// main function to do heap sort
void heapSort(student arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--)
    {
        // Move current root to end
        swap(&arr[0], &arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
 
/* A utility function to print array of size n */
void printArray(student arr[], int n)
{
    for (int i=0; i<n; ++i)
      printf("%s\n", arr[i].fullname);
    printf("\n");
}

//get sub string
char* subString(char *string, int start, int endstr)
{
    int c, length;
    length = endstr-start+1;
    char *pointer = (char*)malloc(sizeof(char)*(length+1));

    for (c = 0 ; c < start ; c++)
        string++;

    for (c = 0 ; c < length; c++){
        *(pointer+c) = *string;
        string++;
    }
    *(pointer+c)= '\0';
    return pointer;
}

//get name
char* getName(char* fullName)
{
    char* name;
    int i, n = strlen(fullName);
    for(i = n - 1; i > 0; i--)
      {
        if(fullName[i] == sp)
	  {
	    name = (subString(fullName, i+1, n-1));
	    break;
	  }
      }
    return name;
}

//get middle name
char* getMiddleName(char* fullname)
{
  char* middle;
  int i, m, n = strlen(fullname);
  for(i = n - 1; i > 0; i--)
      {
        if(fullname[i] == sp)
	  {
	    m = i;
	    break;
	  }
      }
  for (i = 0; i < n; i++)
    {
      if(fullname[i] == sp)
	  {
	    middle = (subString(fullname, i + 1, m - 1));
	    break;
	  }
    }
  return middle;
}

//read data
void lineRead(FILE* ptr)
{
  char line[MAX_LEN];
  int i = 0;
  while (fgets(line, sizeof(line), ptr) != NULL)
    {
      strcpy(name[i].fullname, line);
      strcpy(name[i].name, getName(line));
      strcpy(name[i].middlename, getMiddleName(line));
      i ++;
    }
}


//compare two name
int namecmp(student a, student b)
{
  if (strcmp(a.name, b.name) > 0)
    return 1;
  else if (strcmp(a.name, b.name) < 0)
    return -1;
  else
    if (strcmp(a.middlename, b.middlename) > 0)
      return 1;
    else if (strcmp(a.middlename, b.middlename) < 0)
      return -1;
    else
      if (strcmp(a.fullname, b.fullname) > 0)
	return 1;
      else if (strcmp(a.fullname, b.fullname) < 0)
	return -1;
      else
	return 0;
}

//quick sort from left to right
void quickSort(student list[], int left, int right)
{
  int i, j;
  student pivot;
  if (left < right)
    {
      i = left;
      j = right + 1;
      pivot = list[left];
      do
	{
	  do i ++; while (namecmp(list[i], pivot) < 0);
	  do j --; while (namecmp(list[j],  pivot) > 0);
	  if (i < j)
	    swap(&list[i], &list[j]);
	}while (i < j);
      swap(&list[left], &list[j]);
      quickSort(list, left, j - 1);
      quickSort(list, j + 1, right);
    }
}

int main()
{
  FILE* in;
  int i;
  in = fopen(file, "r+");
  if (in == NULL)
    {
      printf("Cannot open %s. Check file name or path. Exit!\n", file);
      exit (1);
    }
  else
    {
      clock_t begin = clock();
      lineRead(in);
      clock_t pause = clock();
      printf("List of students before sort:\n");
      printArray(name, numS);
      clock_t resume = clock();
      //heapSort(name, numS);
      quickSort(name, 1, (numS - 1));
      clock_t stop = clock();
      printf("\n____________________\n\n\n");
      printf("List of students after sort:\n");
      printArray(name, numS);
      printf("\n____________________\n\n");
      printf("Execution time:\n");
      printf("\tFor readding data from file: %lf second(s).\n", (double)(pause - begin) / CLOCKS_PER_SEC);
      printf("\tFor sorting %d students: %lf sencond(s).\n", numS, (double)(stop - resume) / CLOCKS_PER_SEC);
      printf("\tFor the whole program:\n");
      printf("\t\tExcluding the print tasks: %lf second(s).\n", (double)(stop - resume + pause - begin) / CLOCKS_PER_SEC);
      printf("\t\tIncluding the print tasks: %lf second(s).\n", (double)(stop - begin) / CLOCKS_PER_SEC);
    }
  return 0;
}
