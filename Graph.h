#pragma once
#include "AdjList.h"
#include "AdjListNode.h"
// A structure to represent a graph.s
// A graph is an array of adjacency lists.
// Size of array will be V (number of
// vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

// A utility function that creates
// a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*)
        malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.
    // Size of array will be V
    graph->array = (struct AdjList*)
        malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list
    // as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src,
    int dest, int weight)
{
    // Add an edge from src to dest.
    // A new node is added to the adjacency
    // list of src. The node is
    // added at the beginning
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    graph->array[src].incoming = new Heap(50);
    graph->array[src].outgoing = new Queue;
    // Since graph is undirected,
    // add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
    graph->array[dest].incoming = new Heap(50);
    graph->array[dest].outgoing = new Queue;
}