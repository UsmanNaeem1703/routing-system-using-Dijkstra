#pragma once
#include <iostream>

using namespace std;

class distPath {
public:
    int dist;
    int path;
};

// A utility function used to print the solution
void printArr(distPath dist[], int n, int src)
{
    cout << "Vertex Distance from " << src + 1 << "\n";
    for (int i = 0; i < n; ++i)
        cout << i + 1 << " \t\t " << dist[i].dist << " \t\t " << dist[i].path << endl;
}