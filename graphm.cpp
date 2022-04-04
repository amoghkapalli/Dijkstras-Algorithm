#include "graphm.h"

//----------------------------------------------------------------------------
// GraphM No-arg Constructor
// Sets the terms in the adjacency matrix and the TableType T to INT_MAX and 
// the path value to 0. The visited bool is also false as 
// none of the nodes have been visited 
GraphM::GraphM() {
    size = 0;
    for (int row = 0; row < MAXNODES; row++) {
        for (int col = 0; col < MAXNODES; col++) {
            C[row][col]=INT_MAX;
            T[row][col].visited = false;
            T[row][col].dist = INT_MAX;
            T[row][col].path = 0;
        }
    }
}


GraphM::~GraphM()
{
}

//----------------------------------------------------------------------------
// GraphM buildGraph
// Goes through the file and gets the information starting with the size 
// and the locations. Then, the triple touples on each line are added 
// to the adjacency matrix
void GraphM::buildGraph(ifstream &file){
    file >> size;
    if (file.eof()) return;
    string line;
    getline(file, line);
    for (int i = 1; i <= size; ++i) 
		data[i].setData(file);
    int start=0;
	int destination=0;
    int dist=0; 
	while (file >> start >> destination >> dist) {
        if (file.eof()) return;
		if (start == 0) break;
		C[start][destination] = dist;
	}
}

//----------------------------------------------------------------------------
// GraphM insertEdge
// Inserts a distance into the adjacency matrix with index [start][dest]
// if conditions are met.
bool GraphM::insertEdge(int start, int dest, int distance) {
	if (start > size || start < 1 || dest > size || dest < 1){
        return false;
    }
	if ((distance != 0 && start == dest) || distance<0){
        return false;
    }
	C[start][dest]=distance;
    findShortestPath();
	return true;
}
//----------------------------------------------------------------------------
// GraphM removeEdge
// Removes the distance between two edges and sets it to INT_MAX
bool GraphM::removeEdge(int start, int dest) {
	if (start > size || start < 1 || dest > size || dest < 1){
        return false;
    }
	C[start][dest]=INT_MAX;
    findShortestPath();
	return true;
}

//----------------------------------------------------------------------------
// GraphM findShortestPath
// Finds the shortest path from one node to the other nodes using Dijkstra's.
void GraphM::findShortestPath(){
    for (int curr = 1; curr <= size; curr++){
        T[curr][curr].dist = 0;
        T[curr][curr].visited = true;
        for (int i = 1; i <= size; i++){
            if (C[curr][i] != INT_MAX) {
        //sets the values in the adjacency matrix with values into the table
                T[curr][i].dist = C[curr][i];
                T[curr][i].path = curr;
            }
        }

        while(true){
            int min= INT_MAX;
            int vertVisited=0;
            for (int n = 1; n <= size; n++) {
                if (!T[curr][n].visited && C[curr][n] < min) {
                    min=C[curr][n];// min is set to the cost associated
                    // the smallest vertex is set to the current node
                    vertVisited=n;
                }
            }
            if(vertVisited==0){
                break;
            }
            else{
                T[curr][vertVisited].visited = true;
                for (int w = 1; w <= size; w++) {
                    if (vertVisited != w && !T[curr][w].visited 
                    && C[vertVisited][w] != INT_MAX) {
                    //checks if the new adjacent vertex has a smaller distance
                        if (T[curr][vertVisited].dist + C[vertVisited][w] 
                        < T[curr][w].dist) {
                            T[curr][w].dist = T[curr][vertVisited].dist
                            + C[vertVisited][w];
                            T[curr][w].path = vertVisited;
                        }
                    }
                }
            }
        }
    }
}

//----------------------------------------------------------------------------
// GraphM display
// Displays the single cost info and path from one node to another
void GraphM::display(int start, int dest) {
	if ((start > size || start < 0) || (dest > size || dest < 0)) {
		cout << setw(3) << start << setw(9) << dest; 
		cout << setw(8) << "---" << endl; 
		return;
	}
	cout << setw(3) << start << setw(9) << dest;
	if (T[start][dest].dist != INT_MAX) {
		cout << setw(12) << T[start][dest].dist << setw(12);
		findPath(start, dest);
		cout << endl;
		findData(start, dest);
	}
	else cout << setw(8) << "---" << endl;
	cout << endl;
	
}

//----------------------------------------------------------------------------
// GraphM displayAll
// Writes the total display for all of the locations
void GraphM::displayAll() {
	cout << "Description" << setw(20) << "From Node" << setw(10) <<
		"To Node" << setw(14) << "Djikstra's" << setw(8) << "Path" << endl;

	for (int start = 1; start <= size; ++start) {
		cout << data[start] << endl << endl;
		for (int dest = 1; dest <= size; dest++) {
			if (T[start][dest].dist != 0) { 
				cout << setw(27) << start << setw(10) << dest;
				if (T[start][dest].dist == INT_MAX)
					cout << setw(12) << "---" << endl;
				else {
					cout << setw(12) << T[start][dest].dist;
					cout << setw(10);

					findPath(start, dest);
					cout << endl;
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
// GraphM findPath
// Helper method to find the path for edges
void GraphM::findPath(int start, int dest) {
	if (start == dest && T[start][dest].path==0) {
		cout << dest << " ";
		return;
	}
	int pathInfo = dest;
	findPath(start, T[start][dest].path);
	cout << pathInfo << " "; 
}

//----------------------------------------------------------------------------
// GraphM findPath
// Helper method to find the data and costs
void GraphM::findData(int start, int dest) {
	if (start == dest && T[start][dest].path==0) { 
		cout << data[dest] << " ";
		return;
	}
	int nodeInfo = dest; 
	findData(start, dest = T[start][dest].path);
	cout << data[nodeInfo] << endl << endl;
}

