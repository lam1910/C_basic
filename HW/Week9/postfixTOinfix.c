#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h> 

# define MAX 20

int top;
long int stack[50];
char infix_expression[50], postfix_expression[50];

char str[MAX], stack[MAX];
int top = -1;
 
char pop()
{
      return stack[top--];
}
 
void push(char ch)
{
      stack[++top] = ch;
}
 
void postfix_to_infix(char expression[])
{
      int count, length;
      char element, operator;
      length = strlen(expression);
      for(count = 0; count < MAX; count++)
      {
            stack[count] = 0;
      }
      printf("\nInfix Expression:\t");
      printf("%c", expression[0]);
      for(count = 1; count < length; count++)
      {
            if(expression[count] == '-' || expression[count] == '/' || expression[count] == '*'|| expression[count] == '+')
            {
                  element = pop();
                  operator = expression[count];
                  printf(" %c %c", operator, element);
            }
            else
            {
                  push(expression[count]);
            }
      }
      printf("%c", expression[top--]);
}

void expression_conversion();
int check_space_tabs(char character);
void push1(long int character);
int pop1();
int priority(char character);
int isEmpty();
int main()
{
      char postfix_expression[50];
      printf("\nEnter Postfix Expression:\t");
      scanf("%s", postfix_expression);
      postfix_to_infix(postfix_expression);
      printf("\n");
      return 0;
}


 
int main()
{
      top = -1;
      printf("\nEnter an Expression in Infix format:\t");
      scanf("%[^\n]s", infix_expression);
      expression_conversion();
      printf("\nExpression in Postfix Format: \t%s\n", postfix_expression);
      return 0;
}
 
void expression_conversion()
{
      unsigned int count, temp = 0;
      char next;
      char character; 
      for(count = 0; count < strlen(infix_expression); count++)
      {
            character = infix_expression[count];
            if(!check_space_tabs(character))
            {
                  switch(character)
                  {
                        case '(': push(character);
                                  break;
                        case ')':
                                  while((next = pop()) != '(')
                                  {
                                        postfix_expression[temp++] = next;
                                  }
                                  break;
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '%':
                        case '^':
                                  while(!isEmpty() && priority(stack[top]) >= priority(character))
                                  postfix_expression[temp++] = pop();
                                  push(character);
                                  break;
                        default: 
                                  postfix_expression[temp++] = character;
                  }
            }
      }
      while(!isEmpty()) 
      {
            postfix_expression[temp++] = pop();
      }
      postfix_expression[temp] = '\0';
}
 
int priority(char character)
{
      switch(character)
      {
            case '(': return 0;
            case '+':
            case '-':
                      return 1;
            case '*':
            case '/':
            case '%':
                      return 2;
            case '^':
                      return 3;
            default:
                      return 0;
      }
}
 
void push1(long int character)
{
      if(top > 50)
      {
            printf("Stack Overflow\n");
            exit(1);
      }
      top = top + 1;
      stack[top] = character;
}
 
int check_space_tabs(char character)
{
      if(character == ' ' || character == '\t')
      {
            return 1;
      }
      else
      {
            return 0;
      }
}
 
int pop1()
{
      if(isEmpty())
      {
            printf("Stack is Empty\n");
            exit(1);
      }
      return(stack[top--]);
}
 
int isEmpty()
{
      if(top == -1)
      {
            return 1;
      }
      else
      {
            return 0;
      }
}
