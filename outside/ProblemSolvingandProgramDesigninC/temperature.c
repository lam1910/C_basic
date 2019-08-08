#include <stdio.h>
#include <stdlib.h>

double timeInput(char* hrc, char* minc)
{
  int hr, min;
  hr = atoi(hrc);
  min = atoi(minc);
  while(min >= 60)
    {
      printf("Minute input cannot exceed 59 minutes. Try again(format: hh:mm):\n\t");
       scanf("%d%*c%d", &hr, &min);
       getchar();
    } 
  return hr + min / 60; 
}

//calculate T(emperature) as a function of t(ime) using given formular
double T(double t)
{
  double result;
  result = (4*t*t / (t + 2)) - 20;
  return result;
}

int main(int argc, char* argv[])
{
  //argc = 3, tempt hourElapsed minuteElapsed
  if (argc > 3)
    {
      printf("Too many arguments were given. The correct syntax:\n\t\t");
      printf("tempt hourElapsed minuteElapsed\n");
      printf("Exit now!\n");
      exit(1);
    }
  else if (argc < 3)
    {
      printf("Not enough arguments were given. The correct syntax:\n\t\t");
      printf("tempt hourElapsed minuteElapsed\n");
      printf("Exit now!\n");
      exit(1);
    }
  else
    {
      double time;
      time = timeInput(argv[1], argv[2]);
      printf("The temperature in the freezer right now is(degree Celsius(C)): %lf.\n", T(time));
    }
  return 0;
}
