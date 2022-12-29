#pragma once
#include <iostream>

using namespace std;

class Message {
public:
    int msgId;
    int priority;
    int srcAddr;
    int destAddr;
    string payload;
    string trace;
    Message(int msgId = -1, int priority = -1, string srcAddr = "-", string destAddr = "-", string payload = "-", string trace = "") {
        this->msgId = msgId;
        this->priority = priority;
        this->srcAddr = atoi(srcAddr.c_str());
        this->destAddr = atoi(destAddr.c_str());
        this->payload = payload;
        this->trace = trace;
    }
};