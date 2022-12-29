#pragma once
#include "Queue.h"

struct RoutTable {
    int dest;
    int parent;
    Queue outgoing;
};