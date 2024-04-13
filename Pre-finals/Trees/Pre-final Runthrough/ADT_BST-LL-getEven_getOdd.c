#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define SIZE 15

typedef struct node{
    int elem;
    struct node *LC;
    struct node *RC;
}Cell, *BST;

void initTree(BST *Tree);
void populate(BST *Tree);
bool isMember(BST Tree, int elem);

void insertMem(BST *Tree, int elem);
void populate(BST *Tree);
BST getEven(BST Tree, BST evenTree);
BST getOdd(BST Tree, BST oddTree);
void insertMem(BST *Tree, int elem);
void deleteMem(BST *Tree, int elem);
int deleteMin(BST *Tree);
int deleteMax(BST *Tree);

void display(BST Tree);
void levelOrder(BST Tree);
void preorder(BST Tree);
void postorder(BST Tree);
void inorder(BST Tree);

void initTree(BST *Tree)
{
    *Tree = NULL;
}

bool isMember(BST Tree, int elem)
{
    BST trav;
    for(trav=Tree; trav!=NULL && trav->elem!=elem; )
    {
        trav = (elem < trav->elem) ? trav->LC : trav->RC;
    }

    return (trav!=NULL) ? true : false;
}

void insertMem(BST *Tree, int elem)
{
    BST *trav;
    for(trav=Tree; *trav!=NULL && (*trav)->elem!=elem; )
    {
        trav = (elem < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav==NULL)
    {
        *trav = (BST)calloc(1, sizeof(Cell));
        (*trav)->elem = elem;
    }
}

int deleteMin(BST *Tree)
{
    int num;
    BST *trav, temp;

    for(trav=Tree; *trav!=NULL && (*trav)->LC!=NULL; trav=&(*trav)->LC){}

    if(*trav!=NULL)
    {
        temp = *trav;
        num = temp->elem;
        *trav = temp->RC;
        free(temp);
    }

    return num;
}

int deleteMax(BST *Tree)
{
    int num;
    BST *trav, temp;

    for(trav=Tree; *trav!=NULL && (*trav)->RC!=NULL; trav=&(*trav)->RC){}

    if(*trav!=NULL)
    {
        temp = *trav;
        num = temp->elem;
        *trav = temp->LC;
        free(temp);
    }

    return num;
}

void deleteMem(BST *Tree, int elem)
{
    BST *trav;

    for(trav=Tree; *trav!=NULL && (*trav)->elem!=elem; )
    {
        trav = (elem < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav!=NULL)
    {
        BST temp;
        temp = *trav;
        
        if(temp->LC==NULL && temp->RC==NULL)
        {
            *trav = (temp->LC!=NULL) ? temp->LC : temp->RC;
            free(temp);
        }
        else
        {
            //using predecessor this time
            temp->elem = deleteMax(&temp->LC);
        }
    }
}

void display(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("\n===========================\nTREE: ");
        levelOrder(Tree);
        printf("\n\n");
    }
    else
    {
        printf("\n\t\tEmpty Tree!\n\n");
    }
}

void levelOrder(BST Tree)
{
    BST tempQueue[SIZE], current;
    int front = 1, rear = 0;

    if(Tree!=NULL)
    {
        for(tempQueue[++rear] = Tree; front!=(rear+1)%SIZE; )
        {
            current = tempQueue[front];
            front = (front+1)%SIZE;

            if(current!=NULL)
            {
                printf("%d ", current->elem);

                rear = (rear+1)%SIZE;
                tempQueue[rear] = current->LC;
                rear = (rear+1)%SIZE;
                tempQueue[rear] = current->RC;
            }
        }  
    }
}

void preorder(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("%d ", Tree->elem);
        preorder(Tree->LC);
        preorder(Tree->RC);
    }
}

void postorder(BST Tree)
{
    if(Tree!=NULL)
    {
        postorder(Tree->LC);
        postorder(Tree->RC);
        printf("%d ", Tree->elem);
    }
}

void inorder(BST Tree)
{
    if(Tree!=NULL)
    {
        inorder(Tree->LC);
        printf("%d ", Tree->elem);
        inorder(Tree->RC);
    }
}

BST getOdd(BST Tree, BST oddTree)
{
    if(Tree!=NULL)
    {
        if(Tree->elem%2==1)
        {
            insertMem(&oddTree, Tree->elem);
        }

        oddTree = getOdd(Tree->LC, oddTree);
        oddTree = getOdd(Tree->RC, oddTree);
    }
    
    return oddTree;
}

BST getEven(BST Tree, BST evenTree)
{
    if(Tree!=NULL)
    {
        if(Tree->elem%2==0)
        {
            insertMem(&evenTree, Tree->elem);
        }
        evenTree = getEven(Tree->LC, evenTree);
        evenTree = getEven(Tree->RC, evenTree);
    }
    
    return evenTree;
}
void populate(BST *Tree)
{
    insertMem(Tree, 10);
    insertMem(Tree, 30);
    insertMem(Tree, 5);
    insertMem(Tree, 19);
    insertMem(Tree, 8);
    insertMem(Tree, 70);
}

int main()
{
    BST myTree;
    initTree(&myTree);
    display(myTree);

    populate(&myTree);
    display(myTree);

    BST evenTree = getEven(myTree, NULL);
    printf("EVEN");
    display(evenTree);

    BST oddTree = getOdd(myTree, NULL);
    printf("ODD");
    display(oddTree);

    return 0;
}