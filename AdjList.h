#pragma once
#include "Queue.h"
#include "RoutTable.h"
#include "Heap.h"
#include "AdjListNode.h"
// A structure to represent
// an adjacency list
struct AdjList
{
    RoutTable* routTable;
    Heap* incoming;
    Queue* outgoing;
    // Pointer to head node of list
    struct AdjListNode* head;
    AdjList() {
        incoming = new Heap(50);
        outgoing = new Queue;
        routTable = NULL;
        head = NULL;
    }
    void printRoutTable(int V) {
        for (int i = 0; i < V; i++) {
            cout << routTable[i].dest << " \t\t " << routTable[i].parent << endl;
        }
    }
    int getParent(int child) {
        int i = 0;
        while (i != child) {
            i++;
        }
        return routTable[i].parent;
    }
};