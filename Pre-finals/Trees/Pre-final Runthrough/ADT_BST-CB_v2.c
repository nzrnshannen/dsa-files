#include<stdio.h>
#include<stdbool.h>
#define MAX 15

typedef struct{
    int elem;
    int LC;
    int RC;
}nodeType;

typedef struct{
    nodeType Node[MAX];
    int avail;
}VirtualHeap;

typedef int BST;

void initVHeap(VirtualHeap *VH);
void initBST(BST *Tree);
void insertElem(BST *Tree, VirtualHeap *VH, int elem);
void deleteElem(BST *Tree, VirtualHeap *VH, int elem);
int deleteMin(BST *Tree, VirtualHeap *VH);
int deleteMax(BST *Tree, VirtualHeap *VH);

//display
void levelOrder(BST Tree, VirtualHeap VH);
void postOrder(BST Tree, VirtualHeap VH);
void preOrder(BST Tree, VirtualHeap VH);
void inOrder(BST Tree, VirtualHeap VH);

int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int ndx);
void populate(BST *Tree, VirtualHeap *VH);

void populate(BST *Tree, VirtualHeap *VH)
{
    insertElem(Tree, VH, 2);
    insertElem(Tree, VH, 5);
    insertElem(Tree, VH, 10);
    insertElem(Tree, VH, 19);
    insertElem(Tree, VH, 27);
}

void initVHeap(VirtualHeap *VH)
{
    int x;
    VH->avail = MAX-1;
    for(x=VH->avail; x>=0; x--)
    {
        VH->Node[x].LC = x-1;
        VH->Node[x].RC = x-1;
    }
}

void initBST(BST *Tree)
{
    *Tree = -1;
}

void insertElem(BST *Tree, VirtualHeap *VH, int elem)
{   
    BST *trav;
    for(trav=Tree; *trav!=-1 && VH->Node[*trav].elem!=elem; )
    {
        trav = (elem< VH->Node[*trav].elem) ? &(VH->Node[*trav].LC) : &(VH->Node[*trav].RC);
    }

    if(*trav==-1)
    {
        int ndx;
        ndx = allocSpace(VH);
        if(ndx!=-1)
        {
            VH->Node[ndx].elem = elem;
            VH->Node[ndx].LC = -1;
            VH->Node[ndx].RC = -1;
            *trav = ndx;
        }
    }
}

void deleteElem(BST *Tree, VirtualHeap *VH, int elem)
{
    BST *trav;
    for(trav=Tree; *trav!=-1 && VH->Node[*trav].elem!=elem; )
    {
        trav = (elem < VH->Node[*trav].elem) ? &VH->Node[*trav].LC : &VH->Node[*trav].RC;
    }

    if(*trav!=-1)
    {
        BST temp;
        temp = *trav;

        if(VH->Node[temp].LC==-1 || VH->Node[temp].RC==-1)
        {
            *trav = (VH->Node[temp].LC!=-1) ? VH->Node[temp].LC : VH->Node[temp].RC;
            deallocSpace(VH, temp);
        }
        else
        {
            //using the successor
            VH->Node[temp].elem = deleteMin(&temp, VH);
        }
    }
}

int deleteMin(BST *Tree, VirtualHeap *VH)
{
    BST *trav, temp;
    int num;

    for(trav=Tree; *trav!=-1 && VH->Node[*trav].LC!=-1; trav = &VH->Node[*trav].LC){}

    if(*trav!=-1)
    {
        temp = *trav;
        num = VH->Node[temp].elem;
        *trav = VH->Node[temp].RC;
        deallocSpace(VH, temp);
    }

    return num;
}

int deleteMax(BST *Tree, VirtualHeap *VH)
{
    BST *trav, temp;
    int num;

    for(trav=Tree; *trav!=-1 && VH->Node[*trav].RC!=-1; trav = &VH->Node[*trav].RC){}

    if(*trav!=-1)
    {
        temp = *trav;
        num = VH->Node[temp].elem;
        *trav = VH->Node[temp].LC;
        deallocSpace(VH, temp);
    }

    return num;
}

int allocSpace(VirtualHeap *VH)
{
    int retval = VH->avail;

    if(retval!=-1)
    {
        VH->avail = VH->Node[retval].RC;
    }

    return retval;
}

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx< MAX)
    {
        VH->Node[ndx].RC = VH->avail;
        VH->avail = ndx;
    }
}

void preOrder(BST Tree, VirtualHeap VH)
{
    if(Tree!=-1)
    {
        printf("%d ", VH.Node[Tree].elem);
        preOrder(VH.Node[Tree].LC, VH);
        preOrder(VH.Node[Tree].RC, VH);
    }
}

void postOrder(BST Tree, VirtualHeap VH)
{
    if(Tree!=-1)
    {
        postOrder(VH.Node[Tree].LC, VH);
        postOrder(VH.Node[Tree].RC, VH);
        printf("%d ", VH.Node[Tree].elem);
    }
}

void inOrder(BST Tree, VirtualHeap VH)
{
    if(Tree!=-1)
    {
        inOrder(VH.Node[Tree].LC, VH);
        printf("%d ", VH.Node[Tree].elem);
        inOrder(VH.Node[Tree].RC, VH);
    }
}

int main()
{
    VirtualHeap Vheap;
    BST myTree;

    initBST(&myTree);
    initVHeap(&Vheap);
    
    populate(&myTree, &Vheap);

    printf("\nPreorder: ");
    preOrder(myTree, Vheap);
    printf("\nPostorder: ");
    postOrder(myTree, Vheap);
    printf("\nInorder: ");
    inOrder(myTree, Vheap);

    deleteElem(&myTree, &Vheap, 5);

    printf("\n================\nAfter Deletion: ");
    printf("\nPreorder: ");
    preOrder(myTree, Vheap);
    printf("\nPostorder: ");
    postOrder(myTree, Vheap);
    printf("\nInorder: ");
    inOrder(myTree, Vheap);
    return 0;
}
