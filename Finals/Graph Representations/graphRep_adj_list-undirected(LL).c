#include<stdio.h>
#include<stdlib.h>
#define MAX 6

typedef struct cell{
	int vertex;
	int weight;
	struct cell* link;
}node, *List;

typedef List adj_list[MAX];

void populate(adj_list List);
void display(adj_list List);

void populate(adj_list myList)
{
	int arr[][3] = {{0,2,2}, {2,0,2}, {0,1,4}, {1,0,4}, {4,1,3}, {1,4,3}, {2,3,2}, {3,2,2}, {3,4,3}, {4,3,3}, {2,5,4}, {5,2,4}, {3,5,1}, {5,3,1}, {5,4,1}, {4,5,1}};
	int numPaths = sizeof(arr)/sizeof(arr[0]);
	
	int x; 
	
	for(x=0; x<numPaths; x++)
	{
		List temp = (List)malloc(sizeof(node));
		if(temp!=NULL)
		{
			//performs insert at beginning
			temp->vertex = arr[x][1];
			temp->weight = arr[x][2];
			temp->link = myList[arr[x][0]];
			myList[arr[x][0]] = temp;
		}
	}
}

void display(adj_list dispList) 
{
	int x;
	List trav;
	printf("\n==============================\n");
	for(x=0; x<MAX; x++)
	{
		printf("Vertex [%d] ", x);
		
		for(trav=dispList[x]; trav!=NULL; trav=trav->link)
		{
			printf("--> %d  ", trav->vertex);
		}
		printf("\n");
	}
}

int main()
{
	adj_list listOne = {NULL, NULL, NULL, NULL, NULL, NULL};
	populate(listOne);
	display(listOne);
	return 0;
}
