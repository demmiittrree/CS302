#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>

using namespace std;

// You will need an adjacency list, since each node is labeled by a
// string, a hash map will be used, the structure is declared below.
std :: unordered_map < std :: string , std :: list < std :: string > > adjList ;

// This maps a location to a linked list of its neighbor locations. 
// You will also need a map to track the amount of enemies at a location
std :: unordered_map < std :: string , int > enemiesAtLocation ;

// You also need a ”visited” array, this map will be used to store the amount 
// of ammo Leon has when he arrives at a location, if another path in 
// the future is found to this location but Leon has less ammo in this time,
// then you do not revisit the node, only revisit if the amount of ammo Leon
// has is more than the last time he visited this node, the structure is defined below
std :: unordered_map < std :: string , int > ammoAtLocation ;

// And of course in order to output the path Leon takes, you will need a predecessor array
std :: unordered_map < std :: string , std :: string > predecessor ;

int main() {
    ifstream iFile;
    string from , to ;
    iFile >> from >> to ;
    adjList[from].push_back(to);
    // You can iterate through all the neighbors of any location using the following techniques
    for (auto neighbor = adjList[location].begin();
        neighbor != adjList[location].end(); neighbor++)
    {
        * neighbor ; // retrieves the neighbor node name
    }
    for ( auto neighbor : adjList [location])
    {
        neighbor ; // retrieves the neighbor node name
    }
}