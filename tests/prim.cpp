#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "../src/graph.hpp"
#include "../src/utilities.hpp"

using namespace std;

int main(){
  std::string filename = "assignment1_docs/edgesV2.txt";
  bool directed = false;
  ifstream graphin(filename);

  cout << ">>> Testing Prim's algorithm -----------------------\n\n"
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

  cout << "Applying Prim's algorithm... got MST weight = "
       << Prim_MST_weight(g0) << endl;
  // if(printgraph)
  //g0.print_graph(cout, true);

  // cout << "> Applying DFS to find all connected components (regardless of "
  //   "directionality) ... \n" << endl;
  //
  // vector<bool> g0explored;
  // vector<unsigned int> cc0_nodes;
  // std::vector<std::vector<unsigned int> > all0_ccs;
  // DFS_all_connected_components(g0, all0_ccs);
  //
  // set<unsigned int> cc0_sizes;
  // multiset<unsigned int> cc0_sizes_multi;
  // for(std::vector<std::vector<unsigned int> >::iterator it =
	// all0_ccs.begin(); it != all0_ccs.end(); ++it)
  //   {
  //     cc0_sizes.insert(it->size());
  //     cc0_sizes_multi.insert(it->size());
  //   }
  //
  // cout << "Found " << all0_ccs.size() << " connected components with "
  //      << cc0_sizes.size() << " different sizes. \n \n"
  //      << "Summary of top " << nprint << " (size, multiplicity) pairs: \n";
  //
  // set<unsigned int>::iterator it0 = cc0_sizes.end();
  // for(unsigned int i = 0; i != nprint && i < cc0_sizes.size(); ++i)
  //   {
  //     --it0;
  //     cout << "(" << *it0 << ", " << cc0_sizes_multi.count(*it0) <<  ")"
	//    << endl;
  //   }
  // cout << endl;
  //
  // cout << "> Applying DFS to find all nodes reachable from "
  //      << node1 << "... \n"
  //      << endl;
  // std::vector<unsigned int> cfrom_nodes;
  // DFS_reachable_from(g0, node1, cfrom_nodes);
  //
  // cout << " Printing "
  //      << ((nprint < cfrom_nodes.size()) ? nprint : cfrom_nodes.size())
  //      << " nodes reachable: \n";
  //
  // for(unsigned int i = 0; i < nprint && i < cfrom_nodes.size(); ++i)
  //   cout << cfrom_nodes[i] << ", \t";
  // cout << "\n" << endl;
  //
  // std::vector<double> dists;
  // std::vector< std::vector<unsigned int> > paths;
  // Dijkstra_shortest_paths(g0, 0, dists, paths);
  //
  // cout << "> Printing out Dijkstra's algorithm results\n" << endl
  //      << ">> Shortest paths and lengths "<< endl;
  // for(unsigned int i = 0; i != dists.size(); ++i)
  //   {
  //     cout << " Node " << i + 1 << " with path length " << dists[i] << " | Path: ";
  //     for(unsigned int j = 0; j != paths[i].size(); ++j)
	// cout << paths[i][j] +1 << ", ";
  //     cout << endl;
  //   }

}
