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
  std::string filename = "assignment3_docs/knapsack1.txt";
  //std::string filename = "assignment3_docs/testcase4.txt";
  std::ifstream data_file(filename);
  int knaps_size, nlines;
  data_file >> knaps_size;
  data_file >> nlines;

  // Map to store nodes with given label
  std::vector<std::pair<long, long> > knaps_items;
  long value, weight;
  for(int i = 0; i < nlines; ++i){
      data_file >> value;
      data_file >> weight;
      knaps_items.push_back(std::pair<long, long>(value, weight));
      std::cout<< value << " "<<weight<< std::endl;
  }

  std::vector< std::vector<long> > knap_sols(nlines + 1,
    std::vector<long>(knaps_size + 1, 0));

  for(long i = 1; i < nlines; ++i){
    for(long x = 0; x <=knaps_size; ++x){
      if(x - knaps_items[i].second < 0){
        knap_sols[i][x] = knap_sols[i-1][x];
      }
      else{
        knap_sols[i][x] = std::max(knap_sols[i-1][x],
          knap_sols[i-1][x - knaps_items[i].second] + knaps_items[i].first);
      }
    }
  }
  std::cout << knap_sols[nlines - 1][knaps_size] << std::endl;


}
