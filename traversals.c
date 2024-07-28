#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphs.c"

int
checkVisited (string100 vertex, string100 searchTree[], int totalNodes)
{
	int i = 0, visited = 0;
	
	while (i < totalNodes && !visited)
	{
		if (strcmp(vertex, searchTree[i]) == 0)
			visited = 1;
		i++;
	}
	
	return visited;
}

int
getMatchIndex(string100 vertex, struct adjList graph[], int totalVert)
{
	int i = 0, matchIndex = 0;

	while (i < totalVert && !matchIndex)
	{
		if (strcmp(vertex, graph[i].vertex) == 0)
			matchIndex = i;
		i++;
	}

	return matchIndex;
}

int
doBFS (struct adjList graph[], int totalVert, string100 vertex, 
     string100 BFS[MAX_VERT], int vertDeg)
{
	int visited[totalVert];
	int adjIndex[graph[vertDeg].degree], vertAdj[graph[vertDeg].degree];
	int i, j, k, totalNodes = 0;
	
	for (i = 0; i < totalVert; i++)
	{
		visited[i] = 0;
	}
	
	strcpy(BFS[0], vertex); //first entry in the BFS is the search vertex given
	
	totalNodes++;
	visited[vertDeg] = 1;
	
	for (i = 0; i < graph[vertDeg].degree; i++)
	{ //adjacent vertices of search vertex
		strcpy(BFS[totalNodes], graph[vertDeg].adjacent[i]);
		
		//get the index of each adjacent vertex on the graph
		adjIndex[i] = getMatchIndex(graph[vertDeg].adjacent[i], graph, totalVert);
		
		//get the degree of the adjacent vertices
		vertAdj[i] = graph[adjIndex[i]].degree;
		
		totalNodes++;
	}
	
	for (i = 0; i < graph[vertDeg].degree; i++)
	{
		if (!visited[adjIndex[i]])
		{
			for (j = 0; j < vertAdj[i]; j++)
			{ //adjacent vertices of adjacent vertex
				if (!checkVisited(graph[adjIndex[i]].adjacent[j], BFS, totalNodes))
				{
					strcpy(BFS[totalNodes], graph[adjIndex[i]].adjacent[j]);
					totalNodes++;
				}
			}
			visited[adjIndex[i]] = 1;
		}
	}
	
	return totalNodes;
}

void doDFSUtil(struct adjList graph[], int totalVert, string100 vertex, string100 DFS[], int *totalNodes, int visited[])
{
    int i, vertexIndex = getMatchIndex(vertex, graph, totalVert);
    
    strcpy(DFS[*totalNodes], vertex);
    (*totalNodes)++;
    visited[vertexIndex] = 1;
    
    for (i = 0; i < graph[vertexIndex].degree; i++)
    {
        int adjIndex = getMatchIndex(graph[vertexIndex].adjacent[i], graph, totalVert);
        if (!visited[adjIndex])
        {
            doDFSUtil(graph, totalVert, graph[vertexIndex].adjacent[i], DFS, totalNodes, visited);
        }
    }
}

int doDFS(struct adjList graph[], int totalVert, string100 vertex, string100 DFS[MAX_VERT], int vertDeg)
{
    int visited[totalVert];
    int totalNodes = 0;
    
    for (int i = 0; i < totalVert; i++)
    {
        visited[i] = 0;
    }
    
    doDFSUtil(graph, totalVert, vertex, DFS, &totalNodes, visited);
    
    return totalNodes;
}
