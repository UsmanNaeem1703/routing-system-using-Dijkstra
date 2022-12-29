#pragma once
#include <iostream>

using namespace std;

// A structure to represent a
// node in adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};

// A utility function to create
// a new adjacency list node
struct AdjListNode* newAdjListNode(
    int dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}