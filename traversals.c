#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graphs.c"

void toLowerCase(string100 str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int isNodeVisited(string100 node, string100 visitedNodes[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp(node, visitedNodes[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int findVertex(string100 node, struct adjList graph[], int totalVertices) {
    for (int i = 0; i < totalVertices; i++) {
        if (strcasecmp(node, graph[i].vertex) == 0) {
            return i;
        }
    }
    return -1;
}

int breadthFirstSearch(struct adjList graph[], int totalVertices, string100 startNode, string100 BFS[MAX_VERT], int startDegree, int parent[], string100 originalNames[MAX_VERT]) {
    int visited[totalVertices];
    int adjIndices[graph[startDegree].degree], adjDegrees[graph[startDegree].degree];
    int nodeCount = 0;

    memset(visited, 0, sizeof(visited));

    toLowerCase(startNode);
    strcpy(BFS[0], startNode);
    strcpy(originalNames[0], graph[startDegree].vertex); // Store the original case
    parent[0] = -1; // Root node has no parent
    nodeCount++;
    visited[startDegree] = 1;

    for (int i = 0; i < graph[startDegree].degree; i++) {
        strcpy(BFS[nodeCount], graph[startDegree].adjacent[i]);
        adjIndices[i] = findVertex(graph[startDegree].adjacent[i], graph, totalVertices);
        adjDegrees[i] = graph[adjIndices[i]].degree;
        strcpy(originalNames[nodeCount], graph[startDegree].adjacent[i]); // Store the original case
        parent[nodeCount] = 0; // All adjacent nodes have the root as their parent
        nodeCount++;
    }

    for (int i = 0; i < graph[startDegree].degree; i++) {
        if (!visited[adjIndices[i]]) {
            for (int j = 0; j < adjDegrees[i]; j++) {
                if (!isNodeVisited(graph[adjIndices[i]].adjacent[j], BFS, nodeCount)) {
                    strcpy(BFS[nodeCount], graph[adjIndices[i]].adjacent[j]);
                    strcpy(originalNames[nodeCount], graph[adjIndices[i]].adjacent[j]); // Store the original case
                    parent[nodeCount] = adjIndices[i] + 1; // Store parent index
                    nodeCount++;
                }
            }
            visited[adjIndices[i]] = 1;
        }
    }

    return nodeCount;
}

void depthFirstSearchUtil(struct adjList graph[], int totalVertices, string100 currentNode, string100 DFS[], int *nodeCount, int visited[], string100 originalNames[MAX_VERT]) {
    int currentIndex = findVertex(currentNode, graph, totalVertices);

    strcpy(DFS[*nodeCount], currentNode);
    strcpy(originalNames[*nodeCount], graph[currentIndex].vertex); // Store the original case
    (*nodeCount)++;
    visited[currentIndex] = 1;

    for (int i = 0; i < graph[currentIndex].degree; i++) {
        int adjIndex = findVertex(graph[currentIndex].adjacent[i], graph, totalVertices);
        if (!visited[adjIndex]) {
            depthFirstSearchUtil(graph, totalVertices, graph[currentIndex].adjacent[i], DFS, nodeCount, visited, originalNames);
        }
    }
}

int depthFirstSearch(struct adjList graph[], int totalVertices, string100 startNode, string100 DFS[MAX_VERT], int startDegree, string100 originalNames[MAX_VERT]) {
    int visited[totalVertices];
    int nodeCount = 0;

    memset(visited, 0, sizeof(visited));
    toLowerCase(startNode);
    depthFirstSearchUtil(graph, totalVertices, startNode, DFS, &nodeCount, visited, originalNames);

    return nodeCount;
}

void drawGraph(FILE *output, struct adjList graph[], int totalVert) {
    fprintf(output, "Graph Adjacency List:\n");
    for (int i = 0; i < totalVert; i++) {
        fprintf(output, "%s: ", graph[i].vertex);
        for (int j = 0; j < graph[i].degree; j++) {
            fprintf(output, "%s", graph[i].adjacent[j]);
            if (j < graph[i].degree - 1) {
                fprintf(output, ", ");
            }
        }
        fprintf(output, "\n");
    }
}

void drawBFSTree(FILE *output, string100 BFS[MAX_VERT], int parent[], int totalBFS, string100 originalNames[MAX_VERT]) {
    fprintf(output, "\nBFS Tree:\n");
    for (int i = 0; i < totalBFS; i++) {
        if (parent[i] == -1) {
            fprintf(output, "%s (Root)\n", originalNames[i]);
        } else {
            fprintf(output, "%s -> %s\n", originalNames[parent[i]], originalNames[i]);
        }
    }
}
