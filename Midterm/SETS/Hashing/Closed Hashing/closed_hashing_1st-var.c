#include<stdio.h>
#include<stdbool.h>
#define SIZE 20
#define EMPTY -2
#define DELETED -1
#define PRIME_DATA_SIZE SIZE/2

typedef int Dictionary[SIZE];
int last;

void initDict(Dictionary D);
void displayDict(Dictionary D);
int hash(int elem);
void insert(Dictionary D, int elem);
void delete(Dictionary D, int elem);
void populate(Dictionary D);
// bool isMember(Dictionary D);

void initDict(Dictionary D)
{
    int x;
    for(x=0; x<PRIME_DATA_SIZE; x++)
    {
        D[x] = EMPTY;
    }

    last = x;

    // printf("last index: %d\n", last);
}

void displayDict(Dictionary D)
{
    int x;
    printf("\n===\nPRIME DATA AREA\n");
    for(x=0; x<PRIME_DATA_SIZE; x++)
    {
        printf("D[%d]: ", x);
        switch(D[x])
        {
            case EMPTY: printf("Empty\n"); break;
            case DELETED: printf("Deleted\n"); break;
            default: printf("%d\n", D[x]);
        }
    }

    printf("\n===\nSYNONYM: \n");
    for(; last!= x && x<SIZE; x++)
    {
        printf("D[%d]: %d\n", x, D[x]);
    }

    printf("\n\n");
}

int hash(int elem)
{
    return elem%SIZE;
}

void insert(Dictionary D, int elem)
{
    int key;
    key = hash(elem);

    if(last<SIZE && D[key]!=elem)
    {
        if(D[key]==EMPTY || D[key]==DELETED)
        {
            D[key] = elem;
        }
        else
        {
            int ctr;
            for(ctr=PRIME_DATA_SIZE; ctr<SIZE && D[ctr]!=elem; ctr++){}
            if(ctr==SIZE)
            {
                D[last] = elem;
                last++;
            }
        }
    }
    else
    {
        printf("\n\t>> Cannot add anymore elements <<\n\n");
    }


void populate(Dictionary D)
{
    insert(D, 0);
    insert(D, 20);
    insert(D, 30);
    insert(D, 40);
    insert(D, 50);
    insert(D, 60);
    insert(D, 70);
    insert(D, 80);
    insert(D, 90);
    insert(D, 100);
    insert(D, 1000);
    insert(D, 990);
    insert(D, 11090);
}

int main()
{
    Dictionary D;
    printf("test init\n");
    initDict(D);
    printf("test populate\n");
    populate(D);

    printf("test display\n");
    displayDict(D);

    return 0;
}