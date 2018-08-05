#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "../src/graph.hpp"
#include "../src/utilities.hpp"

using namespace std;

int main(){
  std::string filename = "assignment2_docs/clustering1_V2.txt";
  //std::string filename = "assignment2_docs/test_clustering.txt";
  //std::string filename = "assignment2_docs/test_clustering2.txt";
  //std::string filename = "assignment2_docs/test_clustering3.txt";
  bool directed = false;
  ifstream graphin(filename);

  cout << ">>> Testing k-clustering algorithm -----------------------\n\n"
       << "Graph filename is " << filename << "\n";
  if(directed)
    cout << "Loading graph as DIRECTED";
  else
    cout << "Loading graph as UNDIRECTED";
  cout << "\n\n" << flush;

  cout << "> Loading graph into memory ... " << endl;
  Graph g0(graphin, 0, directed, true); // undirected weighted read from edges list

  std::clog<<" ... done with loading graph! \n "<<endl;
  cout << "number of nodes is " << g0.n() << endl;
  cout << "number of edges is " << g0.m() << "\n" << endl;

  cout << "Applying the clustering algorithm... got max spacing = "
       << Clustering_max_spacing(g0, 4) << endl;


}
