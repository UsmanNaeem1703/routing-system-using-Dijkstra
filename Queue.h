#pragma once
#include <iostream>
#include "Message.h"
#include "Node.h"


class Queue {
public:
    Node* front;
    Node* rear;
public:
    Queue() {
        front = NULL;
        rear = NULL;
    }
    void ENQUEUE(Message msg) {
        if (front == NULL) {
            front = new Node(msg);
            rear = front;
        }
        else {
            rear->next = new Node(msg);
            rear = rear->next;
        }
    }
    Message DEQUEUE() {
        Message temp = front->msg;
        Node* temp2 = front;
        this->front = NULL;
        this->rear = NULL;
        
        delete temp2;
        return temp;
    }
    void clear() {
        Message m;
        if (front) {
            Node* current = front;
            while (current != NULL) {
                current->msg = NULL;
                current = current->next;
            }
        }
    }
    bool isEmpty() {
        return front == NULL;
    }
    Message FRONT() {
        return front->msg;
    }
    Message REAR() {
        return rear->msg;
    }
    /*~Queue() {
        Node* current = front;
        while (current != NULL) {
            Node* temp = current->next;
            delete current;
            current = temp;
        }
        front = NULL;
        rear = NULL;
    }*/
};