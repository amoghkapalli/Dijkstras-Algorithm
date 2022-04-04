#include <iostream>
#include <fstream>
#include "graphm.h"
#include "graphl.h"
using namespace std;

int main() {
   
   // part 1
   ifstream infile1("data31.txt");
   if (!infile1) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   //for each graph, find the shortest path from every node to all other nodes
   for(;;){
      GraphM G;
      G.buildGraph(infile1);
      if (infile1.eof()) 
         break;
      G.findShortestPath();        
      G.displayAll();           // display shortest distance, path to cout
      G.display(1,4);           // display dist/path from node 3 to 1 to cout
      // may be other calls to display 
   }
   
  // part 2 
   ifstream infile2("data32.txt");
   if (!infile2) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   //for each graph, find the depth-first search ordering
   for (;;) {
      GraphL G;
      G.buildGraph(infile2);
      if (infile2.eof()) 
         break;
      G.displayGraph();
      G.depthFirstSearch();    // find and display depth-first ordering to cout
   }
 
   cout << endl;
   return 0;
   
}