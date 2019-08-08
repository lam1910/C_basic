#include<stdio.h>

void swap (int *a, int *b) {
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void insertionSort (int str[],int n) {
  int i,j;
  for (i = 0; i < n; i++) {
    j = i;
    while ( (j > 0) && (str[j] < str[j - 1]) ) {
      swap (&str[j], &str[j-1]);
      j--;
    } 
  }
  return;
}

int BSearch (int str[],int key,int Lo,int Hi) {
  if (Lo <= Hi) {
    int mid = (Lo + Hi) / 2;
    if (str[mid] == key) {
      return mid;
    }

    if (key < str[mid]) {
      return BSearch (str,key,Lo,mid - 1);
    } else {
      return BSearch (str,key,mid +1, Hi);
    }
  }
  return -1;
}

int main() {
  int arr1[30];
  int arr2[30];
  int n,m;
  printf ("Enter the number of elements in the list1: ");
  scanf ("%d",&n);
  for (int j = 0; j < n; j++) {
    printf ("arr1[%d] = ",j);
    scanf ("%d", &arr1[j]);
  }

  printf ("Enter the number of elements in the list2: ");
  scanf ("%d", &m);
  for (int k = 0; k < m; k++) {
    printf ("arr2[%d] = ",k);
    scanf ("%d", &arr2[k]);
  }
 
  insertionSort(arr1, n);
  insertionSort(arr2, m);

  printf("Element in list 1 but not in list 2:\n");
  for (int i = 0; i < n; i++) {
    if (BSearch(arr2, arr1[i], 0, m - 1) == -1) {
      printf("%d ", arr1[i]);
    }
  }
  printf ("\n");

  printf ("Element in list 2 but not in list 1: \n");
  for (int i = 0; i < m; i++) {
    if (BSearch (arr1, arr2[i],0,n-1) == -1) {
      printf ("%d ", arr2[i]);
    }
  }
  printf ("\n");
  return(0);
}
