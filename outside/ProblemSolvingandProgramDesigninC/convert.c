#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double FtoC(double dF)
{
  double result = (5 * (dF - 32) / 9);
  return result;
}
int main(int argc, char* argv[])
{
  //argc = 2, convertToC temperatureInF
  if (argc > 2)
    {
      printf("Too many arguments were given. The correct syntax:\n\t\t");
      printf("convertToC temperatureInF\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc < 2)
    {
      printf("Not enough arguments were given. The correct syntax:\n\t\t");
      printf("convertToC temperatureInF\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      double F = atoi(argv[1]);
      printf("Your input in degree Fahrenheit: %.0lf\n", F);
      printf("\t   in degree Celcius: %lf\n", FtoC(F));
    }
  return 0;
}
