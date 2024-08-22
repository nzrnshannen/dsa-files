#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 5

typedef struct{
    char *elemPtr;
    int count;
}List;

void initializeList(List *L);
void insertElem(List *L, char elem);
void displayList(List L);
void deleteFirstOccur(List *L, char elem);
void deleteAllOccur(List *L, char elem);
void deleteAtPos(List *L, int pos);
bool isFull(List L);
bool isEmpty(List L);
int search(List L, char elem);
void emptyListMsg();
void fullListMsg();
void elemNotFound(char elem);
void clearList(List *L);
void populate(List *L);
void displayList(List L);

bool isFull(List L)
{
    return (L.count==SIZE) ? true : false;
}

bool isEmpty(List L)
{
    return (L.count==0) ? true : false;
}

void emptyListMsg()
{
    printf("\n\n\tList is empty!\n\n");
}

void fullListMsg()
{
    printf("\n\n\tList is full!\n\n");
}

void initializeList(List *L)
{
    L->count=0;
    L->elemPtr = (char*)malloc(sizeof(char) * SIZE);
    if(L->elemPtr==NULL)
    {
        printf("Memory allocation failure\n");
        exit(1);
    }
}

void insertElem(List *L, char elem)
{
    if(isFull(*L))
    {
        printf("\n\tList is full. Reallocating...\n");
        int INIT_CAPACITY = L->count;
        L->elemPtr = (char*)realloc(L->elemPtr, sizeof(char) * (INIT_CAPACITY + 1));

        if(L->elemPtr==NULL)
        {
            printf("\nMemory allocation failure\n");
            exit(1        }
    }
    
    L->elemPtr[L->count++] = elem;
    printf("\n\n\tSuccessfully inserted elemented %c.\n\n", elem);
}

void deleteFirstOccur(List *L, char elem)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        int retval = search(*L, elem);
        
        if(retval!=-1)
        {
            int y;
            for(y=retval; y<L->count-1; y++)
            {
                L->elemPtr[y] = L->elemPtr[y+1];
            }
            L->count--;
        }
        else
        {
            elemNotFound(elem);
        }
    }
}

int search(List L, char elem)
{
    int x;
    for(x=0; x<L.count && L.elemPtr[x]!=elem; x++){}

    return (L.elemPtr[x] == elem) ? x : -1;
}

void elemNotFound(char elem)
{
    printf("\n >> Element %c not found. <<\n\n", elem);
}

void deleteAllOccur(List *L, char elem)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        bool isEqual = false;
        int x;
        for(x=0; x<L->count; )
        {
            if(L->elemPtr[x]==elem)
            {
                isEqual = true;
                int y;
                for(y=0; y<L->count-1; y++)
                {
                    L->elemPtr[y] = L->elemPtr[y+1];
                }
                L->count--;
            }
            else
            {
                x++;
            }
        }

        if(!isEqual)
        {
            elemNotFound(elem);
        }
    }
}

void deleteAtPos(List *L, int pos)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else if(pos<=0 || pos>L->count)
    {
        printf("\n\t >> Invalid position! Position starts at 1 and ends at %d. << \n", L->count);
    }
    else
    {
        int x;
        for(x=0; x<pos-1; x++){}

        for(; x<L->count-1; x++)
        {
            L->elemPtr[x] = L->elemPtr[x+1];
        }

        L->count--;
    }
}

void displayList(List L)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n===\nList: ");
        int x;
        for(x=0; x<L.count; x++)
        {
            printf("%c ", L.elemPtr[x]);
        }
        printf("\n\n");
    }
}

void populate(List *L)
{
    insertElem(L, 'A');
    insertElem(L, 'B');
    insertElem(L, 'C');
    insertElem(L, 'D');
    insertElem(L, 'E');
    insertElem(L, 'F');
    insertElem(L, 'G');
}

void clearList(List *L)
{
    free(L->elemPtr);
    L->elemPtr=NULL;
}

int main()
{
    List listOne;
    initializeList(&listOne);
    populate(&listOne);
    displayList(listOne);
    printf("Elem count = %d\n", listOne.count);
    
    clearList(&listOne);
    return 0;
}
