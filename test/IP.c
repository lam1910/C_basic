#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fname "ip.txt"
#define blist "blockedip.txt"

//list structure
typedef struct n List;
typedef struct n
{
  char key[40];
  List* next;
}List;

//BST structure
//Remember to change all the line when change keyType to char and key change to pointer (string)
typedef char keyType;

typedef struct node
{
  keyType key[40];
  keyType addr[40];
  struct node* left;
  struct node* right;
}node;

typedef struct node* BSTtype;

//find the first occurence of a node that have key x
BSTtype search(keyType* x, BSTtype root)
{
  if (root == NULL) //not found, exit condition
    return NULL;
  else if (strcmp(root->key, x) == 0) //found, exit condition
    return root;
  else if (strcmp(root->key, x) < 0)
    return search(x, root->left);
  else if (strcmp(root->key, x) > 0)
    return search(x, root->right);
}

node* makeNewNode(keyType* x, keyType* ad)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  strcpy(new->key, x);
  strcpy(new->addr, ad);
  new->left = NULL;
  new->right = NULL;
}

//insert a new node to the BST
void insertBST(keyType x[40], keyType ad[40], BSTtype* r)
{
  if (*r == NULL)
    {
      *r = (node* )malloc(sizeof(node));
      strcpy((*r)->key, x);
      strcpy((*r)->addr, ad);
      (*r)->left = NULL;
      (*r)->right = NULL;
    }
  else if (strcmp(x, (*r)->key) < 0)
    insertBST(x, ad, &(*r)->left);
  else if (strcmp(x, (*r)->key) > 0)
    insertBST(x, ad, &(*r)->right);
}

/*//delete the left most node of tree r
keyType* deleteMin(BSTtype* r)
{
  keyType k[MAX_LEN];
  if ((*r)->left == NULL)
    {
      strcpy(k, (*r)->key);
      (*r) = (*r)->right;
      return k;
    }
  else
    return deleteMin(&(*r)->left);
}

//find the left most node (smallest) of the right most subtree of r(all of them are bigger than r->key and change key of node (tree) r to the key of that node than delete that node
void delete(keyType* x, BSTtype* r)
{
  if (*r != NULL)
    if (strcmp(x, (*r)->key) < 0)
      delete(x, &(*r)->left);
    else if (strcmp(x, (*r)->key) > 0)
      delete(x, &(*r)->right);
    else if (((*r)->left == NULL) && ((*r)->right == NULL))
      *r = NULL;
    else if ((*r)->left == NULL)
      *r = (*r)->right;
    else if ((*r)->right == NULL)
      *r = (*r)->left;
    else
      strcpy((*r)->key, deleteMin(&(*r)->right));
  else
    printf("Error: Do not have that tree.\n");
    }*/

//root first travesal
void preoder(BSTtype tree)
{
  if (tree != NULL)
    {
      printf("%s\t%s\n", tree->key, tree->addr);
      preoder(tree->left);
      preoder(tree->right);
    }
}

//root in between two subtree
void inoder(BSTtype tree)
{
  if (tree != NULL)
    {
      inoder(tree->left);
      printf("%s\t%s\n", tree->key, tree->addr);
      inoder(tree->right);
    }
}

//root after
void postoder(BSTtype tree)
{
  if (tree != NULL)
    {
      postoder(tree->left);
      postoder(tree->right);
      printf("%s\t%s\n", tree->key, tree->addr);
    }
}

void read(char* fn, BSTtype* r)
{
  FILE* f  = fopen(fn, "r+");
  char name[40], ad[40];
  if (f == NULL)
    {
      printf("Can not open file %s\n", fn);
      return;
    }
  while (!feof(f))
    {
      fscanf(f, "%s %s\n", name, ad);
      insertBST(name, ad, r);
    }
  fclose(f);
  return;
}

void blockList(FILE* in, char list[40])
{
  FILE* b;
  b = fopen(blist, "r+");
    
}

int main()
{
  int choice;
  BSTtype root = NULL;
  BSTtype h = NULL;
  BSTtype tmp = NULL;
  char a[40];
  do
    {
      printf("\n\n_______________\n");
      printf("Menu:\n");
      printf("\t1: Reading Data.\n");
      printf("\t2: IP Lookup.\n");
      printf("\t3: Blocks Website.\n");
      printf("\t4: IP Sort.\n");
      printf("\t5: Exit.\n");
      printf("\nYour Choice: ");
      scanf("%d", &choice);
      getchar();
      switch(choice)
	{
	case 1:
	  read(fname, &root);
	  printf("List of domain:\n");
	  inoder(root);
	  break;
	case 2:
	  printf("\n");
	  read(fname, &h);
	  printf("Your domain name: ");
	  fgets(a, 39, stdin);
	  //scanf("%s", a);
	  printf("%s", a);
	  tmp = search(a, h);
	  if (tmp != NULL)
	    {
	      printf("Redirecting to %s.\n", tmp->addr);
	    }
	  else
	    {
	      printf("This site cannot be reached.\n");
	    }
	  break;
	case 3:
	  
	  break;
	case 4:
	  break;
	case 5:
	  printf("\nThank you for using our service.\n");
	  break;
	default:
	  printf("Cannot recognize that function. Type in again (1-5).\n");
	  printf("The Menu will be shown again.\n");
	  break;
	}
    }while (choice != 5);
  return 0;
}
