typedef int elmtypeL;
typedef struct node node;
typedef struct node
{
  elmtypeL data;
  node* link;
}node;

node* topL;

void initializeL(node* p)
{
  p = NULL;
}
node* makeNewNode(elmtypeL value)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  new->data = value;
  new->link = NULL;
  return new;
}

int isEmptyL(node* p)
{
  return (p == NULL);
}


void pushHead(node* p, elmtypeL value)
{
  node* tmp = makeNewNode(value);
  tmp->link = p;
  p = tmp;
}

elmtypeL popHead(node* p)
{
  if (p != NULL)
    {
      node* result = p;
      p = result->link;
      return result->data;
    }
  else
    {
      printf("Stack empty!\n");
    }
}

void showHead(node* p)
{
  node* result = p;
  printf("The value of the top is: %s.\n", p->data);
}

