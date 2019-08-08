#include <stdlib.h>

typedef struct {
	char name[30];
	float price;
} dataType;

typedef struct node {
	dataType data;
	struct node *next;
	struct node *prev;
} node;

typedef struct {
	node *first;
	node *last;
} DLL;

void DLL_init(DLL *list) {
	list->first = NULL;
	list->last = NULL;
	return;
}


node *makeNode(dataType data) {

	node *newnode = (node *)malloc(sizeof(node));
	newnode->data = data;
	newnode->prev = NULL;
	newnode->next = NULL;
	
	return(newnode);
}

dataType getInfo() {

	dataType data;
	printf("Name: ");
	scanf("%s", data.name);
	printf("Price: ");
	scanf("%f", &(data.price));
	return(data);
}

void displayNode(node *p) {

	printf("%s  %.1f \n", p->data.name, p->data.price);
	return;
}

void insertAtLast(DLL *list, dataType data) {

	node *newnode = makeNode(data);
	if (list->last == NULL) {
		list->last = list->first = newnode;
		return;
	}

	list->last->next = newnode;
	newnode->prev = list->last;
	list->last = newnode;
	return;
}

void insertAtFirst(DLL *list, dataType data) {

	node *newnode = makeNode(data);
	if (list->first == NULL) {
		list->first = list->last = newnode;
		return;
	}

	newnode->next = list->first;
	list->first->prev = newnode;
	list->first = newnode;
	return;
}

void insertAfter(DLL *list, node *target, dataType data) {

	
	if (target == list->last) {
		insertAtLast(list, data);
		return;
	}

	node *newnode = makeNode(data);
	node *curr = list->first;

	while (curr != NULL && curr != target) {
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("Node not found! \n");
		return;
	}

	newnode->next = curr->next;
	curr->next->prev = newnode;
	curr->next = newnode;
	newnode->prev = curr;
	
	return;
}

void insertBefore(DLL *list, node *target, dataType data) {

	node *newnode = makeNode(data);
	
	if (list->first == NULL) {
		list->first = list->last = newnode;
		return;
	}

	if (target == list->first) {
		insertAtFirst(list, data);
		return;
	}
	
	node *curr = list->first;
	while (curr != NULL && curr != target) {
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("Node not found! \n");
		return;
	}

	newnode->next = curr;
	newnode->prev = curr->prev;
	curr->prev->next = newnode;
	curr->prev = newnode;
	return;
}

void delete(DLL *list, node *target) {

	if (target == list->first) {
		list->first = list->first->next;
		free(target);
		return;
	}

	node *prev = NULL;
	node *curr = list->first;

	while (curr != NULL) {

		if (curr == target) break;

		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("Node not found ! \n");
		return;
	}

	if (curr == list->last) {
		prev->next = NULL;
		free(curr);
		return;
	}

	prev->next = curr->next;
	curr->next->prev = prev;
	free(curr);
	return;
}

void printList(DLL *list) {

	if (list->first == NULL) {
		printf("List is empty!\n");
		return;
	}

	node *curr = list->first;
	while (curr != NULL) {
		displayNode(curr);
		curr = curr->next;
	}
	return;
}

void printListFromLast(DLL *list) {

	if (list->last == NULL) {
		printf("List is empty!\n");
		return;
	}

	node *curr = list->last;
	while (curr != NULL) {
		displayNode(curr);
		curr = curr->prev;
	}
	return;
}

node *linearSearch(DLL *list, char *key) {

	dataType data;
	strcpy(data.name, key);
	data.price = 0.0;
	
	insertAtLast(list, data);
	node *curr = list->first;

	while (curr != NULL) {
	    if ( strcmp(curr->data.name, key) == 0 ) {
			return(curr);
		}
		curr = curr->next;
	}
	
	return(NULL);
}

/* transpose */
node *transpose(DLL *list, char *key) {

	node *prev = NULL;
	node *curr = list->first;
	
	while (curr != NULL) {

		if ( strcmp(curr->data.name, key) == 0 ) {
			break;
		}
		
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) return(NULL); 
	
	if (curr == list->first) {
		return(curr);
	}
	else {
		dataType temp;
		temp = curr->data;
		curr->data = prev->data;
		prev->data = temp;
	}
	
	return(prev);
}

/* move to front */
node *moveToFront(DLL *list, char *key) {

	node *curr = list->first;
	
	while (curr != NULL) {

		if ( strcmp(curr->data.name, key) == 0 ) {
			break;
		}
		
		curr = curr->next;
	}

	if (curr == NULL) return(NULL); 

	dataType data = curr->data;

	delete(list, curr);

	insertAtFirst(list, data);
	
	return(list->first);
}


