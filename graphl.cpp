#include "graphl.h"
//----------------------------------------------------------------------------
// GraphL No-arg Constructor 
GraphL::GraphL() {
}
//----------------------------------------------------------------------------
// GraphL Destructor making the nodeArray empty
GraphL::~GraphL() {
    makeEmpty();
}
//----------------------------------------------------------------------------
// GraphL makeEmpty helper
// Cleares the edges and resets the nodes visited to false
void GraphL::makeEmpty(){
   for (int i = 0; i <= size; i++) {
      nodeArray[i].edges.clear();
		nodeArray[i].visited = false;
   }

}

//----------------------------------------------------------------------------
// GraphL buildGraph
// Goes through the file and gets the information starting with the size 
// and the locations. Then, the double touples on each line are added 
// to the nodeArray edge list
void GraphL::buildGraph(istream& infile) {
   int fromNode, toNode;

   makeEmpty();           

   infile >> size;          
   if (infile.eof()) return; 
   string s;                  
   getline(infile, s);


   for (int i=1; i <= size; i++) {
      nodeArray[i].data.setData(infile);
      nodeArray[i].visited = false;
   }


   for (;;) {
      infile >> fromNode >> toNode;
      if (fromNode == 0 && toNode == 0) return;

      if ((fromNode <= size && toNode <= size) &&(
         fromNode > 0 && toNode > 0)) {
         if ((fromNode > 0 && toNode > 0) && 
            (fromNode <= size && toNode <= size)) {
            nodeArray[fromNode].edges.push_back(toNode);
         }
      }
   }
}

//----------------------------------------------------------------------------
// GraphL depthFirstSearch
// Executes depth first search with helper
void GraphL::depthFirstSearch(){
   cout << "Depth first ordering:";
    for (int i = 1; i <= size; i++) {
        if (nodeArray[i].visited==false) {
            dfsHelper(i);
        }
    }
    cout << endl;
    cout << endl;
}
//----------------------------------------------------------------------------
// GraphL dfsHelper
// The helper prints the nodes in the order of depth first and recursively
// if node is not visited, it is called again.
void GraphL::dfsHelper(int n) {
    nodeArray[n].visited = true;
    cout << " " << n;
    list<int>::iterator curr = nodeArray[n].edges.begin();
    for (int i = 0; i < nodeArray[n].edges.size(); i++) {
        if (!nodeArray[*curr].visited) {
            dfsHelper(*curr);
        }
        ++curr;
    }
    return;
}
//----------------------------------------------------------------------------
// GraphL displayGraph
// Display Graph goes through and prints each node, location, 
// and the different paths
void GraphL::displayGraph() {
    cout << "Graph:" << endl;
    for (int i = 1; i <= size; i++) {

        cout << "Node " << i << "       " << nodeArray[i].data << endl;

        list<int>::iterator curr = nodeArray[i].edges.begin();
        for (int j = 0; j < nodeArray[i].edges.size(); j++) {
            cout << "   "<<"edge" << " " << i << " ";
            cout << *curr << endl; 
            ++curr;
        }
    }
    cout << endl;
}