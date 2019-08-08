#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define file "list.txt"
#define MAX_LEN 80
#define sp " "

//Remember to change all the line when change keyType to char and key change to pointer (string) and vice versa. When it is required that struct node to have more field than the source  file indicated, recommend to copy the source file to that program source code and change it there
typedef char keyType;

typedef struct node
{
  keyType key[MAX_LEN];
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

node* makeNewNode(keyType* x)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  strcpy(new->key, x);
  new->left = NULL;
  new->right = NULL;
}

//insert a new node to the BST at this program insert only when first found a word or use after found,  occur = 1
void insertBST(keyType* x, BSTtype* r)
{
  if (*r == NULL)
    {
      *r = (node* )malloc(sizeof(node));
      strcpy((*r)->key,  x);
      
      (*r)->left = NULL;
      (*r)->right = NULL;
    }
  else if (strcmp((*r)->key, x) < 0)
    insertBST(x, &((*r)->left));
  else if (strcmp((*r)->key, x) > 0)
    insertBST(x, &((*r)->right));
}

//delete the left most node of tree r
keyType* deleteMin(BSTtype* r)
{
  keyType* k;
  k = (keyType* )malloc((MAX_LEN) * sizeof(char));
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
}

//root first travesal
void preorder(BSTtype tree)
{
  if (tree != NULL)
    {
      printf("%s", tree->key);
      preorder(tree->left);
      preorder(tree->right);
    }
}

//root in between two subtree
void inorder(BSTtype tree)
{
  if (tree != NULL)
    {
      inorder(tree->left);
      printf("%s", tree->key);
      inorder(tree->right);
    }
}

//root after
void postorder(BSTtype tree)
{
  if (tree != NULL)
    {
      postorder(tree->left);
      postorder(tree->right);
      printf("%s", tree->key);
    }
}

BSTtype student;

//read a line
void lineRead(FILE* ptr)
{
  char line[MAX_LEN];
  BSTtype tmp;
  while (fgets(line, sizeof(line), ptr) != NULL)
    {
      printf("%s", line);
      insertBST(line, &student);	
    }
}
int main()
{
  char name[MAX_LEN];
  FILE* in;
  in = fopen(file, "r+");
  if (in == NULL)
    {
      printf("Cannot open %s. Check file name or path. Exit!\n", file);
      exit (1);
    }
  else
    {
      lineRead(in);
      printf("Imported! The name you want to search is: ");
      
      fgets(name, MAX_LEN, stdin);
      if (search(name, student) != NULL)
	{
	  printf("He or she is on the list.\n");
	}
      else
	printf("Cannot find %.21s", name);
    }
  return 0;
}
