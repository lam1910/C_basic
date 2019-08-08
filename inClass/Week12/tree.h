//decleration for struct
typedef char elmtypeT;
typedef struct node
{
  elmtypeT element;
  struct node* left;
  struct node* right;
}node;

typedef node* treeType;

//create (empty) a new tree
void makeNewTree(treeType* t)
{
  (*t) = NULL;
}

//check if tree is empty
int isEmptyT(treeType t)
{
  return (t == NULL);
}

//make new node or leaf
node* makeNewNode(elmtypeT value)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  if (new != NULL)
    {
      new->element = value;
      new->left = NULL;
      new->right = NULL;
    }
  return new;
}

//access left child
treeType leftChild(treeType n)
{
  if (n == NULL)
    return NULL;
  else
    return n->left;
}

//access right child
treeType rightChild(treeType n)
{
  if (n == NULL)
    return NULL;
  else
    return n->right;
}

//check if that node is leaf or not
int isLeaf(treeType t)
{
  if (t != NULL)
    return ((leftChild(t) == NULL) && (rightChild(t) == NULL));
  else
    return -1;
}

//count number of node in a tree
int count(treeType T)
{
  if (isEmptyT(T))
    return 0;
  else
    return 1 + count(leftChild(T)) + count(rightChild(T));
}

//merge two tree to make a new one with root having data as v
treeType mergeTree(elmtypeT v, treeType l, treeType r)
{
  treeType n;
  n = (node* )malloc(sizeof(node));
  n->element = v;
  n->left = l;
  n->right = r;
  return n;
}

//adding new node to left most position
treeType addLeft(treeType* t, elmtypeT new)
{
  node* append = makeNewNode(new);
  if (append == NULL)
    return (append);
  if (*t == NULL)
    *t = append;
  else
    {
      node* ln = *t;
      while (ln->left != NULL)
	ln = ln->left;
      ln->left = append;
    }
  return (append);
}

//adding new node to right most position
treeType addRight(treeType* t, elmtypeT new)
{
  node* append = makeNewNode(new);
  if (append == NULL)
    return (append);
  if (*t == NULL)
    *t = append;
  else
    {
      node* rn = *t;
      while (rn->left != NULL)
	rn = rn->left;
      rn->left = append;
    }
  return (append);
}

//root first travesal
void preoder(treeType tree)
{
  if (tree != NULL)
    {
      printf("%4d\t", tree->element);
      preoder(tree->left);
      preoder(tree->right);
    }
}

//root in between two subtree
void inoder(treeType tree)
{
  if (tree != NULL)
    {
      inoder(tree->left);
      printf("%4d\t", tree->element);
      inoder(tree->right);
    }
}

//root after
void postoder(treeType tree)
{
  if (tree != NULL)
    {
      postoder(tree->left);
      postoder(tree->right);
      printf("%4d\t", tree->element);
    }
}

#include "queueL.h"
//from root to leaf (check again, implement for BST as well)
void breadthFirst(treeType node)
{
  queueType queue;//queue of pointer
  initializeL(&queue);
  if (node != NULL)
    {
      enQueue(&queue, node);
      while (!isEmpty(&queue))
	{
	  node = deQueue(&queue);
	  printf(node->element);
	  if (node->left != NULL)
	    enQueue(&queue, node->left);
	  if (node->right != NULL)
	    enQueue(&queue, node->right);
	}
    }
}

