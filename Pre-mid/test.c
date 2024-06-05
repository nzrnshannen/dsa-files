#include<stdio.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
	int elem[MAX];
	int top; //stores last index of topmost elem
}STACK;

void initStack(STACK *S);
void populateStack(STACK *S);
void display(STACK S);
void Push(STACK *S, int elem);
void Pop(STACK *S);
int Top(STACK S);
bool isEmpty(STACK S);
bool isFull(STACK S);

void initStack(STACK *S)
{
	S->top=-1;
}

int Top(STACK S)
{
	return (isEmpty(S)==0) ? S.elem[S.top] : -1;
}

bool isEmpty(STACK S)
{
	return (S.top==-1) ? true : false;
}

bool isFull(STACK S)
{
	return (S.top==MAX-1) ? true : false;
}

void Push(STACK *S, int elem)
{
	if(!isFull(*S))
	{
		S->top++;
		S->elem[S->top]=elem;
	}
}

void Pop(STACK *S)
{
	if(!isEmpty(*S))
	{
		S->top--;
	}
}

void display(STACK S)
{
	STACK tempStack;
	initStack(&tempStack);
	
	printf("\n===\nStack: ");
	while(!isEmpty(S))
	{
		int elem;
		elem = Top(S);
		Push(&tempStack, elem);
		Pop(&S);
	}
	
	while(!isEmpty(tempStack))
	{
		int elem;
		elem = Top(tempStack);
		printf("%d ", elem);
		Push(&S, elem);
		Pop(&tempStack);
	}
	
	printf("\n\n");
}

void populateStack(STACK *S)
{
	Push(S, 1);
	Push(S, 3);
	Push(S, 4);
	Push(S, 5);
	Push(S, 10);
	Push(S, 20); //should not be included in the stack
}

int main()
{
	STACK myStack;
	initStack(&myStack);
	populateStack(&myStack);
	display(myStack);
	
	printf("test");
	
	return 0;
}