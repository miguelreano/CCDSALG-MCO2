#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traversals.c" // source code for BFS and DFS traversals

int main() {
    string100 filename;
    FILE *fp;
    FILE *output;
    
    struct adjList graph[MAX_VERT];
    string100 BFS[MAX_VERT], DFS[MAX_VERT];
    string100 originalBFS[MAX_VERT], originalDFS[MAX_VERT];
    int totalBFS, totalDFS;
    string100 vertex;
    int totalVert, found = 0, i = 0;
    int parent[MAX_VERT];
    
    resetGraph(graph);
    
    output = fopen("TRAVERSALS.txt", "w");

    printf("Input filename: ");
    scanf("%[^\n]", filename);
    toLowerCase(filename);
    
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("\n%s not found.", filename);
    } else {
        fp = fopen(filename, "r"); // reads the input filename
        
        totalVert = buildGraphFromFile(fp, graph);
        
        printf("\nInput start vertex for the traversal: ");
        scanf("%s", vertex);
        getchar();
        
        while (i < totalVert && !found) {
            if (strcasecmp(vertex, graph[i].vertex) == 0)
                found = 1;
            i++;
        }
            
        if (found) {
            totalBFS = breadthFirstSearch(graph, totalVert, vertex, BFS, i - 1, parent, originalBFS);
            totalDFS = depthFirstSearch(graph, totalVert, vertex, DFS, i - 1, originalDFS);
            
            // Drawing the graph
            drawGraph(output, graph, totalVert);
            fprintf(output, "\n");
            
            for (i = 0; i < totalVert; i++)
                fprintf(output, "%s  \t%d\n", graph[i].vertex, graph[i].degree);
            
            fprintf(output, "\n");
            
            for (i = 0; i < totalBFS; i++)
                fprintf(output, "%s ", originalBFS[i]);
            
            fprintf(output, "\n\n");
            
            for (i = 0; i < totalDFS; i++)
                fprintf(output, "%s ", originalDFS[i]);

            drawBFSTree(output, BFS, parent, totalBFS, originalBFS);
        } else {
            printf("Vertex %s not found.", vertex);
        }
        fclose(fp);
    }
    
    fclose(output);
    return 0;
}
