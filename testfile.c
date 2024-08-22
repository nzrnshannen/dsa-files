#include<stdio.h>
int main()
{
    int inputNum;
    int findNum;

    int dig, temp, pos, retval = 0;

    printf("Enter a number: ");
    scanf("%d", &inputNum);

enterSingleDig:
    printf("Enter a number to search within (0-9): ");
    scanf("%d", &findNum);

    if(findNum < 0 || findNum > 9)
    {
        printf("\nPlease enter a single digit!\n");
        goto enterSingleDig;
    }

    temp = inputNum;

    int len = 0;
    while(temp!=0)
    {
        temp/=10;
        len++;
    }

    temp = inputNum;
    pos = len;

    while(temp!=0)
    {
        dig = temp % 10;
        if(dig == findNum)
        {
            retval += pos;
        }
        temp/=10;
        pos--;
    }

    if(retval!=0)
    {
        printf("\n---\nTotal = %d", retval);
    }
    else
    {
        printf("\n---\nDigit %d cannot be found!", findNum);
    }

    return 0;
}