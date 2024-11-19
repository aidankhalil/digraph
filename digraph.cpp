#include "digraph.h"
using namespace std;
/* Project3: define and implement a Directed Graph Adjacency Matrix from file input, and output the strongly connected components.
   Aidan Khalil | COP4530
   ---------------------------------------------------- */

//Constructor of adjacency matrix (graph) *
//This constructs the graph based on the content of an input file in the form of adjacency matrix (2d array)
DigraphMatrix::DigraphMatrix(const string& inputFile)
{
    ifstream in(inputFile);
    if(!in.is_open())           // file read validation
    {
        cout << "Error opening file.\n";
        exit(-1);
    }

   //variables
   char spaces; //used to skip spaces btwn values in inputfile and newline characters

   // read the number of vertices & edges from the inputfile.
   in >> n;
   in.get(spaces);
   in >> e;
   in.get(spaces);

   // allocate memory for the adjacency matrix
   g = new int*[n];
   for (int i = 0; i < n; ++i) {
      g[i] = new int[n];
      for (int j = 0; j < n; ++j) {
         g[i][j] = 0;
      }
    }



   //read through input file of form: 
   // vertex, (->) next vertex...
   // vertex, (->) next vertex...
   int u,v;

   for(int k=0; k<e; k++){ //will iterate from k=0 to k<= # edges
      in >> u;          //save 1st vertex to array
      in.get(spaces);   //save whitespace to var spaces
      in >> v;          //save next to 1st vertex in array, repeat loop for rest of input
      in.get(spaces);   //save newline character to spaces
      g[u][v] = 1;      //save inedge for pair u into v
   }
}

//dfsOut
//first pass: start DFS each iteration at the undiscovered vertex with the min ID
void DigraphMatrix::dfsOut(int vertex)
{
   //mark vertex as discovered
   m[vertex] = DISCOVERED;
   //-recurs until no more out-edges to undiscovered vertices exist 
   for(int i = 0; i<n; i++){
      if((g[vertex])[i] == 1 && m[i] == UNDISCOVERED)
         dfsOut(i);
   }

   //-marks a vertex explored & saves to stack when the vertex has no more unvisited out-edges
   m[vertex] = EXPLORED;
   S.push(vertex);
}

//dfsIn
//second pass: start DFS each iteration w/ first undiscovered vertex from top of stack
void DigraphMatrix::dfsIn(int vertex)
{
   //-recurse on first undiscovered vertex on stack
   //mark vertex as discovered
   m[vertex] = DISCOVERED;
   //-recurs until no more in-edges to undiscovered vertices exist 
   for(int i = 0; i<n; i++){
      if((g[i])[vertex] == 1 && m[i] == UNDISCOVERED)
         dfsIn(i);
   }

   //-marks a vertex explored & saves its component ID. has no more unvisited out-edges
   m[vertex] = EXPLORED;
   cid[vertex] = count;
}


// SCC detection: if there exists a path btwn all pairs of vertices, save verticies to the same component ID 
// SCC detection using the two-pass DFS functions (above) 
// will return a vector of ints (component ID for each vertex in the graph)
vector<int> DigraphMatrix::stronglyConnectedComponents()// const
{
   //vector of component IDs (function return type)
   vector<int> componentIDs;
   count = 0;
   //stack<int> S declared as data member in header, ensure it's empty;
   while(!S.empty())
      S.pop();

   //dfsOut iterates thru out-neighbors of starting vertex in sorted order (call dfsOut each iteration at undiscovered neighboring vertex w the minimum id)
   //-initializes all vertices as undiscovered to begin
   for(int i=0; i<n; i++)
      m[i] = UNDISCOVERED;

   //-recurs @ smallest undiscovered vertex
   for(int i=0; i<n; i++)
      if(m[i] == UNDISCOVERED)
         dfsOut(i);

   //dfsIn iterates in stack order. neighbor iteration doesn’t matter here, however, so long as reverse dfs transversal in stack order.
   //-initializes all vertices as undiscovered to begin
   for(int i=0; i<n; i++)
      m[i] = UNDISCOVERED;
   while(!S.empty()){
      int top = S.top();
      if(m[top] == UNDISCOVERED)
      {
         dfsIn(top);
         count++;
      }
      S.pop();
   }
   //GOAL: return vector containing a map of each vertex to its stronglyconnectedcomponent ID (from dfsOut)
   for(int i=0; i<n; i++){
      componentIDs.push_back(cid[i]);
   }
   //return vector of SCC component IDs
   return componentIDs;
}






/* 2D adjacency matrix visualization.
  "v" ---->
[ 0 0 0 0 0 0 1      "u"
  1 1 0 0 0 1 0     |
  0 1 0 1 1 1 0     |
  0 0 0 1 0 0 1 ]   V  
*/