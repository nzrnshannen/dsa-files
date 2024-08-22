#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 15

typedef struct{
    int day, month, year;
}Date;
typedef struct{
    char prodName[20];
    float prodPrice;
    int prodQty;
    Date expDate;
}Product;
typedef struct node{
    Product item;
    struct node *LC;
    struct node *RC;
}Cell, *BST;

void initTree(BST * Tree);
void populate(BST *Tree);
void insertMem(BST *Tree, Product elem);
void deleteMem(BST *Tree, Product elem);

void preorder(BST Tree);
void postorder(BST Tree);
void inorder(BST Tree);

void levelOrder(BST Tree);
void display(BST Tree);

void initTree(BST *Tree)
{
    *Tree = NULL;
}


void insertMem(BST *Tree, Product elem)
{
    BST *trav;
    for(trav=Tree; *trav!=NULL && strcmp(elem.prodName, (*trav)->item.prodName)!=0; )
    {
        trav = (strcmp(elem.prodName, (*trav)->item.prodName) > 0) ? &(*trav)->RC : &(*trav)->LC;
    }

    if(*trav==NULL)
    {
        *trav = (BST)calloc(1, sizeof(Cell));
        (*trav)->item= elem;
    }
}


void deleteMem(BST *Tree, Product elem)
{
    BST *trav;

    //searching for elem if it exists in the BST
    for(trav=Tree; *trav!=NULL && strcmp(elem.prodName, (*trav)->item.prodName)!=0; )
    {
        trav = (strcmp(elem.prodName, (*trav)->item.prodName) > 0) ? &(*trav)->RC : &(*trav)->LC;
    }

    if(*trav!=NULL) //if the node to be deleted is found
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
            //using the successor (we can also use the predecessor but we do = deleteMin(&temp->RC) instead ^_^)

            //using temp (PN) only since we're gonna be modifying the data part only
            Product val;
            BST *trav2, temp2;

            for(trav2=Tree; *trav!=NULL && (*trav2)->RC!=NULL; trav2=&(*trav2)->RC){}

            if(*trav2!=NULL)
            {
                temp2 = *trav2;
                val = temp2->item;
                *trav2 = temp2->LC;
                free(temp2);
            }

            temp->item = val;
        }
    }
}

void preorder(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("%s ", Tree->item.prodName);
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
        printf("%s ", Tree->item.prodName);
    }
}

void inorder(BST Tree)
{
    if(Tree!=NULL)
    {
        inorder(Tree->LC);
        printf("%s ", Tree->item.prodName);
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
            front = (front+1)%SIZE;

            if(current!=NULL)
            {
                printf("%s ", current->item.prodName);

                rear = (rear+1)%SIZE;
                tempQueue[rear] = current->LC;
                rear= (rear+1)%SIZE;
                tempQueue[rear] = current->RC;
            }
        }
    }
}

void display(BST Tree)
{
    if(Tree!=NULL)
    {
        printf("\n===================================\nTree:\n");
        levelOrder(Tree);
        printf("\n\n");
    }
    else
    {
        printf("\n\n\tEmpty Tree!\n\n");
    }
}

int main()
{
    BST myTree;
	Product p1 = {"Cadbury", 100.00, 30, {12, 7, 2024}};
	Product p2 = {"Ferrero", 200.00, 30, {22, 1, 2024}};
	Product p3 = {"Hershey", 150.00, 20, {2, 4, 2024}};
	Product p4 = {"Lindt", 235.00, 50, {24, 11, 2024}};
	Product p5 = {"Goya", 90.00, 100, {8, 8, 2024}};
    
    initTree(&myTree);
    insertMem(&myTree, p1);
    insertMem(&myTree, p2);
    insertMem(&myTree, p3);
    insertMem(&myTree, p4);
    insertMem(&myTree, p5);

    display(myTree);

    deleteMem(&myTree, p2);
    display(myTree); 

    return 0;
}