/*Project from book: Problem Solving and Program Design in C
  Author(s): Jeri R.Hanly & Elliot B.Koffman
  Program by: Lam
  Date: 30/3/2018 16:35*/
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define waterMass 1000
#define g 9.80
#define H 0.90

//This prgram calculate how much energy will be generated from a dam with the height h (m) and flow of v (m^3/s)

int main(int argc, char* argv[])
{
  //argc = 3, dam height flow
  double h, v;
  if (argc < 3)
    {
      printf("Not enough arguments were given.\nThe correct syntax:\n");
      printf("\tdam heightofDam flowOfWater\n");
      printf("Exit now!");
      exit(1);
    }
  else if (argc > 3)
    {
      printf("Too much arguments were given.\nThe correct syntax:\n");
      printf("\tdam heightofDam flowOfWater\n");
      printf("Exit now!");
      exit(1);
    }
  else
    {
      h = atof(argv[1]);
      v = atof(argv[2]);
      double work;
      work = h * (v * waterMass) * g * H;
      printf("Output Power in Watt: %.4lf, in Megawatt: %.4lf\n", work, work / 1000000); 
    }
  return 0;
}
