#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct address_t
{
  char name[20];
  char tel[11];
  char email[25];
}address;

struct list_el
{
  address addr;
  struct list_el *next;
};
typedef struct list_el node_addr;

node_addr *root, *cur, *prev;

// get data from user
address addContact()
{
  address new;
  printf("Name: \n\t");
  gets(new.name);
  printf("\tTelephone number: \n\t\t");
  gets(new.tel);
  printf("\tEmail: \n\t\t");
  gets(new.email);
  return new;
}
//make a new node
node_addr* makeNewNode(address addr)
{
  node_addr* new;
  new = (node_addr* )malloc(sizeof(node_addr));
  new->addr = addr;
  new->next = NULL;
  return new;
}

//print node
void printNode(node_addr* now)
{
  if (now == NULL)
    {
      printf("Do not have this node.\n");
      return;
    }
  address temp = now->addr;
  printf("%s\t%s\t%s %p\n", temp.name, temp.tel, temp.email, now->next);
  
}

//add node to first
void insertHead(address person)
{
  node_addr* personC = makeNewNode(person);
  personC->next = root;
  root = personC;
  cur = root;
}

//show all node from pointer head to end
void printPart(node_addr* head)
{
  node_addr* temp = head;
  while(temp != NULL)
    {
      printNode(temp);
      temp = temp->next;
    }
}

//show all list
void traversingList()
{
  node_addr* p;
  for(p = root; p != NULL; p = p->next)
    printNode(p);
}

//insert after the current position
void insert(address person)
{
  node_addr* append = makeNewNode(person);
  if (root == NULL)
    {
      root = append;
      cur = root;
    }
  else
    {
      append->next = cur->next;
      cur->next = append;
      prev = cur;
      cur = cur->next;
    }
}

//insert before the current position (not test) (need to declare node_addr* prev as global var to point to previous element of the list)
void insertBefore(address person)
{
  node_addr* append = makeNewNode(person);
  if (root == NULL)
    {
      root = append;
      cur = root;
    }
  else if (cur == root)
      insertHead(person);
  else
    {
      append->next = cur;
      prev->next = append;
      cur = append;
    }
}

//insert after position n
node_addr* insertAtPosition(node_addr* root, address person, int n)
{
  node_addr* append = makeNewNode(person);
  node_addr* tmp;
  //position of the last node (if neccessery)
  int i;
  if (n == 0)
    {
      cur = root;
      append->next = cur->next;
      cur->next = append;
      prev = cur;
      cur = cur->next;
      return cur;
    }
  for (tmp = root; tmp != NULL; tmp = tmp->next)
    {
      i ++;
      if (i == n)
	{
	  cur = tmp;
	  append->next = cur->next;
	  cur->next = append;
	  prev = cur;
	  cur = cur->next;
	  return cur;
	}
    }
  cur = tmp;
  append->next = cur->next;
  cur->next = append;
  prev = cur;
  cur = cur->next;
  return cur;
}

//free list
void freeLinked()
{
  node_addr* to_free = root;
  while (to_free != NULL)
    {
      root = root->next;
      free(to_free);
      to_free = root;
    }
}

int main()
{
  address mine;
  address* people;
  mine = addContact();
  root = makeNewNode(mine);
  cur = root;
  printNode(root);
  int i, num;
  printf("How many contact: ");
  scanf("%d", &num);getchar();
  people = (address *)malloc(num * sizeof(address));
  for (i = 0; i < num; i ++)
    {
      people[i] = addContact();
      insertHead(people[i]);
      printNode(cur);
    }
  traversingList();
  free(people);
  address duc;
  duc = addContact();
  insertAtPosition(root, duc, 2);
  traversingList();
  return 0;
}
