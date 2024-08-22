D#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#define MATRIX_MAX 6
#define OPEN_MAX 6
#define VH_MAX 16
#define CL0SE_MAX 6
#define INFINITY 99999
#define INF __INT_MAX__

typedef int graphtype[MATRIX_MAX][MATRIX_MAX];
typedef int set[MATRIX_MAX];

typedef struct{
	int elem[MATRIX_MAX];
	int front;
	int rear;
}QUEUE;

typedef struct{
	int u, v;
	int weight;	
}edgetype;

typedef struct{
	edgetype edges[MATRIX_MAX];
	int minCost;
	int edgeCount;
}primMST, kruskalMST;

void initMatrix(graphtype graph);
int* bfs(graphtype graph, int src);
int* dfs(graphtype graph, int src);
void printArray(int arr[]);
void initQueue(QUEUE *queue);
void Enqueue(QUEUE *queue, int elem);
void Dequeue(QUEUE *queue);
int Front(QUEUE queue);

int* Dijkstra(graphtype graph, int src);
void Floyd(graphtype graph, graphtype cost);
void Warshall(graphtype graph, graphtype cost);

primMST primAlgo(graphtype graph, int startvertex);
kruskalMST kruskalAlgo(graphtype graph);
int findRep(int tracker[], int vertexNo);

void initQueue(QUEUE *queue)
{
	queue->front=-1;
	queue->rear=-1;
}

void Enqueue(QUEUE *queue, int elem)
{
	if((queue->rear+1)%MATRIX_MAX!=queue->front)
	{
		if(queue->front==-1)
		{
			queue->front++;
			queue->rear++;
		}
		else
		{
			queue->rear=(queue->rear+1)%MATRIX_MAX;
		}
		queue->elem[queue->rear] = elem;
	}
}

void Dequeue(QUEUE *queue)
{
	if(queue->front!=-1)
	{
		if(queue->front==queue->rear)
		{
			queue->front=-1;
			queue->rear=-1;
		}
		else
		{
			queue->front = (queue->front+1)%MATRIX_MAX;
		}
	}
}

int Front(QUEUE queue)
{
	return queue.elem[queue.front];
}

void initMatrix(graphtype graph)
{
	int x, y;
	for(x=0; x<MATRIX_MAX; x++)
	{
		for(y=0; y<MATRIX_MAX; y++)
		{
			graph[x][y] = -1;
		}
	}
}

int *bfs(graphtype graph, int src)
{
	int *bfstrav = (int*)malloc(sizeof(int) * MATRIX_MAX);
	set visited = {0};
	
	if(bfstrav!=NULL)
	{
		QUEUE queue;
	
		initQueue(&queue);
		int node, neighbor, ctr;
	
		for(node=src, ctr=0, Enqueue(&queue, src); queue.front!=-1; Dequeue(&queue), node=Front(queue))
		{
			bfstrav[ctr++]=node;
			visited[node] = 1;
			
			for(neighbor=0; neighbor<MATRIX_MAX; neighbor++)
			{
				if(graph[node][neighbor]==1 && visited[neighbor]==0)
				{
					Enqueue(&queue, neighbor);
				}
			}
		}
	}
	
	return bfstrav;
}

void printArray(int arr[])
{
	printf("\n--- Result ---\n");
	int x;
	for(x=0; x<MATRIX_MAX; x++)
	{
		printf("%d ", arr[x]);
	}
	
	printf("\n\n");
}

void populateMatrix(graphtype graph)
{
	graphtype given = {  INFINITY, 1, 5, 4, 6, 5, 1, INFINITY, 5, INFINITY, INFINITY, 6, 5, 5, INFINITY, 2, INFINITY, INFINITY, 4,
                             INFINITY, 2, INFINITY, 1, INFINITY, 6, INFINITY,INFINITY, 1, INFINITY, 3, 5, 6, INFINITY, INFINITY, 3, INFINITY} ;   //5

	memcpy(graph, given, sizeof(given));
}


void Floyd(graphtype graph, graphtype cost)
{
	int i, j, k;
	
	for(i=0; i<MATRIX_MAX; i++)
	{
		for(j=0; j<MATRIX_MAX; j++)
		{
			graph[i][j] = cost[i][j];
		}
	}
	
	for(i=0; i<MATRIX_MAX; i++)
	{
		graph[i][i] = 0;
	}
	
	for(k=0; k<MATRIX_MAX; k++)
	{
		for(i=0; i<MATRIX_MAX; i++)
		{
			for(j=0; j<MATRIX_MAX; j++)
			{
				if(graph[i][k] != INFINITY && graph[k][j] != INFINITY && graph[i][k] + graph[k][j] < graph[i][j])
				{
					graph[i][j] = graph[i][k] + graph[k][j];
				}
			}
		}
	}
}

void Warshall(graphtype graph, graphtype cost)
{
	int i, j, k;
	for(i=0; i<MATRIX_MAX; i++)
	{
		for(j=0; j<MATRIX_MAX; j++)
		{
			graph[i][j] = (cost[i][j]==INFINITY) ? 0 : 1;
		}
	}
	
	for(i=0; i<MATRIX_MAX; i++)
	{
		graph[i][i] = 1;
	}
	
	for(k=0; k<MATRIX_MAX; k++)
	{
		for(i=0; i<MATRIX_MAX; i++)
		{
			for(j=0; j<MATRIX_MAX; j++)
			{
				if(graph[i][j]==0)
				{
					graph[i][j] = graph[i][k] && graph[k][j];
				}
			}
		}
	}
}

primMST primAlgo(graphtype graph, int startvertex)
{
	set visited = {0};
	primMST prim;
	prim.edgeCount=0;
	prim.minCost=0;
	
	visited[startvertex]=1;
	
	while(prim.edgeCount<MATRIX_MAX-1)
	{
		int min = INFINITY;
		int u, v;
		edgetype minEdge;
		
		for(u=0; u<MATRIX_MAX; u++)
		{
			if(visited[u]==1)
			{
				for(v=0; v<MATRIX_MAX; v++)
				{
					if(visited[v]==0 && graph[u][v] < min)
					{
						min = graph[u][v];
						minEdge.u = u;
						minEdge.v = v;
						minEdge.weight = min;
					}
				}
			}
		}
		
		visited[minEdge.v] = 1;
		prim.edges[prim.edgeCount++] = minEdge;
		prim.minCost+=min;
	}
	
	return prim;
}

int findRep(int tracker[], int vertexno)
{
	if(tracker[vertexno]!=vertexno)
	{
		tracker[vertexno] = findRep(tracker, tracker[vertexno]);
	}
	
	return tracker[vertexno];
}

kruskalMST kruskalAlgo(graphtype graph)
{
	int i, j;
	kruskalMST edgeList;
	kruskalMST spanList;
	int tracker[MATRIX_MAX]; //keeping track of disjoint sets
	
	edgeList.edgeCount = 0;
	for(i=0; i<MATRIX_MAX; i++)
	{
		for(j=0; j<MATRIX_MAX; j++)
		{
			if(graph[i][j]!=INFINITY)
			{
				edgeList.edges[edgeList.edgeCount].u = i;
				edgeList.edges[edgeList.edgeCount].v = j;
				edgeList.edges[edgeList.edgeCount].weight = graph[i][j];
				edgeList.edgeCount++;
			}
		}
	}
	
	//sort
	edgetype temp;
	for(i=0; i<edgeList.edgeCount; i++)
	{
		for(j=0; j<edgeList.edgeCount-1; j++)
		{
			if(edgeList.edges[j].weight > edgeList.edges[j+1].weight)
			{
				temp = edgeList.edges[j];
				edgeList.edges[j] = edgeList.edges[j+1];
				edgeList.edges[j+1] = temp;
			}
		}
	}
	
	for(i=0; i<MATRIX_MAX; i++)
	{
		tracker[i] = i;
	}
	
	int u, v;
	spanList.edgeCount=0;
	spanList.minCost=0;
	
	for(i=0; i<edgeList.edgeCount; i++)
	{
		u = findRep(tracker, edgeList.edges[i].u);
		v = findRep(tracker, edgeList.edges[i].v);
		
		if(u!=v)
		{
			spanList.edges[spanList.edgeCount++] = edgeList.edges[i];
			spanList.minCost+= edgeList.edges[i].weight;
			
			int z;
			for(z=0; z<MATRIX_MAX; z++)
			{
				if(tracker[z]==v)
				{
					tracker[z]=u;
				}
			}
		}
	}
	
	return spanList;
}

void printKruskalMST(kruskalMST mst) {
    printf("\nEdges in Minimum Spanning Tree:\n");
    int i;
    for (i = 0; i < mst.edgeCount; i++) {
        printf("(%d, %d) - weight: %d\n", mst.edges[i].u, mst.edges[i].v, mst.edges[i].weight);
    }
    
    printf("\nMinimum cost: %d\n", mst.minCost);
}

int main()
{
//	graphtype mygraph;
//	initMatrix(mygraph);
//	
//	int* bfsOutput = bfs(mygraph, 8);
//	printArray(bfsOutput);
	
	graphtype m1 = {{INFINITY, 10, INFINITY, 30, 100}, {INFINITY, INFINITY, 50, INFINITY, INFINITY}, {20, INFINITY, INFINITY, INFINITY, 10}, {INFINITY, INFINITY, 20, INFINITY, 60}, {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY}};
	kruskalMST m1Kruskal = kruskalAlgo(m1);
	printKruskalMST(m1Kruskal);
	return 0;
}