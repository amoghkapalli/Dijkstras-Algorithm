
#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <vector>
//---------------------------------------------------------------------------
// Graph ADT
//   -- Implements Dijkstra's shortest path algorithm
//   -- The graph is built from the data given through a text file
//   -- Edges are inserted or removed between two nodes
//   -- The displayAll displays the whole set of shortest paths for each node
//   -- The display method displays the shortest path from one node to another
//
// Implementation and assumptions:
//   -- Implemented using a Table structure which contains the nodes visited
//   -- shortest distance, and the previous node in the shortest path
//   -- Helper methods for finding the Data and the path
//   -- Testing for this was done using the driver which read inputs
//---------------------------------------------------------------------------
const int MAXNODES = 101;
class GraphM {                             
    public: 
        // No-arg constructor which sets all the terms in the cost array 
        // and in the Table to the INT_MAX which is used as a flag for
        // the values at that index not being filled
        GraphM();
        ~GraphM();
        // buildGraph takes in a file and fills the node info and edges
        void buildGraph(ifstream &fileVals);
        // Insert edge adds a edge between two nodes
        bool insertEdge(int start, int dest, int distance);
        // Removes edge adds a edge between two nodes
        bool removeEdge(int start, int dest);
        // Finds the Dijkstra info for each node
        void findShortestPath();
        // Displays all the paths for each node and the cost
        void displayAll();
        // Displays the single cost info and path from one node to another
        void display(int fromNode, int toNode);
    private: 
        struct TableType { 
            bool visited;  // whether node has been visited 
            int dist;  // currently known shortest distance from source  
            int path;  // previous node in path of min dist  
        }; 
        void findData(int start, int dest);
        void findPath(int start, int dest);
        
        NodeData data[MAXNODES]; // data for graph nodes information 
        int C[MAXNODES][MAXNODES];// Cost array, the adjacency matrix 
        int size=0;// number of nodes in the graph 
        TableType T[MAXNODES][MAXNODES];// stores Dijkstra information 
};
#endif
