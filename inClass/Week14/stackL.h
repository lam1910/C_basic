typedef char elmtypeL;
typedef struct node node;
typedef struct node
{
  elmtypeL* data;
  node* link;
}node;


void initializeL(node* p)
{
  p = NULL;
}
node* makeNewNode(elmtypeL* value)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  strcpy(new->data, value);
  new->link = NULL;
  return new;
}

int isEmptyL(node* p)
{
  return (p == NULL);
}


void pushHead(node* p, elmtypeL* value)
{
  node* tmp = makeNewNode(value);
  tmp->link = p;
  p = tmp;
}

elmtypeL* popHead(node* p)
{
  node* result = p;
  p = result->link;
  return result->data;
}

elmtypeL* showHead(node* p)
{
  node* result = p;
  return result->data;
}

