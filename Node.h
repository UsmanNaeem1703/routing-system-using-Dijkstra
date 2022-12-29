#pragma once
#include <iostream>
#include "Message.h"

using namespace std;

class Node {
public:
    Message msg;
    Node* next;
    Node(Message msg, Node* next = NULL) {
        this->msg = msg;
        this->next = next;
    }
};