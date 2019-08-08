#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* subStr(char *s1, int offset, int number)
{
    char *result;
    int length;
    int i;
    if (number < 0)                                                //the case of negative number input
    {
        printf("The number of letter in the substring cannot be negative. Exit now!\n");
        exit(EXIT_FAILURE);
    }
    else if (offset >= strlen(s1) || offset < 0)                   //the case of inputting wrong offset
    {
        printf("Offset is out of range. Exit now!\n");
        exit(EXIT_FAILURE);
    }
    else if (offset + number - 1 >= strlen(s1))                    //the case of trying to copy too many letter
    {
        printf("Out of range. Your substring will end at the end of the original string!\n");
        length = strlen(s1) - offset;
        result = (char *)malloc(length + 1);
        for(i = 0; i < length; i ++)
        {
            *(result + i) = *((s1 + offset - 1));
            s1 ++;
        }
        *(result + i) = '\0';
    }
    else                                                            //normal case
    {
        printf("Substring will begin at %c and end at %c\n", *(s1 + offset - 1), *(s1 + offset + number - 2));
        result = (char *)malloc(number + 2);
        for(i = 0; i < number; i ++)
        {
            *(result + i) = *((s1 + offset - 1));
            s1 ++;
        }
        *(result + i + 1) = '\0';
    }
    return result;
}

int main()
{
    char *str;
    int initialLength;
    int i;
    int lengthSub;
    char *substr;
    printf("How long do you want your string last?\n");
    scanf("%d", &initialLength);
    str = (char *)malloc(initialLength + 1);
    printf("Enter your string here: ");
    scanf("%s", str);
    printf("Your substring will begin at: ");
    scanf("%d", &i);
    printf("How long will your substring last?\n");
    scanf("%d", &lengthSub);
    substr = (char *)malloc(lengthSub + 1);
    substr = subStr(str, i, lengthSub);

    printf("Your substring:\n");
    printf("\t%s\n", substr);
    free(substr);
    return 0;
}
