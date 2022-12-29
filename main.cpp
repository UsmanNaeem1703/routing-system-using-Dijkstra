// C / C++ program for Dijkstra's
// shortest path algorithm for adjacency
// list representation of graph
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Graph.h"
#include "DistPath.h"
#include "MinHeap.h"
using namespace std;
// The main function that calculates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
distPath* dijkstra(struct Graph* graph, int src)
{
    // Get the number of vertices in graph
    int V = graph->V;

    // dist values used to pick
    // minimum weight edge in cut
    distPath* dist = new distPath[V];

    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v].dist = INT_MAX;
        dist[v].path = -1;
        minHeap->array[v] = newMinHeapNode(v, dist[v].dist);
        minHeap->pos[v] = v;
    }

    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src].dist);
    minHeap->pos[src] = src;
    dist[src].dist = 0;
    decreaseKey(minHeap, src, dist[src].dist);

    // Initially size of min heap is equal to V
    minHeap->size = V;
    int parent;
    // In the following loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);

        // Store the extracted vertex number
        int u = minHeapNode->v;
        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        //AdjListNode* parent = NULL;
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)//
        {
            int v = pCrawl->dest;
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            if (isInMinHeap(minHeap, v) &&
                dist[u].dist != INT_MAX &&//mahd check this function again
                pCrawl->weight + dist[u].dist < dist[v].dist)
            {
                dist[v].dist = dist[u].dist + pCrawl->weight;
                dist[v].path = u;

                // update distance
                // value in min heap also
                decreaseKey(minHeap, v, dist[v].dist);
            }

            pCrawl = pCrawl->next;
        }
        //if(u)
        parent = u + 1;
    }
    //printArr(dist, V, src);
    return dist;
    // print the calculated shortest distances
}

void sendMessage(Graph graph, Message msg) {
    /*
    1. send message m
    2. machine
    */
    graph.array[msg.srcAddr].outgoing->ENQUEUE(msg);
    cout << "Enqueueing message#" << msg.msgId << " in Outgoing Queue of " << msg.srcAddr << endl;
    Message m = graph.array[msg.srcAddr].outgoing->DEQUEUE();
    cout << "Dequeueing message#" << msg.msgId << " from Outgoing Queue of " << msg.srcAddr << endl;
    char buffer[10];
    m.trace += _itoa(msg.srcAddr, buffer, 10);
    m.trace += " => ";
    cout << "\nSending Message#" << msg.msgId << " to " << graph.array[msg.srcAddr].head->dest << endl;
    Sleep(1000);
    m.trace += _itoa(graph.array[msg.srcAddr].head->dest, buffer, 10);
    graph.array[graph.array[msg.srcAddr].head->dest].incoming->insert(m);
    cout << "Enqueueing Message#" << msg.msgId << " in incoming Priority Queue of " << graph.array[msg.srcAddr].head->dest << endl;
    int destination = msg.destAddr;
    int nextDest = msg.destAddr;
    int presentAddr = graph.array[msg.srcAddr].head->dest;
    while (presentAddr != destination) {
        while(nextDest != presentAddr){
            if (presentAddr == graph.array[presentAddr].getParent(nextDest)) {
                m = graph.array[presentAddr].incoming->remove();
                cout << "Dequeuing Message#" << msg.msgId << " from incoming Priority Queue of " << presentAddr << endl;
                graph.array[presentAddr].routTable[nextDest].outgoing.ENQUEUE(m);
                cout << "Enqueueing Message#" << msg.msgId << " into outgoing queue of rout table index " << nextDest << endl;
                m = graph.array[presentAddr].routTable[nextDest].outgoing.DEQUEUE();
                cout << "Dequeuing Message#" << msg.msgId << " from outgoing queue of rout table index " << nextDest << endl;
                cout << "\nSending Message#" << msg.msgId << " from " << presentAddr << " to " << nextDest << endl;
                Sleep(1000);
                m.trace += " => ";
                m.trace += _itoa(nextDest, buffer, 10);
                graph.array[nextDest].incoming->insert(m);
                cout << "Enqueueing Message#" << msg.msgId << " in incoming queuing of " << nextDest << endl;
                presentAddr = nextDest;
            }
            else {
                nextDest = graph.array[presentAddr].getParent(nextDest);
            }
        }
        nextDest = destination;
    }
    cout << "Trace = " << m.trace << "\nMessage Successfully sent from " << msg.srcAddr << " to " << msg.destAddr << " UwU\n";
}

void printPath(Graph graph, int V, int src, int dest) {
    if (dest == -1) {
        for (int i = 0; i < V; i++) {
            string path = "";
            char buffer[10];
            path += _itoa(src, buffer, 10);
            int destination = i;
            int nextDest = i;
            int presentAddr = graph.array[src].head->dest;
            path += " => ";
            path += _itoa(graph.array[src].head->dest, buffer, 10);
            while (presentAddr != destination) {
                while (nextDest != presentAddr) {
                    if (presentAddr == graph.array[presentAddr].getParent(nextDest)) {
                        path += " => ";
                        path += _itoa(nextDest, buffer, 10);
                        presentAddr = nextDest;
                    }
                    else {
                        nextDest = graph.array[presentAddr].getParent(nextDest);
                    }
                }
                nextDest = destination;
            }
            cout << "Path = " << path << endl;
        }
    }
    else if (src == -1) {
        for (int i = 0; i < V; i++) {
            string path = "";
            char buffer[10];
            path += _itoa(i, buffer, 10);
            int destination = dest;
            int nextDest = dest;
            int presentAddr = graph.array[i].head->dest;
            path += " => ";
            path += _itoa(graph.array[i].head->dest, buffer, 10);
            while (presentAddr != destination) {
                while (nextDest != presentAddr) {
                    if (presentAddr == graph.array[presentAddr].getParent(nextDest)) {
                        path += " => ";
                        path += _itoa(nextDest, buffer, 10);
                        presentAddr = nextDest;
                    }
                    else {
                        nextDest = graph.array[presentAddr].getParent(nextDest);
                    }
                }
                nextDest = destination;
            }
            cout << "Path = " << path << endl;
        }
    }
    else {
        string path = "";
        char buffer[10];
        path += _itoa(src, buffer, 10);
        int destination = dest;
        int nextDest = dest;
        int presentAddr = graph.array[src].head->dest;
        path += " => ";
        path += _itoa(graph.array[src].head->dest, buffer, 10);
        while (presentAddr != destination) {
            while (nextDest != presentAddr) {
                if (presentAddr == graph.array[presentAddr].getParent(nextDest)) {
                    path += " => ";
                    path += _itoa(nextDest, buffer, 10);
                    presentAddr = nextDest;
                }
                else {
                    nextDest = graph.array[presentAddr].getParent(nextDest);
                }
            }
            nextDest = destination;
        }
        cout << "Path = " << path << endl;
    }
}

// Driver program to test above functions
int main()
{
    // create the graph given in above figure
    fstream network("D:\\Project1\\Project1\\network.csv", ios::in);
    int sources = 0;
    char line[100];
    network.getline(line, 100);
    for (int i = 1; i < 100; i++) {
        if (line[i] == '\0')
            break;
        if (line[i] == ',') {
            sources++;
        }
    }
    string** devices = new string * [sources + 2];
    for (int i = 0; i < sources + 2; i++) {
        devices[i] = new string[sources + 2];
    }
    string machine = "";
    int j = 1;
    for (int i = 1; i < 100; i++) {
        if (line[i] == '\0')
            break;
        if (line[i] == ',')
        {
            devices[0][j] = machine;
            devices[j][0] = machine;
            machine = "";
            j++;
        }
        else
        {
            machine += line[i];
        }
    }
    devices[0][j] = machine;
    devices[j][0] = machine;
    machine = "";
    int row = 1, col = 1;
    while (!network.eof()) {
        int i = 0;
        network.getline(line, 100);
        while (line[i] != ',')
            i++;
        machine = "";
        for (int j = i + 1; j < 100; j++) {
            if (line[j] == '\0')
                break;
            if (line[j] == ',') {
                devices[row][col] = machine;
                machine = "";
                col++;
            }
            else
            {
                machine += line[j];
            }
        }
        devices[row][col] = machine;
        machine = "";
        row++;
        col = 1;
    }
    /*for (int i = 0; i <= sources + 1; i++) {
        for (int j = 0; j <= sources + 1; j++) {
            cout << devices[i][j] << '\t';
        }
        cout << endl;
    }*/
    //cout << "\n--------------------------------------------\n\n";


    int V = sources + 1;
    Graph* graph = createGraph(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (j >= i && devices[i + 1][j + 1] != "?") {
                //int d = atoi(devices[i+1][j+1].c_str());
                addEdge(graph, i, j, atoi(devices[i + 1][j + 1].c_str()));
            }
        }
    }
    for (int i = 0; i < V; i++) {
        graph->array[i].routTable = NULL;
        if (devices[0][i + 1][0] != 'M') {
            distPath* d = dijkstra(graph, i);
            graph->array[i].routTable = new RoutTable[V];
            for (int j = 0; j < V; j++) {
                graph->array[i].routTable[j].dest = d[j].dist;
                graph->array[i].routTable[j].parent = d[j].path;
            }
        }
    }
    /*for (int i = 0; i < V; i++) {
        if (graph->array[i].routTable) {
            graph->array[i].printRoutTable(V);
            cout << "\n--------------------------------------------\n\n";
        }
    }*/
    cout << "Welcome To Network Emulator\n\n\aCommands\tParameters\n\n--------------------------------------------------------------------------------\n\nsend_msg\t<Message ID>:<Priority>:<Source>:<Destination>:<Payload>\n\nsend_msgs\t<.txt file name>\n\nprint_path\t<Source> to <Destination>\n\nchange_edge\t<Source> <Destination> <Weight>\n\nchange_edges\t<.txt file name>\n\n";
        char command[100] = "";		// This is overall command
        char commandN[20] = "";		// This is form command name
        bool correct = false;
        do {
            // Emptying command and commandN
            for (int i = 0, j = 0; i < 100; i++, j++) {
                if (j < 20) {
                    command[i] = '\0';
                    commandN[j] = '\0';
                }
                else {
                    command[i] = '\0';
                }
            }
            // command getting from user
            cout << "Server/root>";
            cin.getline(command, 100);
            // Setting commandN
            for (int i = 0; i < 50; i++) {
                if (command[i] == ' ' || command[i] == '\0') {
                    break;
                }
                else {
                    commandN[i] = command[i];
                }
            }
            string commandName = commandN;
            string correctCommands = "send_msg";
            // Checking for correct command in commandName
            if (commandName == correctCommands) {
                correct = true;
                int count = 1;
                string msgid = "";
                string src = "";
                string dest = "";
                string priority = "";
                string payload = "";
                // Getting and setting values from user
                for (int i = 8; i < 100; i++) {
                    if (command[i] == ':') {
                        count++;
                    }
                    else if (command[i] == '\0') {
                        break;
                    }
                    else {
                        if (count == 1) {
                            msgid += command[i];
                        }
                        else if (count == 2) {
                            priority += command[i];
                        }
                        else if (count == 3) {
                            src += command[i];
                        }
                        else if (count == 4) {
                            dest += command[i];
                        }
                        else if (count == 5){
                            payload += command[i];
                        }
                        else {
                            break;
                        }
                    }
                }
                cout << msgid << '\t' << priority << '\t' << src << '\t' << dest << '\t' << payload << '\n';
                Message msg(atoi(msgid.c_str()), atoi(priority.c_str()), src, dest, payload);
                sendMessage(*graph, msg);
            }
            correctCommands = "send_msgs";//command
            // Checking for correct command in commandName
            if (commandName == correctCommands) {
                correct = true;
                int count = 1;
                string file = "";
                // Getting and setting values from user
                for (int i = 10; i < 100; i++) {
                    if (command[i] == '\0') {//s?
                        break;
                    }
                    else {
                        if (count == 1) {
                            file += command[i];
                        }
                        else {
                            break;
                        }
                    }
                }
                fstream insert(file, ios::in);
                cout << "\nReading file: " << file << "\n\n";
                while (!insert.eof()) {
                    char hello[100];
                    insert.getline(hello, 100);
                    int count = 1;
                    string msgid = "";
                    string src = "";
                    string dest = "";
                    string priority = "";
                    string payload = "";
                    // Getting and setting values from user
                    for (int i = 0; i < 100; i++) {
                        if (hello[i] == ':') {
                            count++;
                        }
                        else if (hello[i] == '\0') {
                            break;
                        }
                        else {
                            if (count == 1) {
                                msgid += hello[i];
                            }
                            else if (count == 2) {
                                priority += hello[i];
                            }
                            else if (count == 3) {
                                src += hello[i];
                            }
                            else if (count == 4) {
                                dest += hello[i];
                            }
                            else if (count == 5) {
                                payload += hello[i];
                            }
                            else {
                                break;
                            }
                        }
                    }
                    cout << msgid << '\t' << priority << '\t' << src << '\t' << dest << '\t' << payload << '\n';
                    Message msg(atoi(msgid.c_str()), atoi(priority.c_str()), src, dest, payload);
                    sendMessage(*graph, msg);
                    cout << "\n--------------------------------------------\n\n";
                }
            }
            correctCommands = "change_rt";
            // Checking for correct command in commandName
            if (commandName == correctCommands) {
                correct = true;
                int count = 1;
                string router = "";
                string src = "";
                string dest = "";
                string priority = "";
                string payload = "";
                // Getting and setting values from user
                for (int i = 10; i < 100; i++) {
                    if (command[i] == ':') {
                        count++;
                    }
                    else if (command[i] == '\0') {
                        break;
                    }
                    else {
                        if (count == 1) {
                            router += command[i];
                        }
                        else if (count == 2) {
                            priority += command[i];
                        }
                        else if (count == 3) {
                            src += command[i];
                        }
                        else if (count == 4) {
                            dest += command[i];
                        }
                        else if (count == 5) {
                            payload += command[i];
                        }
                        else {
                            break;
                        }
                    }
                }
                cout << router << '\t' << priority << '\t' << src << '\t' << dest << '\t' << payload << '\n';
                Message msg(atoi(router.c_str()), atoi(priority.c_str()), src, dest, payload);
                sendMessage(*graph, msg);
            }
            correctCommands = "print_path";
            // Checking for correct command in commandName
            if (commandName == correctCommands) {
                correct = true;
                int count = 1;
                string src = "";
                string to = "";
                string dest = "";
                // Getting and setting values from user
                for (int i = 11; i < 100; i++) {
                    if (command[i] == ' ') {
                        count++;
                    }
                    else if (command[i] == '\0') {
                        break;
                    }
                    else {
                        if (count == 1) {
                            src += command[i];
                        }
                        else if (count == 2) {
                            to += command[i];
                        }
                        else if (count == 3) {
                            dest += command[i];
                        }
                        else {
                            break;
                        }
                    }
                }
                cout << "Print path from " << src << " to " << dest << endl;
                if (dest == "*" && src != "*")
                    printPath(*graph, V, atoi(src.c_str()), -1);
                else if (src == "*" && dest != "*")
                    printPath(*graph, V, -1, atoi(dest.c_str()));
                else
                    printPath(*graph, V, atoi(src.c_str()), atoi(dest.c_str()));
            }
            correctCommands = "change_edge";
            // Checking for correct command in commandName
            if (commandName == correctCommands) {
                correct = true;
                int count = 1;
                string src = "";
                string dest = "";
                string weight = "";
                // Getting and setting values from user
                for (int i = 12; i < 100; i++) {
                    if (command[i] == ' ') {
                        count++;
                    }
                    else if (command[i] == '\0') {
                        break;
                    }
                    else {
                        if (count == 1) {
                            src += command[i];
                        }
                        else if (count == 2) {
                            dest += command[i];
                        }
                        else if (count == 3) {
                            weight += command[i];
                        }
                        else {
                            break;
                        }
                    }
                }
                cout << "Changing Edge of " << src << " to/from " << dest << endl;
                devices[atoi(src.c_str()) + 1][atoi(dest.c_str()) + 1] = weight;
                devices[atoi(dest.c_str()) + 1][atoi(src.c_str()) + 1] = weight;
                for (int i = 0; i <= sources + 1; i++) {
                    for (int j = 0; j <= sources + 1; j++) {
                        cout << devices[i][j] << '\t';
                    }
                    cout << endl;
                }
                cout << "\n--------------------------------------------\n\n";
                delete graph;
                graph = createGraph(V);
                for (int i = 0; i < V; i++) {
                    for (int j = 0; j < V; j++) {
                        if (j >= i && devices[i + 1][j + 1] != "?") {
                            //int d = atoi(devices[i+1][j+1].c_str());
                            addEdge(graph, i, j, atoi(devices[i + 1][j + 1].c_str()));
                        }
                    }
                }
                for (int i = 0; i < V; i++) {
                    graph->array[i].routTable = NULL;
                    if (devices[0][i + 1][0] != 'M') {
                        distPath* d = dijkstra(graph, i);
                        graph->array[i].routTable = new RoutTable[V];
                        for (int j = 0; j < V; j++) {
                            graph->array[i].routTable[j].dest = d[j].dist;
                            graph->array[i].routTable[j].parent = d[j].path;
                        }
                    }
                }
                for (int i = 0; i < V; i++) {
                    if (graph->array[i].routTable) {
                        graph->array[i].printRoutTable(V);
                        cout << "\n--------------------------------------------\n\n";
                    }
                }
            }
            correctCommands = "change_edges";
            // Checking for correct command in commandName
            if (commandName == correctCommands) {
                correct = true;
                int count = 1;
                string file = "";
                // Getting and setting values from user
                for (int i = 13; i < 100; i++) {
                    if (command[i] == ' ') {
                        count++;
                    }
                    else if (command[i] == '\0') {
                        break;
                    }
                    else {
                        if (count == 1) {
                            file += command[i];
                        }
                        else {
                            break;
                        }
                    }
                }
                cout << "Changing Edges according to " << file << endl;
                for (int i = 0; i < sources + 2; i++) {
                    delete[] devices[i];
                }
                delete[] devices;
                fstream network(file, ios::in);
                sources = 0;
                char line[100];
                network.getline(line, 100);
                for (int i = 1; i < 100; i++) {
                    if (line[i] == '\0')
                        break;
                    if (line[i] == ',') {
                        sources++;
                    }
                }
                
                devices = new string * [sources + 2];
                for (int i = 0; i < sources + 2; i++) {
                    devices[i] = new string[sources + 2];
                }
                string machine = "";
                int j = 1;
                for (int i = 1; i < 100; i++) {
                    if (line[i] == '\0')
                        break;
                    if (line[i] == ',')
                    {
                        devices[0][j] = machine;
                        devices[j][0] = machine;
                        machine = "";
                        j++;
                    }
                    else
                    {
                        machine += line[i];
                    }
                }
                devices[0][j] = machine;
                devices[j][0] = machine;
                machine = "";
                int row = 1, col = 1;
                while (!network.eof()) {
                    int i = 0;
                    network.getline(line, 100);
                    if (line[0] == '\0') {
                        break;
                    }
                    while (line[i] != ',')
                        i++;
                    machine = "";
                    for (int j = i + 1; j < 100; j++) {
                        if (line[j] == '\0')
                            break;
                        if (line[j] == ',') {
                            devices[row][col] = machine;
                            machine = "";
                            col++;
                        }
                        else
                        {
                            machine += line[j];
                        }
                    }
                    devices[row][col] = machine;
                    machine = "";
                    row++;
                    col = 1;
                }

                for (int i = 0; i <= sources + 1; i++) {
                    for (int j = 0; j <= sources + 1; j++) {
                        cout << devices[i][j] << '\t';
                    }
                    cout << endl;
                }
                cout << "\n--------------------------------------------\n\n";
                int V = sources + 1;
                delete graph;
                graph = createGraph(V);
                for (int i = 0; i < V; i++) {
                    for (int j = 0; j < V; j++) {
                        if (j >= i && devices[i + 1][j + 1] != "?") {
                            //int d = atoi(devices[i+1][j+1].c_str());
                            addEdge(graph, i, j, atoi(devices[i + 1][j + 1].c_str()));
                        }
                    }
                }
                for (int i = 0; i < V; i++) {
                    graph->array[i].routTable = NULL;
                    if (devices[0][i + 1][0] != 'M') {
                        distPath* d = dijkstra(graph, i);
                        graph->array[i].routTable = new RoutTable[V];
                        for (int j = 0; j < V; j++) {
                            graph->array[i].routTable[j].dest = d[j].dist;
                            graph->array[i].routTable[j].parent = d[j].path;
                        }
                    }
                }
                /*for (int i = 0; i < V; i++) {
                    if (graph->array[i].routTable) {
                        graph->array[i].printRoutTable(V);
                        cout << "\n--------------------------------------------\n\n";
                    }
                }*/
            }
            if (!correct) {
                cout << "Command Not found\n\n\aCommands\t\tParameters\n\n--------------------------------------------------------------------------------\n\nsend_msg\t<Message ID>:<Priority>:<Source>:<Destination>:<Payload>\n\nsend_msgs\t<.txt file name>\n\nprint_path\t<Source> to <Destination>\n\nchange_edge\t<Source> <Destination> <Weight>\n\nchange_edges\t <.txt file name>\n\n";
            }
            correct = false;
        } while ((command[0] != 'e' || command[1] != 'x' || command[2] != 'i' || command[3] != 't'));
        
    return 0;
}