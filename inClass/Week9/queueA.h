//(rear + 1) % sizeof(queue)
#define MAXLEN 100
typedef int elmtype;
typedef struct
{
  elmtype queueType[MAXLEN];
  //store value
  int Front, Rear;
} Queue;

void creteQueue(Queue* new)
{
  new->Front = 0;
  new->Rear = 0;
}

int isEmpty(Queue* new)
{
  return ((new->Front == 0) && (new->Rear == 0);)
}

int isFull(Queue* new)
{
  return ();
}

void enQueue(Queue* ap

