#include<stdio.h>
#include<stdlib.h>
#define MATRIX_MAX 5
#define OPEN_MAX 5
#define INF __INT_MAX__

typedef int Matrix[MATRIX_MAX][MATRIX_MAX];

typedef struct node{
	int vertex;
	int cost;
	struct node* edge;	
}*Node;

typedef Node List[OPEN_MAX];

void populateMatrix(Matrix matrix)
{
	Matrix data = {
	{INF, 10, INF, 30, 100},
	{INF, INF, 50, INF, INF},
	{20, INF, INF, INF, 10},
	{INF, INF, 20, INF, 20},
	{INF, INF, INF, INF, INF}
	};
	
	int x, y;
	for(x=0; x<MATRIX_MAX; x++)
	{
		for(y=0; y<MATRIX_MAX; y++)
		{
			matrix[x][y] = data[x][y];
		}
	}
}

void initializeMatrix(Matrix m)
{
	int x, y;
	for(x=0; x<MATRIX_MAX; x++)
	{
		for(y=0; y<MATRIX_MAX; y++)
		{
			m[x][y] = -1;
		}
	}
}

void initializeList(List *L)
{
	int x;
	for(x=0; x<OPEN_MAX; x++)
	{
		(*L)[x] = NULL;
	}
}

void displayMatrix(Matrix m)
{
	int x, y;
	
	printf("%-7s", "Source");
	printf("%15s", "Cost");
	printf("\n%-7s%15s\n", "--------", "------------");
	
	for(x=0; x<MATRIX_MAX; x++)
	{
		printf("%-7d", x);
		for(y=0; y<MATRIX_MAX; y++)
		{
			printf("%-5d", m[x][y] == INF ? -1 : m[x][y]);
		}
		printf("\n");
	}
	printf("\n\n");
}

List* convertToList(Matrix m)
{	
	List *L = (List*)malloc(sizeof(List));
	if(*L!=NULL)
	{
		printf("\ntesting convertToList");
		initializeList(L);
		int x,y ;
		for(x=0; x<MATRIX_MAX; x++)
		{
			for(y=MATRIX_MAX-1; y>-1; y--)
			{
				if(m[x][y] != INF)
				{
					Node newNode = (Node)malloc(sizeof(struct node));
					if(newNode!=NULL)
					{
						newNode->vertex = y;
						newNode->cost = m[x][y];
						newNode->edge = (*L)[x];
						(*L)[x] = newNode;
					}
				}
			}
		}
	}
	printf("\ntesting convertToList");
	return L;
}



void displayList(List list)
{
    printf("\n\nDetails of the List :: ");
    printf("\n---------------------------");
    printf("\n\n%-7s", "Source");
    printf("%15s", "Connected Vertices (cost)");
    printf("\n%-7s%15s\n", "------", "--------------------");
    
    int x;
    
    for(x=0; x<OPEN_MAX; x++)
    {
    	printf("%-7d\n", x);
    	Node trav;
    	for(trav=list[x]; trav!=NULL; trav=trav->edge)
    	{
    		printf("%-2d (%-3d)", trav->vertex, trav->cost == INF ? -1 : trav->cost);
		}
		printf("\n");
	}
	printf("\n\n");
}

int main()
{
	Matrix testMatrix;
	initializeMatrix(testMatrix);
	displayMatrix(testMatrix);
	
	populateMatrix(testMatrix);
	displayMatrix(testMatrix);
	
	List *L = convertToList(testMatrix);
	displayList(*L);
	
	
	printf("\ntest");
	
	return 0;
}