#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

int main()
{
  BSTtype ts = NULL;
  int i;
  for (i = 1; i <= 20; i ++)
    insertBST(i, &ts);
  inoder(ts);
  printf("\n_______________________\n\n");
  delete(10, &ts);
  inoder(ts);
  printf("\n_______________________\n");
}
