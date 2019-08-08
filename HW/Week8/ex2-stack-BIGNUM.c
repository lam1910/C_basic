#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define T 1
#define F 0
#define max 1000
#define EMP "0"
int top1,top2;
char num1[max],num2[max], substract[max], sum[max];

int isEmpty(int top);
int isFull(int top);
void init(char a[], int *top);
void push(char a[], int *top, char data);
char pop(char a[], int *top);
void getNum(char a[], int *top);
int addition(char a[], char b[], int atop, int btop);
int isGreater(char a[], char b[], int atop, int btop);
int substraction(char a[], char b[], int atop, int btop);

void main(void){
  char ch;
  int i,top,start;
  char cur;
  do{
    printf("\n______\nMenu");
    printf("\n\t1. Enter 2 number;");
    printf("\n\t2. Addition;");
    printf("\n\t3. Substraction;");
    printf("\n\t4. Quit;");
    printf("\nYour choice: ");
    while((ch=getchar())=='\n');scanf("%*c");
    switch(ch){
    case'1':{
      init(num1,&top1);
      init(num2,&top2);
      printf("Enter the first number: ");
      getNum(num1,&top1);
      printf("Enter the second number: ");
      getNum(num2,&top2);
      break;
    }
    case'2':{
      if(isEmpty(top1) == T || isEmpty(top2) == T){
	printf("Please choose option 1 to input data!\n");
	break;
      }
      printf("---\nResult:\n");
      top = addition(num1,num2,top1,top2);
      for(i=1;i<=top1;i++) printf("%c",num1[i]);
      printf(" + ");
      for(i=1;i<=top2;i++) printf("%c",num2[i]);
      printf(" = ");
      for(i=top;i>0;i--) printf("%c",sum[i]);
      break;
    }
    case'3':{
      if(isEmpty(top1) == T || isEmpty(top2) == T){
	printf("Please choose option 1 to input data!\n");
	break;
      }
      printf("---\nResult:\n");     
      switch(isGreater(num1,num2,top1,top2)){
      case T:{
	top = substraction(num1,num2,top1,top2);
		
	for(i=1;i<=top1;i++) printf("%c",num1[i]);
	printf(" - ");
	for(i=1;i<=top2;i++) printf("%c",num2[i]);
	printf(" = ");

	start = 0;
	for(i=top;i>0;i--){
	  if(start ==  0){
	    if(substract[i] == '0'){
	      continue;
	    }else{
	      start = 1;
	      printf("%c",substract[i]);
	    }
	  }else{
	    printf("%c",substract[i]);
	  }
	}
	if(start == 0){
	  printf("%c\n",'0');
	  for(i=1;i<=top1;i++) printf("%c",num1[i]);
	  printf(" - ");
	  for(i=1;i<=top2;i++) printf("%c",num2[i]);
	  printf(" = ");
	  printf("%c",'0');
	}else{
	  printf("\n");
	  for(i=1;i<=top2;i++) printf("%c",num2[i]);
	  printf(" - ");
	  for(i=1;i<=top1;i++) printf("%c",num1[i]);
	  printf(" = -");
	
	  start = 0;
	  for(i=top;i>0;i--){
	    if(start ==  0){
	      if(substract[i] == '0'){
		continue;
	      }else{
		start = 1;
		printf("%c",substract[i]);
	      }
	    }else{
	      printf("%c",substract[i]);
	    }
	  }
	}
	break;
      }
      case F: {
	top = substraction(num2,num1,top2,top1);
	
      	for(i=1;i<=top1;i++) printf("%c",num1[i]);
	printf(" - ");
	for(i=1;i<=top2;i++) printf("%c",num2[i]);
	printf(" = -");
	start = 0;
	for(i=top;i>0;i--){
	  if(start ==  0){
	    if(substract[i] == '0'){
	      continue;
	    }else{
	      start = 1;
	      printf("%c",substract[i]);
	    }
	  }else{
	    printf("%c",substract[i]);
	  }
	}
	
	printf("\n");
	for(i=1;i<=top2;i++) printf("%c",num2[i]);
	printf(" - ");
	for(i=1;i<=top1;i++) printf("%c",num1[i]);
	printf(" = ");

	start = 0;
	for(i=top;i>0;i--){
	  if(start ==  0){
	    if(substract[i] == '0'){
	      continue;
	    }else{
	      start = 1;
	      printf("%c",substract[i]);
	    }
	  }else{
	    printf("%c",substract[i]);
	  }
	}
	break;
      }
      }
      break;
    }
    case'4':{
      printf("Thank you for using our services!\n");
      break;
    }
    default:{
      printf("Your option is not available!\nPlease try another one!\n");
      break;
    }
    }
  }while(ch!='4');
}
int addition(char a[], char b[], int atop, int btop){
  char atmp[max];
  char btmp[max];
  int top, i, x, y;
  char data;
  strcpy(atmp,a);
  strcpy(btmp,b);
  init(sum,&top);
  i = 0;
  do{
    if(isEmpty(atop) == T && isEmpty(btop) == T){
      break;
    }
    if(isEmpty(atop) == F){
      x = pop(atmp,&atop) - '0';
    }else
      x = 0;
    if(isEmpty(btop) == F){
      y = pop(btmp,&btop) - '0';
    }else
      y = 0;
    i = i + x + y;
    data = (i % 10) + '0';
    push(sum,&top,data);
    i = i / 10;
  }while(1);
  if(i == 1){
    data = i + '0';
    push(sum,&top,data);
  }
  return top;
}
int isGreater(char a[], char b[], int atop, int btop){
  if(atop > btop){
    return T;
  }else{
    if(atop < btop){
      return F;
    }else{
      int i = 1;
      do{
	if(a[i] > b[i])
	  return T;
	if(a[i] < b[i])
	  return F;
	i++;
      }while(i <= atop);
      return T;
    }
  }
}
int substraction(char a[], char b[], int atop,int btop){
  char atmp[max];
  char btmp[max];
  int top, i, tmp, x, y;
  char data;
  strcpy(atmp,a);
  strcpy(btmp,b);
  init(substract,&top);
  i = 0;
  do{
    if(isEmpty(atop) == T){
      break;
    }
    x = pop(atmp,&atop) - '0';
    if(isEmpty(btop) == F){
      y = pop(btmp,&btop) - '0';
    }else
      y = 0;
    i = x - y - i;
    if(i<0){
      if(atop > 0){
	data = (i + 10) % 10 + '0';
	i = 1;
      }else{
	data = (0 - i) + '0';
	i = 1;
      }
    }else{
      data = i + '0';
      i = 0;
    }
    push(substract,&top,data);
  }while(1);
  return top;
}
void getNum(char a[], int *top){
  char cur;
  int i;
  do{
    if(isFull(*top) == T)
      break;
    cur = getchar();
    if(cur >= '0' && cur <= '9'){
      push(a,top,cur);
    }
  }while(cur != '\n');
}
void push(char a[], int *top, char data){
  (*top)++;
  a[*top] = data;
}
void init(char a[], int *top){
  *top = 0;
  strcpy(a,EMP);
}
char pop(char a[], int *top){
  char tmp = a[*top];
  *top = *top -1;
  return tmp;
}
int isEmpty(int top){
  if(top == 0)
    return T;
  else
    return F;
}
int isFull(int top){
  if(top == max -1)
    return T;
  else
    return F;
}
