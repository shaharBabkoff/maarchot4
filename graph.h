// graph.h

#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct AdjList {
    Node* head;
} AdjList;

typedef struct Graph {
    int numVertices;
    int* degrees; // Array to store degrees of each vertex
    AdjList* array;
} Graph;

Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
bool edgeExists(Graph* graph, int src, int dest);
void removeEdge(Graph* graph, int src, int dest);
void createManualGraph(Graph* graph) ;
void freeGraph(Graph* graph);

#endif
