#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#include "menu.h"
#define MAX 8

void readFromText(char *fn, DLL *list) {

	FILE *f = fopen(fn, "r");
	dataType temp;
	
	if (f == NULL) {
		printf("Can not open file %s\n", fn);
		return;
	}

	while ( !feof(f) ) {
		fscanf(f, "%s", temp.name);
		fscanf(f, "%f", &(temp.price));

		insertAtLast(list, temp);
	}

	delete(list, list->last);
	fclose(f);
	return;
}

int main() {

	DLL list;
	DLL_init(&list);
	char sections [MAX][40] = {"Import from text","Display","Add at first","Add at last","Sential Search","Move to front","Transpose","Exit"}; 
	
	int choice;

	do {
	  choice = getMenu (sections, MAX);
	  switch (choice) {
	  case 1: {
	    readFromText("phoneDB.txt", &list);
	    break;
	  }
	    
	  case 2: {
	    printList(&list);
	    break;
	  }

	  case 3: {
	    printf("Add new phone at the head: ");
	    insertAtFirst(&list, getInfo());
	    break;
	  }

	  case 4: {
	    printf("Add new phone at the end: ");
	    insertAtLast(&list, getInfo());
	    break;
	  }

	  case 5: {
	    char key[30];
	    printf("Enter the name of the phone you want to find: ");
	    scanf("%s", key);
	    node *temp = linearSearch(&list, key);
	    if (temp != NULL) {
	      displayNode(temp);
	    } else {
	      printf("Phone not found!\n");
	    }
	    break;
	  }

	  case 6: {
	    char key[30];
	    printf("Enter the name of the phone you want to find : ");
	    scanf("%s", key);

	    node *temp = moveToFront(&list, key);
	    if (temp != NULL) {
	      displayNode(temp);
	    } else {
	      printf("Phone not found!\n");
	    }
	    break;
	  }

	  case 7: {
	    char key[30];
	    printf("Enter the name of the phone you want to find : ");
	    scanf("%s", key);

	    node *temp = transpose(&list, key);
	    if (temp != NULL) {
	      displayNode(temp);
	    } else {
	      printf("Phone not found!\n");
	    }
	    break;
	  }

	  case 8:
	    break;

	  default:
	    printf ("Wrong choice. It should be from 1 to 8.\n");
	    break;
	  }
	} while (choice != 8);
		
	return(0);
}

