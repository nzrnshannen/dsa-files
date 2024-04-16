#include<stdio.h>
#include<stdbool.h>
#define MAX 15

typedef struct{
    int elem[MAX];
    int lastNdx;
    int heapLastNdx;
}Heap;

void initialize(Heap *H)
{
    H->heapLastNdx=-1;
    H->lastNdx=-1;
}

