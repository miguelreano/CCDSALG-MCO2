#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100
#define MAX_VERT 100

typedef char string100[MAX_CHAR];

struct adjList
{
	string100 vertex;
	string100 adjacent[MAX_VERT];
	int degree;
};

void
initializeGraph (struct adjList graph[])
{
	int i, j;
	
	for (i = 0; i < MAX_VERT; i++)
	{
		strcpy(graph[i].vertex, "");
		for (j = 0; j < MAX_VERT; j++)
			strcpy(graph[i].adjacent[j], "");
		graph[i].degree = 0;
	}
}

int
inputToGraph (FILE *fp, struct adjList graph[])
{
	int totalVert;
	int i, vert, terminate;
	string100 temp;
	
	fscanf(fp, "%d", &totalVert);
		
	while (!feof(fp))
	{
		for (i = 0; i < totalVert; i++)
		{
			vert = 0;
			fscanf(fp, "%s", temp);
			
			if (temp[strlen(temp) - 1] == ' ')
				temp[strlen(temp) - 1] = '\0'; //remove space from the text
				
			strcpy(graph[i].vertex, temp);
			
			while (!(fscanf(fp, "%d", &terminate) == 1)) //while end of vertex adjacency list is not terminated
			{
				fscanf(fp, "%s", temp);
				if (temp[strlen(temp) - 1] == ' ')
					temp[strlen(temp) - 1] = '\0'; //remove space or next line
				strcpy(graph[i].adjacent[vert], temp);
				vert++;
				
				graph[i].degree++;
			}
		}
	}
		
	return totalVert;
}
