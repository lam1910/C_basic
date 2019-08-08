#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

#define TBD "TBD"

//function to choose a winner
int chooseWinner()
{
  int r = rand() % 2;
  return 1 + r;
}

treeType createBracket()
{
  treeType champion;
  makeNewTree(&champion);
  champion = makeNewNode(TBD);
  treeType finalist1 = addLeft(&champion, TBD);
  treeType finalist2 = addRight(&champion, TBD);
  treeType semiF1 = addLeft(&finalist1, TBD);
  treeType semiF2 = addRight(&finalist2, TBD);
  treeType semiF3 = addLeft(&finalist2, TBD);
  treeType semiF4 = addRight(&finalist1, TBD);
  treeType quaterF1 = addLeft(&semiF1, TBD);
  treeType quaterF2 = addRight(&semiF2, TBD);
  treeType quaterF3 = addLeft(&semiF3, TBD);
  treeType quaterF4 = addRight(&semiF4, TBD);
  treeType quaterF5 = addLeft(&semiF4, TBD);
  treeType quaterF6 = addRight(&semiF3, TBD);
  treeType quaterF7 = addLeft(&semiF2, TBD);
  treeType quaterF8 = addRight(&semiF1, TBD);
  treeType n1 = addLeft(&quaterF1, "R.Nadal");
  treeType n2 = addRight(&quaterF2, "R.Federer");
  treeType n3 = addLeft(&quaterF3, "A.Zverev");
  treeType n4 = addRight(&quaterF4, "M.Cilic");
  treeType n5 = addLeft(&quaterF5, "G.Dimitrov");
  treeType n6 = addRight(&quaterF6, "J.M.delPotro");
  treeType n7 = addLeft(&quaterF7, "D.Thiem");
  treeType n8 = addRight(&quaterF8, "K.Anderson");
  treeType n9 = addLeft(&quaterF8, "J.Isner");
  treeType n10 = addRight(&quaterF7, "D.Gofin");
  treeType n11 = addLeft(&quaterF6, "P.C.Busta");
  treeType n12 = addRight(&quaterF5, "N.Djokovic");
  treeType n13 = addLeft(&quaterF4, "S.Querrey");
  treeType n14 = addRight(&quaterF3, "R.B.Agut");
  treeType n15 = addLeft(&quaterF2, "J.Sock");
  treeType n16 = addRight(&quaterF1, "T.Berdych");
  return champion;
}

int main()
{
  srand(time(NULL));
  treeType tennis = createBracket();
  int ro, mt;
  for (ro = 0; ro < 4; ro++)
    {
      if (ro == 0)
	{
	  for (mt = 0; mt < 8; ++mt)
	    {
	      if (
	    }
	}
      else if (mo == 1)
	{
	  for (mt = 0; mt < 4; ++mt)
	    {
	    }
	}
      else if (mo == 2)
	{
	  for (mt = 0; mt < 2; ++mt)
	    {
	    }
	}
      else
	{
	}
    }
  return 0;
}
