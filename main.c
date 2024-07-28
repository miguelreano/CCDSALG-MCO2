#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traversals.c" // source file for BFS and DFS implementations

#define MAX_FILENAME 100
#define MAX_VERTICES 100

typedef char Filename[MAX_FILENAME];
typedef char VertexList[MAX_VERTICES][MAX_FILENAME];

void handleFileError(const Filename filename) {
    printf("\nError: File %s not found.\n", filename);
}

void processGraph(FILE *file, struct adjList graph[], int *totalVertices) {
    *totalVertices = inputToGraph(file, graph);
}

int findVertexIndex(struct adjList graph[], int totalVertices, const char *targetVertex) {
    for (int i = 0; i < totalVertices; i++) {
        if (strcmp(targetVertex, graph[i].vertex) == 0) {
            return i;
        }
    }
    return -1;
}

void printGraph(FILE *output, struct adjList graph[], int totalVertices) {
    for (int i = 0; i < totalVertices; i++) {
        fprintf(output, "%s\t%d\n", graph[i].vertex, graph[i].degree);
    }
}

void printTraversalResults(FILE *output, const char BFS[], const char DFS[], int totalBFS, int totalDFS) {
    fprintf(output, "\nBFS Traversal:\n");
    for (int i = 0; i < totalBFS; i++) {
        fprintf(output, "%s ", BFS[i]);
    }
    fprintf(output, "\n\nDFS Traversal:\n");
    for (int i = 0; i < totalDFS; i++) {
        fprintf(output, "%s ", DFS[i]);
    }
}

int main() {
    Filename filename;
    FILE *inputFile;
    FILE *outputFile;
    struct adjList graph[MAX_VERTICES];
    VertexList BFS, DFS;
    int totalVertices, totalBFS, totalDFS;
    char startVertex[MAX_FILENAME];
    
    printf("Enter the filename: ");
    scanf("%s", filename);
    
    inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        handleFileError(filename);
        return 1;
    }

    processGraph(inputFile, graph, &totalVertices);
    
    printf("Enter start vertex for traversal: ");
    scanf("%s", startVertex);
    
    int startVertexIndex = findVertexIndex(graph, totalVertices, startVertex);
    if (startVertexIndex != -1) {
        totalBFS = doBFS(graph, totalVertices, startVertex, BFS, startVertexIndex);
        totalDFS = doDFS(graph, totalVertices, startVertex, DFS, startVertexIndex);

        outputFile = fopen("TRAVERSALS.txt", "w");
        if (outputFile != NULL) {
            printGraph(outputFile, graph, totalVertices);
            printTraversalResults(outputFile, BFS, DFS, totalBFS, totalDFS);
            fclose(outputFile);
        } else {
            printf("Error: Could not open output file for writing.\n");
        }
    } else {
        printf("Error: Vertex %s not found.\n", startVertex);
    }

    fclose(inputFile);
    return 0;
}
