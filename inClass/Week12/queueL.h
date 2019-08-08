typedef treeType elmtypeL;
typedef struct node node;
typedef struct node
{
  elmtypeL data;
  node* toFront;
  node* toRear;
}node;

typedef struct queue
{
  node* Front;
  node* Rear;
}queueType;


void initializeL(queueType* p)
{
  p->Front = NULL;
  p->Rear = NULL;
}

node* makeNewNode(elmtypeL value)
{
  node* new;
  new = (node* )malloc(sizeof(node));
  new->data = value;
  new->toFront = NULL;
  new->toRear = NULL;
  return new;
}

int isEmpty(queueType* p)
{
  return ((p->Front == NULL) && (p->Rear == NULL));
}

void enQueue(queueType* p, elmtypeL value)
{
  if (isEmpty(p))
    {
      node* tmp = makeNewNode(value);
      p->Front = tmp;
      p->Rear = NULL;
    }
  else if (p->Rear == NULL)
    {
      node* tmp = makeNewNode(value);
      p->Front->toRear = tmp;
      tmp->toFront = p->Front;
      p->Rear = p->Front->toRear;
    }
  else
    {
      node* append = makeNewNode(value);
      p->Rear->toRear = append;
      append->toFront = p->Rear;
      p->Rear = p->Rear->toRear;
    }
}

elmtypeL deQueue(queueType* p)
{
  if (isEmpty(p))
    {
      printf("Queue is empty.\n");
    }
  else
    {
      node* takeout = p->Front;
      p->Front = p->Front->toRear;
      p->Front->toFront = NULL;
      return takeout->id;
    }
}
