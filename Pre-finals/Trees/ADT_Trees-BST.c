#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 10

typedef struct cell{
    int data;
    int height;
    struct cell *LC;
    struct cell *RC;
}cellType, *Tree;

void initializeTree(Tree *T);
void populateA(Tree *T);
void insertElem(Tree *T, int node);
void display(Tree T);
void levelOrder(Tree T);

void deleteElem(Tree *T, int node);
int deleteMin(Tree *T);
int deleteMax(Tree *T);

void preorderNonRecursive(Tree T);
void inorderNonRecursive(Tree T);
void postorderNonRecursive(Tree T);

void preorderRecursive(Tree T);
void postorderRecursive(Tree T);
void inorderRecursive(Tree T);


void initializeTree(Tree *T)
{
    *T = NULL;
}

void insertElem(Tree *T, int node)
{
    Tree *trav;
    for(trav=T; *trav!=NULL && (*trav)->data!=node; )
    {
        trav = (node < (*trav)->data) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav==NULL)
    {
        *trav = (Tree)calloc(1, sizeof(cellType));
        (*trav)->data = node;
    }
}

void levelOrder(Tree T)
{
    Tree tempQueue[SIZE], current;
    int front = 1, rear = 0;

    for(tempQueue[++rear] = T; front!=(rear+1)%SIZE; )
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

void populateA(Tree *T)
{
    insertElem(T, 1);
    insertElem(T, 0);
    insertElem(T, 10);
}

int deleteMin(Tree *T)
{
    int num =-1;
    Tree *trav, temp;

    for(trav = T; *trav!=NULL && (*trav)->LC!=NULL; trav = &(*trav)->LC){}

    if(*trav!=NULL)
    {
        temp = *trav;
        num = temp->data;
        *trav = temp->RC;
        free(temp);
    }
    return num;
}

int deleteMax(Tree *T)
{
    int num = -1;
    Tree *trav, temp;

    for(trav = T; *trav!=NULL && (*trav)->RC!=NULL; trav = &(*trav)->RC){}

    if(*trav!=NULL)
    {
        temp = *trav;
        num = temp->data;
        *trav = temp->LC; 
        free(temp);
    }
    return num;
}

void deleteElem(Tree *T, int node)
{
    Tree *trav;

    for(trav=T; *trav!=NULL && (*trav)->data!=node; )
    {
        trav = (node < (*trav)->data) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav!=NULL)
    {
        Tree temp; 
        temp = *trav;

        if(temp->LC==NULL || temp->RC==NULL)
        {
            *trav = (temp->LC!=NULL) ? temp->LC : temp->RC;.
            free(temp);
        }
        else
        {
            (*trav)->data= deleteMax(&temp->LC);
        }
        
    }
}

void preorderNonRecursive(Tree T)
{
    Tree tempStack[SIZE], current;
    int top = -1;;

    if(T!=NULL)
    {
        printf("\nPREORDER: ");
        for(tempStack[++top] = T; top!=-1; )
        {
            current = tempStack[top];

            if(current!=NULL)
            {
                printf("%d ", current->data);
                tempStack[++top] = current->LC;
            }
            else
            {
                current = tempStack[--top]; //go back to the previous node by doing pop()
                tempStack[top] = current->RC; //push right child (previously, we pushed the left child)
            }
        }
        printf("\n");
    }
}

void preorderRecursive(Tree T)
{
    
}
void display(Tree T)
{
    if(T==NULL)
    {
        printf("\n\n\tEmpty tree!\n\n");
    }
    else
    {
        printf("\n==============================\n Tree: ");
        levelOrder(T);
        printf("\n");
    }
}

int main()
{
    Tree myTree_1;
    initializeTree(&myTree_1);
    display(myTree_1);
    populateA(&myTree_1);
    display(myTree_1);

    preorderNonRecursive(myTree_1);

    return 0;
}