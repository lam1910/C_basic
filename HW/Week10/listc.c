#include <stdio.h>

typedef struct {
	int key;
	int val;
} info;


int linearSearch(info s[], int n, int key) {

	for (int i = 0; i < n; i++) {
		if (s[i].key == key) {
			return(i);
		}
	}
	return(-1);
}

void verificate(info list1[], int n1, info list2[], int n2) {

	int i;
	printf ("All records have the same key but different values are: \n");
	for (i = 0; i < n1; i++) {
		int index = linearSearch(list2, n2, list1[i].key);
	
		if ( index != -1 && list2[index].val != list1[i].val ) {
		  printf("(%d, %d) and (%d, %d)\n",list1[i].key,list1[i].val,list2[index].key,list2[index].val);
		}
	}
	return;
}

int main() {

	info list1[] = {
		{1, 4},
		{2, 7},
		{3, 8},
		{4, 9},
		{5, 6},
		{6, 5},
		{7, 1}
	};

	int n1 = sizeof(list1) / sizeof(list1[0]);

	info list2[] = {
		{1, 3},
		{1, 2},
		{8, 9},
		{5, 8},
		{9, 10},
		{6, 12},
		{6, 14},
		{4, 16}
	};

	int n2 = sizeof(list2) / sizeof(list2[0]);

	verificate(list1, n1, list2, n2);
	return(0);
}
