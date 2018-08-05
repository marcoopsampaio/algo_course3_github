#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>
#include <set>
#include <list>
#include <map>
#include <iterator>
#include "../src/graph.hpp"
#include "../src/utilities.hpp"
#include <boost/pending/disjoint_sets.hpp>

int nbits24(int node){
  //std::cout<<"node_init is " << std::bitset<32>(node) << std::endl;
  int nbits = 0;
  for(int i = 0; i != 24; ++i){
    nbits += node & 1;
    node = node >> 1;
    //std::cout<<"node is " << std::bitset<32>(node) << std::endl;
  }
  //std::cout << "nbits is "<< nbits << std::endl;
  return nbits;
}

bool compare_nbits(std::tuple<int, int> a, std::tuple<int, int> b) {
  if(nbits24(std::get<1>(a)) == nbits24(std::get<1>(b)))
    return std::get<1>(a) < std::get<1>(b);
  return nbits24(std::get<1>(a)) < nbits24(std::get<1>(b));
}

int main(){
  std::string filename = "assignment2_docs/clustering_big.txt";
  std::ifstream data_file(filename);
  int nlines, nbits;
  data_file >> nlines >> nbits; // eliminate first line
  int bit;
  std::vector<std::tuple<int, int> > nodes;
  std::set<int> nodes_set;
  std::map<int, std::vector<int> > nodes_map;
  for(int i = 0; i < nlines; ++i){
    int node_bits = 0;
    for(int j = 0; j < nbits; ++j){
      data_file >> bit;
      node_bits = node_bits | (bit << (nbits-1-j));
    }
    nodes.push_back(std::tuple<int, int>(i,node_bits));
    nodes_set.insert(node_bits);
    if(nodes_map.find(node_bits) != nodes_map.end()){
      nodes_map[node_bits].push_back(i);
      //std::cout<<"bla"<< std::endl;
    }
    else{
      nodes_map[node_bits] = std::vector<int>(1,i);
      //std::cout<<"blu"<< std::endl;
    }
    //std::cout << std::bitset<32>(node_bits)<<std::endl;
  }

  // Make groups by number of bits


  //std::cout << std::bitset<32>(nodes[0])<<std::endl;
  std::cout << "diff_lengths is "<< (((int) nodes_set.size()) - ((int) nodes.size()))<<std::endl;
  // for(int node: nodes){
  //   std::cout << std::bitset<32>(node)<<std::endl;
  // }
  // nbits24(15787216);
  // nbits24((1 << 24) -1);

  // sort vector in groups by number of bins and by ascending order within each group
  std::sort(nodes.begin(), nodes.end(), compare_nbits);
  // Create 25 groups
  std::vector< std::list< std::tuple<int, int> > > vec_by_nbits(25,
    std::list< std::tuple<int, int> >());
  for(auto & node: nodes){
    vec_by_nbits[nbits24(std::get<1>(node))].push_back(node);
  }
  for(auto & lis: vec_by_nbits){
    std::cout<< "length is "<< lis.size() << std::endl;
  }

  // first consider the special case of d=0 (i.e. nodes with same label)

  /*
    For this particular problem we only need distances up to 2, because,
    to be able to comply with the exercise's requirement to have minimum distance
    between clusters larger than d=2, we need to check all length 2 edges before
    being able to add length d=3 edges to the clustering.
    If we hash the labels, then we can easily look up a label. Furthermore, for each
    distance we can do a linear scan over all labels to check if there is an edge to
    any of the possible binomial(24, d) distance d node. For edge lengths smaller than 3
    this 1, 24 or 276 for d=0,1,2. This means that at most we will have to build
    a graph with at most 200 000*(297) edges (and probably much less because we
    have much less than 2^24 nodes).

    In fact, we can first build all the edges and then use precisely the same code
    as before!
  */
  std::string filename2("temp.txt");
  /*std::ofstream fgraph_red(filename2);

  // d = 0
  for(auto & item: nodes_map){
    for(int i = 0; i !=  item.second.size(); ++i){
      for(int j = i + 1; j != item.second.size(); ++j ){
        // print edge to file
        fgraph_red << item.second[i] << "\t" << item.second[j] << "\t" << 0 << std::endl;
      }
    }

  }

  // d = 1
  for(auto & item: nodes_map){
    for(int b1 = 1; b1 !=24; ++b1){
      int key2 = item.first;
      key2 ^= (1 << b1);
      if(nodes_map.find(key2) != nodes_map.end()){
        for(int i = 0; i !=  item.second.size(); ++i){
          for(int j = 0; j != nodes_map[key2].size(); ++j ){
            // print edge to file
            fgraph_red << item.second[i] << "\t" << nodes_map[key2][j] << "\t" << 1 << std::endl;
          }
        }
      }
    }
  }

  // d = 2
  for(auto & item: nodes_map){
    for(int b1 = 1; b1 !=24; ++b1){
      for(int b2 = b1+1; b2!=24; ++b2){
        int key2 = item.first;
        key2 ^= (1 << b1);
        key2 ^= (1 << b2);
        if(nodes_map.find(key2) != nodes_map.end()){
          for(int i = 0; i !=  item.second.size(); ++i){
            for(int j = 0; j != nodes_map[key2].size(); ++j ){
              // print edge to file
              fgraph_red << item.second[i] << "\t" << nodes_map[key2][j] << "\t" << 1 << std::endl;
            }
          }
        }
      }
    }
  }*/



  std::ifstream graphin(filename2);
  Graph g0(graphin, 0, false, true); // undirected weighted read from edges list
  graphin.close();

  Clustering_hamming(g0, 120000);



}
