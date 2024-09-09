// // graph.c

// #include <stdio.h>
// #include <stdlib.h>
// #include "graph.h"

// /**
//  * Creates a new node in the adjacency list.
//  *
//  * @param vertex The vertex to be stored in the node.
//  * @return Pointer to the newly created node.
//  */
// Node* createNode(int vertex) {
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     if (newNode == NULL) {
//         fprintf(stderr, "Error: Memory allocation failed for new node.\n");
//         exit(EXIT_FAILURE);
//     }
//     newNode->vertex = vertex;
//     newNode->next = NULL;
//     return newNode;
// }

// /**
//  * Creates a graph with a specified number of vertices.
//  *
//  * @param numVertices The number of vertices in the graph.
//  * @return Pointer to the newly created graph.
//  */
// Graph* createGraph(int numVertices) {
//     Graph* graph = (Graph*)malloc(sizeof(Graph));
//     if (graph == NULL) {
//         fprintf(stderr, "Error: Memory allocation failed for graph.\n");
//         exit(EXIT_FAILURE);
//     }
//     graph->numVertices = numVertices;
//     graph->degrees = (int*)calloc(numVertices, sizeof(int));
//     if (graph->degrees == NULL) {
//         fprintf(stderr, "Error: Memory allocation failed for degrees array.\n");
//         exit(EXIT_FAILURE);
//     }
//     graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));
//     if (graph->array == NULL) {
//         fprintf(stderr, "Error: Memory allocation failed for adjacency list array.\n");
//         exit(EXIT_FAILURE);
//     }

//     for (int i = 0; i < numVertices; i++) {
//         graph->array[i].head = NULL;
//     }

//     return graph;
// }

// /**
//  * Adds an edge to the graph between two vertices.
//  * This is for an undirected graph, so it adds edges in both directions.
//  *
//  * @param graph The graph to which the edge will be added.
//  * @param src The source vertex of the edge.
//  * @param dest The destination vertex of the edge.
//  */
// void addEdge(Graph* graph, int src, int dest) {
//     // Add edge from src to dest
//     Node* newNode = createNode(dest);
//     newNode->next = graph->array[src].head;
//     graph->array[src].head = newNode;

//     // Add edge from dest to src (since the graph is undirected)
//     newNode = createNode(src);
//     newNode->next = graph->array[dest].head;
//     graph->array[dest].head = newNode;

//     // Update the degrees of both vertices
//     graph->degrees[src]++;
//     graph->degrees[dest]++;
// }



// /**
//  * Prints the adjacency list representation of the graph.
//  *
//  * @param graph The graph to be printed.
//  */
// void printGraph(Graph* graph) {
//     for (int v = 0; v < graph->numVertices; v++) {
//         Node* temp = graph->array[v].head;
//         printf("\n Adjacency list of vertex %d\n head ", v);
//         while (temp) {
//             printf("-> %d", temp->vertex);
//             temp = temp->next;
//         }
//         printf("\n");
//     }
// }
// /**
//  * Checks if an edge between two vertices exists in the graph.
//  *
//  * @param graph The graph in which to check for the edge.
//  * @param src The source vertex.
//  * @param dest The destination vertex.
//  * @return true if the edge exists, false otherwise.
//  */
// bool edgeExists(Graph* graph, int src, int dest) {
//     Node* temp = graph->array[src].head;
//     while (temp != NULL) {
//         if (temp->vertex == dest) {
//             return true; // Edge exists
//         }
//         temp = temp->next;
//     }
//     return false; // Edge does not exist
// }

// /**
//  * Removes an edge between two vertices.
//  *
//  * @param graph The graph where the edge will be removed.
//  * @param src The source vertex.
//  * @param dest The destination vertex.
//  */
// void removeEdge(Graph* graph, int src, int dest) {
//     // Remove edge from src to dest
//     Node* prev = NULL;
//     Node* temp = graph->array[src].head;
//     while (temp != NULL) {
//         if (temp->vertex == dest) {
//             if (prev != NULL) {
//                 prev->next = temp->next;
//             } else {
//                 graph->array[src].head = temp->next;
//             }
//             free(temp);
//             break;
//         }
//         prev = temp;
//         temp = temp->next;
//     }

//     // Remove edge from dest to src (since graph is undirected)
//     prev = NULL;
//     temp = graph->array[dest].head;
//     while (temp != NULL) {
//         if (temp->vertex == src) {
//             if (prev != NULL) {
//                 prev->next = temp->next;
//             } else {
//                 graph->array[dest].head = temp->next;
//             }
//             free(temp);
//             break;
//         }
//         prev = temp;
//         temp = temp->next;
//     }

//     // Update the degrees of both vertices
//     graph->degrees[src]--;
//     graph->degrees[dest]--;
// }

// /**
//  * Helper function to count reachable vertices from a given vertex using DFS.
//  *
//  * @param graph The graph being traversed.
//  * @param v The starting vertex.
//  * @param visited Array of boolean flags indicating if a vertex has been visited.
//  * @return The number of reachable vertices.
//  */
// int countReachableVertices(Graph* graph, int v, bool visited[]) {
//     visited[v] = true;
//     int count = 1; // Count the current vertex

//     Node* adjList = graph->array[v].head;
//     while (adjList != NULL) {
//         int connectedVertex = adjList->vertex;
//         if (!visited[connectedVertex]) {
//             count += countReachableVertices(graph, connectedVertex, visited);
//         }
//         adjList = adjList->next;
//     }
//     return count;
// }

// /**
//  * Checks if removing an edge will disconnect the graph.
//  * If it does, that edge is a bridge.
//  *
//  * @param graph The graph being checked.
//  * @param src The source vertex of the edge.
//  * @param dest The destination vertex of the edge.
//  * @return true if removing the edge does not disconnect the graph, false otherwise.
//  */
// bool isValidNextEdge(Graph* graph, int src, int dest) {
//     // Check if it's the only edge left from src
//     if (graph->array[src].head->next == NULL) {
//         return true;
//     }

//     // Count vertices reachable from src before removing the edge
//     bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
//     int beforeRemovalCount = countReachableVertices(graph, src, visited);
//     free(visited);

//     // Temporarily remove the edge
//     removeEdge(graph, src, dest);

//     // Count vertices reachable from src after removing the edge
//     visited = (bool*)calloc(graph->numVertices, sizeof(bool));
//     int afterRemovalCount = countReachableVertices(graph, src, visited);
//     free(visited);

//     // Re-add the edge to restore the original graph
//     addEdge(graph, src, dest);

//     // If the number of reachable vertices is the same before and after removal,
//     // then removing this edge does not disconnect the graph
//     return beforeRemovalCount == afterRemovalCount;
// }
// graph.c

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/**
 * Creates a new node in the adjacency list.
 *
 * @param vertex The vertex to be stored in the node.
 * @return Pointer to the newly created node.
 */
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

/**
 * Creates a graph with a specified number of vertices.
 *
 * @param numVertices The number of vertices in the graph.
 * @return Pointer to the newly created graph.
 */
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for graph.\n");
        exit(EXIT_FAILURE);
    }
    graph->numVertices = numVertices;
    graph->degrees = (int*)calloc(numVertices, sizeof(int));
    if (graph->degrees == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for degrees array.\n");
        exit(EXIT_FAILURE);
    }
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));
    if (graph->array == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for adjacency list array.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

/**
 * Checks if an edge between two vertices exists in the graph.
 *
 * @param graph The graph in which to check for the edge.
 * @param src The source vertex.
 * @param dest The destination vertex.
 * @return true if the edge exists, false otherwise.
 */
bool edgeExists(Graph* graph, int src, int dest) {
    Node* temp = graph->array[src].head;
    while (temp != NULL) {
        if (temp->vertex == dest) {
            return true; // Edge exists
        }
        temp = temp->next;
    }
    return false; // Edge does not exist
}

/**
 * Adds an edge to the graph between two vertices.
 * This is for an undirected graph, so it adds edges in both directions.
 *
 * @param graph The graph to which the edge will be added.
 * @param src The source vertex of the edge.
 * @param dest The destination vertex of the edge.
 */
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    if (!edgeExists(graph, src, dest)) {
        Node* newNode = createNode(dest);
        newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;

        // Add edge from dest to src (since the graph is undirected)
        newNode = createNode(src);
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;

        // Update the degrees of both vertices
        graph->degrees[src]++;
        graph->degrees[dest]++;
    }
}

/**
 * Prints the adjacency list representation of the graph.
 *
 * @param graph The graph to be printed.
 */
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (temp) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

/**
 * Removes an edge between two vertices.
 *
 * @param graph The graph where the edge will be removed.
 * @param src The source vertex.
 * @param dest The destination vertex.
 */
void removeEdge(Graph* graph, int src, int dest) {
    // Remove edge from src to dest
    Node* prev = NULL;
    Node* temp = graph->array[src].head;
    while (temp != NULL) {
        if (temp->vertex == dest) {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                graph->array[src].head = temp->next;
            }
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    // Remove edge from dest to src (since graph is undirected)
    prev = NULL;
    temp = graph->array[dest].head;
    while (temp != NULL) {
        if (temp->vertex == src) {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                graph->array[dest].head = temp->next;
            }
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    // Update the degrees of both vertices
    graph->degrees[src]--;
    graph->degrees[dest]--;
}
void createManualGraph(Graph* graph) {
    int numEdges;
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);

        // Ensure the vertices are within bounds
        if (src >= graph->numVertices || dest >= graph->numVertices || src < 0 || dest < 0) {
            printf("Invalid edge! Vertices must be between 0 and %d.\n", graph->numVertices - 1);
            i--; // Retry this edge
        } else {
            addEdge(graph, src, dest);
        }
    }

    printf("Graph creation complete.\n");
}
void freeGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    // Free the adjacency list nodes
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->array[i].head;
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    // Free the array and degrees array
    free(graph->array);
    free(graph->degrees);

    // Free the graph structure
    free(graph);
}
