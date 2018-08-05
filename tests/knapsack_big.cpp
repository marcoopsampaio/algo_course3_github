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

int knap_count = 0;

std::string make_key(long i, long x){
  return std::to_string(i)+":"+std::to_string(x);
}

long knap_recurse(std::vector<std::pair<long, long> > & knaps_items, int i, int x,
  std::map<std::string, long> &knap_sols){
    //std::cout<<"i,x,  = "<< i <<" , "<< x << std::endl;
    ++knap_count;
    if(knap_count % 20000000 == 0){
      std::cout << "percent progress is "<< knap_count*100.0/(2000000. * 2000.)<<std::endl;
    }
    std::string key1 = make_key(i,x);
    std::string key2 = make_key(i-1,x);

    if(i==0){
      knap_sols[key1] = 0;
    }
    else if(x - knaps_items[i].second < 0){
      if(knap_sols.find(key2) == knap_sols.end())
        knap_sols[key1] = knap_recurse(knaps_items, i-1, x, knap_sols);
      else
        knap_sols[key1] = knap_sols[key2];
    }
    else{
      std::string key3 = make_key(i-1,x - knaps_items[i].second);
      long val1, val2;
      if(knap_sols.find(key2) != knap_sols.end())
        val1 = knap_sols[key2];
      else
        val1 = knap_recurse(knaps_items, i-1, x, knap_sols);
      if(knap_sols.find(key3) != knap_sols.end())
          val2 = knap_sols[key3];
      else
          val2 = knap_recurse(knaps_items, i-1, x - knaps_items[i].second, knap_sols);

      knap_sols[key1] = std::max(val1,val2 + knaps_items[i].first);
    }
    return knap_sols[key1];

}

int main(){
  std::string filename = "assignment3_docs/knapsack_big.txt";
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
      //std::cout<< value << " "<<weight<< std::endl;
  }

  std::map<std::string, long> knap_sols;

  // // Initialise zero entries
  // for(long x = 0; x <=knaps_size; ++x)
  //   knap_sols[make_key(0,x)] = 0;

  std::cout<< knap_recurse(knaps_items, nlines-1, knaps_size, knap_sols) << std::endl;
  return 0;




  // for(long i = 1; i < nlines; ++i){
  //
  //   for(long x = 0; x <=knaps_size; ++x){
  //     std::string key1 = make_key(i,x);
  //     std::string key2 = make_key(i,x);
  //     std::string key3 = make_key(i,x);
  //
  //     if(x - knaps_items[i].second < 0){
  //       knap_sols[i][x] = knap_sols[i-1][x];
  //     }
  //     else{
  //       knap_sols[i][x] = std::max(knap_sols[i-1][x],
  //         knap_sols[i-1][x - knaps_items[i].second] + knaps_items[i].first);
  //     }
  //   }
  // }
  // std::cout << knap_sols[nlines - 1][knaps_size] << std::endl;


}
