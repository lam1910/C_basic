#define Max 50
typedef int elmtype;
typedef elmtype stackType[Max];

//position that can be added new element in the near future
int top;

//make a new stack
void initialize(stackType stack)
{
  top = 0;
}

int isEmpty(stackType stack)
{
  return (top == 0);
}

int isFull(stackType stack)
{
  return (top == Max);
}

void push(elmtype elm, stackType stack)
{
  if (isFull(stack))
    printf("Stack overflow.\n");
  else
    stack[top ++] = elm;
}

elmtype pop(stackType stack)
{
  if (isEmpty(stack))
    printf("Stack underflow.\n");
  else return stack[-- top];
}

void showTop(stackType stack)
{
  if (isEmpty(stack))
    printf("Stack is empty.\n");
  else
    {
      int i;
      i = top - 1;
      printf("The value of top: %d.\n", stack[i]);
    }
}	

