#ifndef __DIGRAPH_MATRIX_H
#define __DIGRAPH_MATRIX_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };

class DigraphMatrix
{
  friend ostream& operator<<(ostream& out, const DigraphMatrix& graph); 

private:
  vector<bool> A;
  int n;          // n = num of vertices 
  int** g;        // g = adjacency matrix (2d int array)  
  int e;          // e = num of edges
  stack<int> S;   // S = empty stack

  unordered_map<int, mark_t> m;   // m = discovered status map
  unordered_map<int, int> cid;    // cid = componentID map
  int count=0;                    // count (currentID) is used to count upwards from ID 0 (i.e. 0,1,2,3,...)

public:
  //Reads in digraph from given file & stores graph as an adjacency matrix *Required*
  DigraphMatrix(const string&);

  //2-pass dfs functions *Required*
  void dfsOut(int);
  void dfsIn(int);

  //Returns vector containing component ID for each vertex  *Required*
  vector<int> stronglyConnectedComponents();

  //Helper functions:
  vector<int> getNeighbors(const int& v) const;
  bool isAdjacent(const int& v1, const int& v2) const;
};

ostream& operator<<(ostream& out, const DigraphMatrix& graph);

#endif