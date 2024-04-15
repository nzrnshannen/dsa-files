#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define SIZE 30

typedef struct node{
    int data;
    struct node *LC;
    struct node *RC;
}*BST;

void initializeBST(BST *Tree);
bool isMember(BST Tree, int elem);
void populate(BST *Tree);

void insertMem(BST *Tree, int elem);
void deleteMem(BST *Tree, int elem);
int deleteMin(BST *Tree);
int deleteMax(BST *Tree);

void display(BST Tree);
void preorder(BST Tree);
void postorder(BST Tree);
void inorder(BST Tree);
void levelOrder(BST Tree);
BST getAllNegatives(BST Tree, BST newTree); //recursive
void getEven(BST Tree, BST* newTree); //non recursive

void initializeBST(BST *Tree)
{
    *Tree = NULL;
}

bool isMember(BST Tree, int elem)
{
    BST trav;
    for(trav=Tree; trav!=NULL && elem!=trav->data; )
    {
        trav = (elem < trav->data) ? trav->LC : trav->RC;
    }

    return (trav!=NULL) ? true : false;
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
        *trav = (BST)calloc(1, sizeof(struct node));
        (*trav)->data = elem;
    }
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
            //using successor
            temp->data = deleteMin(&temp->RC);
        }
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
        *trav = temp->RC;

        free(temp);
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
        temp= *trav;
        num = temp->data;
        *trav = temp->LC;

        free(temp);
    }

    return num;
}

void display(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("\n======================\nTree: ");
        levelOrder(Tree);
        printf("\n");
    }
    else
    {
        printf("\n\tEmpty tree!\n\n");
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
    int front=1, rear=0;

    if(Tree!=NULL)
    {
        for(tempQueue[++rear]=Tree; front!=(rear+1)%SIZE; )
        {
            current = tempQueue[front];
            front=(front+1)%SIZE;

            if(current!=NULL)
            {
                printf("%d ", current->data);

                rear=(rear+1)%SIZE;
                tempQueue[rear] = current->LC;
                rear=(rear+1)%SIZE;
                tempQueue[rear] = current->RC;
            }
        }
    }
}

BST getAllNegatives(BST Tree, BST newTree)
{
    if(Tree!=NULL)
    {
        if(Tree->data < 0)
        {
            insertMem(&newTree, Tree->data);
        }

        newTree = getAllNegatives(Tree->LC, newTree);
        newTree = getAllNegatives(Tree->RC, newTree);
    }

    return newTree;
}

void getEven(BST Tree, BST* newTree)
{
    BST tempQueue[SIZE], current;
    int front=1, rear=0;

    if(Tree!=NULL)
    {
        for(tempQueue[++rear]=Tree; front!=(rear+1)%SIZE; )
        {
            current = tempQueue[front];
            front = (front+1)%SIZE;

            if(current!=NULL)
            {
                if(current->data%2==0)
                {
                    insertMem(newTree, current->data);
                }

                rear=(rear+1)%SIZE;
                tempQueue[rear] = current->LC;
                rear=(rear+1)%SIZE;
                tempQueue[rear] = current->RC;
            }
        }
    }
}

void populate(BST *Tree)
{
    insertMem(Tree, 10);
    insertMem(Tree, 3);
    insertMem(Tree, -4);
    insertMem(Tree, 9);
    insertMem(Tree, -10);
}

int main()
{
    BST myTree;
    initializeBST(&myTree);
    display(myTree);

    populate(&myTree);

    display(myTree);

    BST evenBST;
    initializeBST(&evenBST);
    BST negaBST;
    
    negaBST = getAllNegatives(myTree, NULL);
    getEven(myTree, &evenBST);

    printf("\nNegative Tree: ");
    display(negaBST);

    printf("\nEven Tree: ");
    display(evenBST);
    
    return 0;
}
