
#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <list>
//---------------------------------------------------------------------------
// Graph ADT
//   -- Implements Depth first search
//   -- The graph is built from the data given through a text file
//   -- The displayAll displays the whole set of shortest paths for each node
//   -- The display method displays the shortest path from one node to another
//
// Implementation and assumptions:
//   -- Implemented using a Graph node containing the edges which 
//   -- shortest distance, and the previous node in the shortest path
//   -- Helper methods for finding the Data and the path
//   -- Testing for this was done using the driver which read inputs
//---------------------------------------------------------------------------
const int MAXNODES_L = 101;
class GraphL {                             
    public: 
        // no arg constructor
        GraphL();
        // destructor
        ~GraphL();
        //deletes the edge list
        void makeEmpty();
        // buildGraph takes in a file and fills the node info and edges
        void buildGraph(istream &fileVals);
        //executes a depth first search
        void depthFirstSearch();
        // displays all of the parths for each node and the final 
        // depth first order
        void displayGraph();
    private: 
        int size;																															
        struct GraphNode {																	
            list <int> edges;							
            NodeData data;								
            bool visited;		
        };																					
	    GraphNode nodeArray[MAXNODES_L];																
																						
        void dfsHelper(int); 
};
#endif
