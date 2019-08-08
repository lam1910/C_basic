#define Max 50
typedef int elmtype;
typedef struct stackRec
{
  elmtype storage[Max];
  int top;
};
typedef struct stackRec stackType;

void initialize(stackType stack)
{
  stack.top = 0;
}

int isEmpty(stackType stack)
{
  return (stack.top == 0);
}

int isFull(stackType stack)
{
  return (stack.top == Max);
}

void push(elmtype elm, stackType stack)
{
  if (isFull(stack.storage))
    printf("Stack overflow.\n");
  else
    {
      stack.storage[stack.top] = elm;
      stack.top ++;
    }
}

int pop(elmtype elm, stackType stack)
{
  if (isEmpty(stack.storage))
    printf("Stack underflow.\n");
  else
    {
      --stack.top;
      return stack.storage[stack.top]
    }
}
