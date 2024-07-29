#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100
#define MAX_VERT 100

typedef char string100[MAX_CHAR];

struct adjList {
    string100 vertex;
    string100 adjacent[MAX_VERT];
    int degree;
};

void resetGraph(struct adjList graph[]) {
    for (int i = 0; i < MAX_VERT; i++) {
        graph[i].vertex[0] = '\0';
        for (int j = 0; j < MAX_VERT; j++) {
            graph[i].adjacent[j][0] = '\0';
        }
        graph[i].degree = 0;
    }
}

int buildGraphFromFile(FILE *fp, struct adjList graph[]) {
    int totalVertices, vertexCount, terminate;
    string100 temp;
    
    fscanf(fp, "%d", &totalVertices);

    for (int i = 0; i < totalVertices; i++) {
        vertexCount = 0;
        fscanf(fp, "%s", temp);
        
        if (temp[strlen(temp) - 1] == ' ') {
            temp[strlen(temp) - 1] = '\0'; // Remove trailing space
        }
        
        strcpy(graph[i].vertex, temp);
        
        while (fscanf(fp, "%d", &terminate) != 1) {
            fscanf(fp, "%s", temp);
            if (temp[strlen(temp) - 1] == ' ') {
                temp[strlen(temp) - 1] = '\0'; // Remove trailing space or newline
            }
            strcpy(graph[i].adjacent[vertexCount], temp);
            vertexCount++;
            
            graph[i].degree++;
        }
    }
    
    return totalVertices;
}
