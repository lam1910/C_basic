#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
  treeType newTree;
  makeNewTree(&newTree);
  printf("%d\n", isEmptyT(newTree));
  addLeft(&newTree, '+');
  
  addRight(&newTree, 'a');
  addLeft(&newTree, 'A');
  return 0;
}
