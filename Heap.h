#pragma once
#include "Message.h"
#include <iostream>

using namespace std;

class Heap {
public:
    Message* heap;
    int currSize;
    int totalSize;
    Heap(int size) {
        heap = new Message[size];
        currSize = 0;
        totalSize = size;
        for (int i = 0; i < totalSize; i++) {
            heap[i] = -1;
        }
    }
    void insert(Message message) {
        if (currSize < totalSize - 1) {
            heap[++currSize] = message;
            int curr = currSize;
            while (curr > 1) {
                if (heap[curr].priority < heap[curr / 2].priority) {
                    cout << "Swapping " << curr << " and " << curr / 2 << endl;
                    Message temp = heap[curr];
                    heap[curr] = heap[curr / 2];
                    heap[curr / 2] = temp;
                }
                curr /= 2;
            }
        }
    }

    Message remove() {
        Message temp = heap[1];
        heap[1] = heap[currSize--];
        int curr = 1;
        while (curr <= currSize) {
            if (heap[curr].priority > heap[2 * curr].priority && heap[2 * curr].priority != -1) {
                cout << "Swapping " << curr << " and " << curr / 2 << endl;
                Message temp = heap[2 * curr];
                heap[2 * curr] = heap[curr];
                heap[curr] = temp;
            }
            else if (heap[curr].priority > heap[2 * curr + 1].priority && heap[2 * curr + 1].priority != -1) {
                cout << "Swapping " << curr << " and " << curr / 2 << endl;
                Message temp = heap[2 * curr + 1];
                heap[2 * curr + 1] = heap[curr];
                heap[curr] = temp;
            }
            curr++;
        }
        return temp;
    }

    void clear() {
        Message m;
        for (int i = 0; i < totalSize; i++) {
            heap[i] = m;
        }
        currSize = 0;
    }

    bool isEmpty() {
        return currSize == 0;
    }
    ~Heap() {
        delete[] heap;
    }
};
