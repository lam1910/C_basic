#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define file "test.txt"
#define sp ' '

//Remember to change all the line when change keyType to char and key change to pointer (string) and vice versa. When it is required that struct node to have more field than the source  file indicated, recommend to copy the source file to that program source code and change it there
typedef char keyType;

typedef struct node
{
  keyType key[20];
  int occur;
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
  else
    return search(x, root->right);
}

node* makeNewNode(keyType* x)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  strcpy(new->key, x);
  new->occur = 0;
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
      (*r)->occur = 1;
      (*r)->left = NULL;
      (*r)->right = NULL;
    }
  else if (strcmp((*r)->key, x) < 0)
    insertBST(x, &(*r)->left);
  else if (strcmp((*r)->key, x) > 0)
    insertBST(x, &(*r)->right);
}

//delete the left most node of tree r
keyType* deleteMin(BSTtype* r)
{
  keyType k[20];
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
void preoder(BSTtype tree)
{
  if (tree != NULL)
    {
      printf("%s\t", tree->key);
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
      printf("%s\t", tree->key);
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
      printf("%s\t", tree->key);
    }
}

keyType* readWord(FILE* fptr)
{
  int count = 0;
  char c;
  keyType* word;
  word = (keyType* )malloc(3 * sizeof(char));
  c = getc(fptr);
  if (c == sp)
    {
      count = 0;
      return word;
    }
  else
    {
      count ++;
      word = (keyType* )realloc(word, count * sizeof(char));
      *(word + count - 1) = c;
    }
}

BSTtype sort = NULL;

void sortWord(keyType* word)
{
  BSTtype node = search(word, sort);
  if (node == NULL)
    insertBST(word, &sort);
  else
    (node->occur) ++;
}

int main()
{
  char *term;
  FILE* strm;
  strm = fopen(file, "w+");
  if (strm == NULL)
    {
      printf("Cannot open text file %s. Check file name or file path. Exit!\n", file);
      exit(1);
    }
  else
    {
      do
	{
	  term = readWord(strm);
	  sortWord(term);
	}while (!feof(strm));
    }
  inoder(sort);
  free(term);
  fclose(strm);
  return 0;
}
