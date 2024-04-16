#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 15

typedef struct{
    int elem;
    int left;
    int right;
}node;

typedef struct{
    node data;
    int link;
}nodeType;

typedef struct VH{
    nodeType Node[SIZE];
    int avail;
}*VHeap;

typedef struct{
    VHeap vptr;
    int root;
}BST;

void initBST(BST *Tree);
void initVHeap(VHeap *VH);
void populate(BST *Tree);

void insertMem(BST *Tree, int elem);
void deleteMem(BST *Tree, int elem);
int deleteMin(BST *Tree);
int deleteMax(BST *Tree);

void levelOrder(BST Tree);
void inorder(VHeap VH, int root);
void display(BST Tree);


void initBST(BST *Tree)
{
    Tree->root = -1;
}

void initVHeap(VHeap *VH)
{
    int x;
    (*VH)->avail = SIZE-1;
    for(x=(*VH)->avail; x>=0; x--)
    {
        (*VH)->Node[x].link = x-1;
    }
}

void populate(BST *Tree)
{
    insertMem(Tree, 3);
    insertMem(Tree, 10);
    insertMem(Tree, -7);
    insertMem(Tree, 25);
    insertMem(Tree, 5);
}

void insertMem(BST *Tree, int elem)
{
    int ndx;
    int *trav;

    for(trav=&Tree->root; *trav!=-1 && Tree->vptr->Node[*trav].data.elem!=elem; )
    {
        trav = (elem<Tree->vptr->Node[*trav].data.elem) ? &Tree->vptr->Node[*trav].data.left : &Tree->vptr->Node[*trav].data.right;
    }

    if(*trav==-1)
    {
        ndx = Tree->vptr->avail;
        Tree->vptr->avail = Tree->vptr->Node[ndx].link;

        Tree->vptr->Node[ndx].link = -1;
        Tree->vptr->Node[ndx].data.elem = elem;
        Tree->vptr->Node[ndx].data.left = -1;
        Tree->vptr->Node[ndx].data.right = -1;
        *trav = ndx;
    }
}

int deleteMin(BST *Tree)
{
    int num, *trav;
    int temp;

    for(trav=&Tree->root; *trav!=-1 && Tree->vptr->Node[*trav].data.left!=-1; trav=&Tree->vptr->Node[*trav].data.left){}

    if(*trav!=-1)
    {
        temp = *trav;
        num = Tree->vptr->Node[temp].data.elem;
        *trav = Tree->vptr->Node[temp].data.right;

        Tree->vptr->Node[temp].link = Tree->vptr->avail;
        Tree->vptr->avail = temp;
    }
    
    return num;
}

int deleteMax(BST *Tree)
{
    int num, *trav;
    int temp;

    for(trav=&Tree->root; *trav!=-1 && Tree->vptr->Node[*trav].data.right!=-1; trav = &Tree->vptr->Node[*trav].data.right){}

    if(*trav!=-1)
    {
        temp = *trav;
        num = Tree->vptr->Node[temp].data.elem;
        *trav = Tree->vptr->Node[temp].data.right;

        Tree->vptr->Node[temp].link = Tree->vptr->avail;
        Tree->vptr->avail = temp;
    }

    return num;
}

void deleteMem(BST *Tree, int elem)
{
    int *trav;

    for(trav=&Tree->root; *trav!=-1 && Tree->vptr->Node[*trav].data.elem!=elem; )
    {
        trav = (elem < Tree->vptr->Node[*trav].data.left) ? &Tree->vptr->Node[*trav].data.left : &Tree->vptr->Node[*trav].data.right;
    }

    if(*trav!=-1)
    {
        int temp;
        temp = *trav;

        if(Tree->vptr->Node[temp].data.left==-1 || Tree->vptr->Node[temp].data.right==-1)
        {
            *trav = (Tree->vptr->Node[temp].data.left!=-1) ? Tree->vptr->Node[temp].data.left : Tree->vptr->Node[temp].data.right;

            Tree->vptr->Node[temp].link = Tree->vptr->avail;
            Tree->vptr->avail = temp;
        }
        else
        {
            //using the successor
            Tree->vptr->Node[temp].data.elem = deleteMin(&Tree->vptr->Node[temp].data.right);
        }
    }
}

void inorder(VHeap VH, int Root)
{
    if(Root!=-1)
    {
        inorder(VH, VH->Node[Root].data.left);
        printf("%d ", VH->Node[Root].data.elem);
        inorder(VH, VH->Node[Root].data.right);
    }
}

int main()
{
    VHeap VH = (VHeap)calloc(1, sizeof(struct VH));
    initVHeap(&VH);

    BST myBST = {VH, -1};
    populate(&myBST);
    printf("\n====\nInorder: ");
    inorder(VH, myBST.root);
    deleteMem(&myBST, 10);

    printf("\nAfter deletion: ");
    inorder(VH, myBST.root);
    return 0;
}

