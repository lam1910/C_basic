typedef int keyType

typedef struct node
{
  keyType key;
  struct node* left;
  struct node* right;
};

typedef struct node* BSTtype;

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
  new->right = NULL
}
