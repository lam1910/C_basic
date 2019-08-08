//Remember to change all the line when change keyType to char and key change to pointer (string)
typedef int keyType;

typedef struct node
{
  keyType key;
  struct node* left;
  struct node* right;
}node;

typedef struct node* BSTtype;

//find the first occurence of a node that have key x
BSTtype search(keyType x, BSTtype root)
{
  if (root == NULL) //not found, exit condition
    return NULL;
  else if (root->key == x) //found, exit condition
    return root;
  else if (root->key < x)
    return search(x, root->left);
  else
    return search(x, root->right);
}

node* makeNewNode(keyType x)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  new->key = x;
  new->left = NULL;
  new->right = NULL;
}

//insert a new node to the BST
void insertBST(keyType x, BSTtype* r)
{
  if (*r == NULL)
    {
      *r = (node* )malloc(sizeof(node));
      (*r)->key = x;
      (*r)->left = NULL;
      (*r)->right = NULL;
    }
  else if (x < (*r)->key)
    insertBST(x, &(*r)->left);
  else if (x > (*r)->key)
    insertBST(x, &(*r)->right);
}

//delete the left most node of tree r
keyType deleteMin(BSTtype* r)
{
  keyType k;
  if ((*r)->left == NULL)
    {
      k = (*r)->key;
      (*r) = (*r)->right;
      return k;
    }
  else
    return deleteMin(&(*r)->left);
}

//find the left most node (smallest) of the right most subtree of r(all of them are bigger than r->key and change key of node (tree) r to the key of that node than delete that node
void delete(keyType x, BSTtype* r)
{
  if (*r != NULL)
    if (x < (*r)->key)
      delete(x, &(*r)->left);
    else if (x > (*r)->key)
      delete(x, &(*r)->right);
    else if (((*r)->left == NULL) && ((*r)->right == NULL))
      *r = NULL;
    else if ((*r)->left == NULL)
      *r = (*r)->right;
    else if ((*r)->right == NULL)
      *r = (*r)->left;
    else
      (*r)->key = deleteMin(&(*r)->right);
  else
    printf("Error: Do not have that tree.\n");
}

//root first travesal
void preoder(BSTtype tree)
{
  if (tree != NULL)
    {
      printf("%4d\t", tree->key);
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
      printf("%4d\t", tree->key);
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
      printf("%4d\t", tree->key);
    }
}
