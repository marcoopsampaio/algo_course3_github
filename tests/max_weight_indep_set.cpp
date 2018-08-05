#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>
#include <set>
#include <list>
#include <map>
#include <utility>
#include <iterator>
#include "../src/graph.hpp"
#include "../src/utilities.hpp"
#include <boost/pending/disjoint_sets.hpp>


int main(){
  std::string filename = "assignment3_docs/mwis.txt";
  //std::string filename = "assignment3_docs/testcase4.txt";
  std::ifstream data_file(filename);
  int nlines;
  data_file >> nlines; // eliminate first line

  // Map to store nodes with given label
  std::vector<long> weights;
  long weight;
  for(int i = 0; i < nlines; ++i){
      data_file >> weight;
      weights.push_back(weight);
  }
  std::vector<long> sols(weights.size()+1);
  sols[0] = 0;
  sols[1] = weights[0];
  for(int i = 2; i < weights.size()+1; ++i){
    sols[i] = std::max(sols[i-1], sols[i-2] + weights[i-1]);
    //std::cout<<"sol[" << i << "] " <<sols[i]<< std::endl;
  }
  std::map<int, long> sol_vertices;
  for(int i = weights.size(); i>0;--i){
    //std::cout << "(i, weight) is "<<i<<", "<< sum_weights[i-1]<<std::endl;
    if(i==1){
      // Special case where the last decision is such that we did not include vertex 2
      sol_vertices[1] = weights[0];
    }
    else if(sols[i-1] < sols[i-2]+weights[i-1]){
      sol_vertices[i] = weights[i-1];
      --i; // skip the next one
    }
  }


  // Query map
  std::vector<int> query{1, 2, 3, 4, 17, 117, 517, 997};
  //std::vector<int> query{1, 2, 3, 4, 5,6,7,8,9,10};
   for(auto & item: query){
     if(sol_vertices.find(item) != sol_vertices.end())
      std::cout << 1;
    else
      std::cout << 0;
   }
   std::cout<< std::endl;

}
