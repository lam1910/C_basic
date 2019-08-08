typedef struct node node
typedef struct node
{
  int data;
  node* link;
}node;

node* top;

node* makeNewNode(int value)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  new->data = value;
  new->link = NULL;
  return new;
}

int isEmpty(node* top)
{
  return (top->link == NULL);
}

int isFull(node* top)
{

}

node* push(node* p, int value)
{
  
}
