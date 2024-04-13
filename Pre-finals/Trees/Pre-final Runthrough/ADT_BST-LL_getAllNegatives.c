#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define SIZE 15

typedef struct node{
    int data;
    struct node *LC;
    struct node *RC;
}Cell, *BST;

void initTree(BST *Tree);
void populate(BST *Tree);
void insertMem(BST *Tree, int elem);
void deleteMem(BST *Tree, int elem);
int deleteMin(BST *Tree);
int deleteMax(BST *Tree);
bool isElem(BST Tree, int elem);
BST getAllNegatives(BST Tree, BST negaTree);

void display(BST Tree);
void preorder(BST Tree);
void postorder(BST Tree);
void inorder(BST Tree);
void levelOrder(BST Tree);

void initTree(BST *Tree)
{
    *Tree = NULL;
}

void insertMem(BST *Tree, int elem)
{
    BST *trav;
    for(trav=Tree; *trav!=NULL && (*trav)->data!=elem; )
    {

        trav = (elem < (*trav)->data) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav==NULL)
    {
        *trav = (BST)calloc(1, sizeof(Cell));
        (*trav)->data = elem;
    }
}

int deleteMin(BST *Tree)
{   
    BST *trav, temp;
    int num;

    for(trav=Tree; *trav!=NULL && (*trav)->LC!=NULL; trav=&(*trav)->LC){}

    if(*trav!=NULL)
    {
        temp = *trav;
        num = temp->data;
        *trav = temp->RC; //adopt child of the node to be deleted if there are any
        free(temp); //node finally deleted
    }

    return num;
}   


int deleteMax(BST *Tree)
{
    BST *trav, temp;
    int num;

    for(trav=Tree; *trav!=NULL && (*trav)->RC!=NULL; trav=&(*trav)->RC){}

    if(*trav!=NULL)
    {
        temp = *trav;
        num = temp->data;
        *trav = temp->LC; //adopt child of the node to be deleted if there are any
        free(temp); //node finally deleted
    }
    
    return num;
}

void deleteMem(BST *Tree, int elem)
{
    BST *trav;
    for(trav=Tree; *trav!=NULL && (*trav)->data!=elem; )
    {
        trav = (elem < (*trav)->data) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav!=NULL)
    {
        BST temp;
        temp = *trav;

        if(temp->LC==NULL || temp->RC==NULL)
        {
            *trav = (temp->LC!=NULL) ? temp->LC : temp->RC;
            free(temp);
        }
        else
        {
            //using successor this time
            temp->data = deleteMin(&temp->RC);
        }
    }
}

bool isElem(BST Tree, int elem)
{
    BST trav;
    for(trav=Tree; trav!=NULL && trav->data!=elem; )
    {
        trav = (elem < trav->data) ? trav->LC : trav->RC;
    }

    return (trav!=NULL) ? true : false;
}

void display(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("\n===========\nTREE: ");
        levelOrder(Tree);
        printf("\n");
    }
    else
    {
        printf("\n\n\tEmpty tree!\n\n");
    }
}

void preorder(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("%d ", Tree->data);
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
        printf("%d ", Tree->data);
    }
}

void inorder(BST Tree)
{
    if(Tree!=NULL)
    {
        inorder(Tree->LC);
        printf("%d ", Tree->data);
        inorder(Tree->RC);
    }
}

void levelOrder(BST Tree)
{
    BST tempQueue[SIZE], current;
    int front = 1, rear = 0;

    if(Tree!=NULL)
    {
        for(tempQueue[++rear]=Tree; front!=(rear+1)%SIZE; )
        {
            current = tempQueue[front];
            front = (front+1)%SIZE;

            if(current!=NULL)
            {
                printf("%d ", current->data);

                rear = (rear+1)%SIZE;
                tempQueue[rear] = current->LC;
                rear = (rear+1)%SIZE;
                tempQueue[rear] = current->RC;
            }
        }
    }

    printf("\n");
}

BST getAllNegatives(BST Tree, BST negaTree)
{
    if(Tree!=NULL)
    {
        if(Tree->data<0)
        {
            insertMem(&negaTree, Tree->data);
        }

        negaTree = getAllNegatives(Tree->LC, negaTree);
        negaTree = getAllNegatives(Tree->RC, negaTree);
    }

    return negaTree;
}

void populate(BST *Tree)
{
    insertMem(Tree, 10);
    insertMem(Tree, -1);
    insertMem(Tree, -8);
    insertMem(Tree, 16);
    insertMem(Tree, -2);
}

int main()
{
    BST myTree;
    initTree(&myTree);
    display(myTree);
    populate(&myTree);
    display(myTree);

    BST negaTree = getAllNegatives(myTree, NULL);
    display(negaTree);
    return 0;
}