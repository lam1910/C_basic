#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct point
{
    double x;
    double y;
}point_t;

typedef struct circle
{
    point_t center;
    double radius;
}circle_t;

int inCircle(point_t *a, circle_t *o)
{
    double distance;
    distance = (a->x - o->center.x) * (a->x - o->center.x) + (a->y - o->center.y) * (a->y - o->center.y);
    return (distance <= (o->radius * o->radius));
}

int isCrossing(circle_t *o1, circle_t *o2)              //two circle with O1, O2 as center respectively
{
    double distance0, distance1, distance2;             //distance0 is the distance between O1 and O2
                                                        //distance1 is the distance from O1 to the intersection between O1O2 and circle O2
                                                        //distance2 is the distance from O2 to the intersection between O1O2 and circle O1
    distance0 = (o1->center.x - o2->center.x) * (o1->center.x - o2->center.x) + (o1->center.y - o2->center.y) * (o1->center.y - o2->center.y);
    distance1 = o2->radius * o2->radius - distance0;
    distance2 = o1->radius * o2->radius - distance0;

    if (inCircle(&(o2->center), o1))                    //the case O2 is inside circle O1
        return (distance2 <= (o1->radius - o2->radius));
    else if (inCircle(&(o1->center), o2))               //the case O1 is inside circle O2
        return (distance1 <= (o2->radius - o1->radius));
    else                                                //O1 is not inside circle O2 and vice versa
        return (distance0 <= (o1->radius + o2->radius));
}

void printCircle(circle_t *o)
{
    printf("The circle's center coordinate: x = %.4lf, y = %.4lf\n", o->center.x, o->center.y);
    printf("The circle's radius will be: r = %.4lf\n", o->radius);
}

int main()
{
    int number, choice, i = 0, j = 1;
    printf("How many circle do you want to create?\n");
    printf("\t I want: ");
    scanf("%d", &number);
    circle_t setofCircles[number];
    circle_t* setofCircle = setofCircles;
    double limit = 0;
    setofCircle = (circle_t *)malloc((number + 3) * sizeof(circle_t));
    printf("Beginning to create circle.\n");
    srand((unsigned int)time(NULL));
    do
    {
        printf("Circle number %d:\n", i + 1);
        printf("\t1: Enter Manually.\n\t2: Randomly Generate.\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Please enter your circle's center coordinate:\n");
            printf("\tX: ");
            scanf("%lf", &(setofCircle->center.x));
            printf("\tY: ");
            scanf("%lf", &(setofCircle->center.y));
            printf("Now enter your circle's radius:\n");
            scanf("%lf", &(setofCircle->radius));
            while (setofCircle->radius <= 0)
            {
                printf("Wrong input! Radius of a circle must be a positive real number. Input the radius again: ");
                scanf("%lf", &(setofCircle->radius));
            }
            i ++;
            break;
        case 2:
            printf("How big this circle could possibly be (both coordinate of center and radius)?\n");
            scanf("%lf", &limit);
            setofCircle->center.x = ((double)rand()/(double)(RAND_MAX)) * limit;
            setofCircle->center.y = ((double)rand()/(double)(RAND_MAX)) * limit;
            setofCircle->radius = ((double)rand()/(double)(RAND_MAX)) * limit;
            i ++;
            break;
        default:
            printf("Wrong input. Your choice must be either 1 or 2. The choosing menu will be shown again.\n");
            break;
        }
        setofCircle ++;
    } while (i < number);
    setofCircle = setofCircle - number;
    for(i = 0; i < number; i ++)
    {
        printf("Circle number %d\n", i + 1);
        printCircle(setofCircle + i);
    }
    setofCircle = setofCircle - number + 1;
    for (i = 0; i < number; i ++)
    {
        printf("Circle number %d is crossing:\n", i + 1);
        for (j = i; j < number; j ++)
        {
            if (isCrossing(setofCircle + i, setofCircle + j) == 1)
                printf("\tCircle number %d\n", j + 1);
        }
    }
    return 0;
}
