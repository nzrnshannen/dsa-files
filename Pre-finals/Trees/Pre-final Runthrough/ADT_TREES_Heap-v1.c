#include<stdio.h>
#include<stdbool.h>
#define SIZE 15


typedef struct{
    int elem[SIZE];
    int lastNdx;
    int heapLastNdx;
}Heap;

void initHeap(Heap *Heap);
void populateHeapV1(Heap *Heap);
void populateHeapV2(Heap *Heap);

void insertMaxV1(Heap *Heap, int elem); //swapping method
void insertMinV1(Heap* Heap, int elem); //swapping method
void insertMaxV2(Heap *Heap, int elem); //shifting method
void insertMinV2(Heap *Heap, int elem); //shifting method

int deleteMaxV1(Heap *Heap); //swapping method
int deleteMinV1(Heap *Heap); //swapping method

void display(Heap Heap);
void displayHeap(Heap Heap);

void initHeap(Heap *Heap)
{
    Heap->heapLastNdx=-1;
    Heap->lastNdx=-1;
}

void display(Heap Heap)
{
    printf("\n=============================\nContents: ");
    int x;
    for(x=0; x<=Heap.lastNdx; x++)
    {
        printf("%d ", Heap.elem[x]);
    }

    printf("\nTotal elements in the heap: %d/%d\n\n", Heap.heapLastNdx+1, Heap.lastNdx+1);
}

void populateHeapV1(Heap *Heap)
{
    insertMaxV1(Heap, 4);
    insertMaxV1(Heap, 5);
    insertMaxV1(Heap, 9);
    insertMaxV1(Heap, 2);
}

void populateHeapV2(Heap *Heap)
{
    insertMaxV2(Heap, 3);
    insertMaxV2(Heap, 19);
    insertMaxV2(Heap, 16);
    insertMaxV2(Heap, 8);
}

void populateHeapV2b(Heap *Heap)
{
    insertMinV1(Heap, 2);
    insertMinV1(Heap, 4);
    insertMinV1(Heap, 20);
    insertMinV1(Heap, 10);
}

void insertMaxV1(Heap* Heap, int elem) //swapping method
{
    if(Heap->lastNdx+1<SIZE)
    {
        int parent, child;
        int temp; //for swapping
        Heap->elem[++Heap->lastNdx] = elem; //inserting at the first available space
        child = Heap->lastNdx;

        bool isHeap=false;

        for(parent=(child-1)/2; isHeap==false && parent>=0; parent=(child-1)/2)
        {
            if(Heap->elem[parent] >= Heap->elem[child])
            {
                isHeap = true;
            }
            else
            {
                //swapping method
                temp = Heap->elem[parent];
                Heap->elem[parent] = Heap->elem[child];
                Heap->elem[child] = temp;

                //update value of child (child's new value will be the parent value)
                //this is to avoid infinite loop caused by child
                //remember: insertion is an upward process towards the root
                child = parent;
            }
        }
        Heap->heapLastNdx++;
    }
}

void insertMinV1(Heap *Heap, int elem) //swapping method
{
    if(Heap->lastNdx+1<SIZE)
    {
        int parent, child;
        int temp; //for swapping
        Heap->elem[++Heap->lastNdx] = elem; //inserting at the first available space
        child = Heap->heapLastNdx;

        bool isHeap=false;

        for(parent=(child-1)/2; isHeap==false && parent>=0; parent=(child-1)/2)
        {
            if(Heap->elem[parent] <= Heap->elem[child])
            {
                isHeap = true;
            }
            else
            {
                //swapping 
                temp = Heap->elem[parent];
                Heap->elem[parent] = Heap->elem[child];
                Heap->elem[child] = temp;

                //to avoid infinite loop, change value of child by its parent value
                child = parent;
            }
        }
        Heap->heapLastNdx++;
    }

}

void insertMaxV2(Heap *Heap, int elem) //shifting method
{
    if(Heap->lastNdx+1<SIZE)
    {
        int x;

        Heap->lastNdx++;
        
        for(x=Heap->lastNdx; x>0 && Heap->elem[x-1] < elem; x--)
        {
            Heap->elem[x] = Heap->elem[x-1];
        }

        Heap->elem[x] = elem;
        Heap->heapLastNdx++;
    }
}   

void insertMinV2(Heap *Heap, int elem)//shifting method
{
    if(Heap->lastNdx+1<SIZE)
    {
        int x;

        Heap->lastNdx++;

        for(x=Heap->lastNdx; x>0 && Heap->elem[x] > elem; x--)
        {
            Heap->elem[x] = Heap->elem[x-1];
        }

        Heap->elem[x] = elem;
        Heap->heapLastNdx++;

    }
}

int deleteMaxV1(Heap *Heap) //swapping method
{
    int retval = -1;
    if(Heap->heapLastNdx!=-1)
    {
        int temp; //for swapping
        int parent, successor;
        retval = Heap->elem[0];
        Heap->elem[0] = Heap->elem[Heap->heapLastNdx];
        Heap->elem[Heap->heapLastNdx--] = retval;
        int last = Heap->heapLastNdx; //stores modified value of heapLastNdx

        bool isHeap = false;

        for(parent=0; isHeap==false && parent <= (last-1)/2; parent=successor) //from root to leaf 
        {
            successor = (Heap->elem[parent*2+1] <= Heap->elem[parent*2+2]) ? parent*2+1 : parent*2+2;

            if(Heap->elem[parent] >= Heap->elem[successor])
            {
                isHeap = true;
            }
            else
            {
                temp = Heap->elem[parent];
                Heap->elem[parent] = Heap->elem[successor];
                Heap->elem[successor] = temp;
            }
        }
    }

    return retval;
}

int deleteMinV1(Heap *Heap)
{
    int retval=-1;
    if(Heap->heapLastNdx+1 < SIZE)
    {
        int temp;
        int parent, successor;
        retval = Heap->elem[0];
        Heap->elem[0] = Heap->elem[Heap->heapLastNdx];
        Heap->elem[Heap->heapLastNdx--] = retval;
        int last = Heap->heapLastNdx;

        bool isHeap = false;

        for(parent=0; isHeap==false && parent<=(last-1)/2; parent=successor)
        {
            successor = (Heap->elem[parent*2+1] < Heap->elem[parent*2+2]) ? parent*2+1 : parent*2+2;

            if(Heap->elem[parent]>= Heap->elem[successor])
            {
                isHeap= true;
            }
            else
            {
                temp = Heap->elem[parent];
                Heap->elem[parent] = Heap->elem[successor];
                Heap->elem[successor] = Heap->elem[parent];
            }
        }
    }

    return retval;
}

void displayHeap(Heap Heap)
{
    printf("\n=============\nHeap Contents: ");
    int x;
    for(x=0; x<=Heap.heapLastNdx; x++)
    {
        printf("%d ", Heap.elem[x]);
    }

    printf("\n");
}

int main()
{
    //uses the swapping method
    Heap myMaxHeapv1;
    initHeap(&myMaxHeapv1);
    populateHeapV1(&myMaxHeapv1);
    display(myMaxHeapv1);
    
    Heap myMinHeapv1;
    initHeap(&myMinHeapv1);
    populateHeapV2b(&myMinHeapv1);
    display(myMinHeapv1);

    //uses the shifting method
    Heap myMaxHeapv2;
    initHeap(&myMaxHeapv2);
    populateHeapV2(&myMaxHeapv2);
    display(myMaxHeapv2);

    printf("\nDeleted element in Max Heap V1: %d\n", deleteMaxV1(&myMaxHeapv1));
    printf("Deleted element in Min Heap 1: %d\n", deleteMinV1(&myMinHeapv1));

    display(myMaxHeapv1);
    displayHeap(myMaxHeapv1);

    display(myMinHeapv1);
    displayHeap(myMinHeapv1); 

    return 0;
}