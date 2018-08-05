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
  std::string filename = "assignment3_docs/huffman.txt";
  std::ifstream data_file(filename);
  int nlines;
  data_file >> nlines; // eliminate first line
  // Map to store nodes with given label
  std::vector<int> weights;
  int weight;
  // loop over lines of file
  for(int i = 0; i < nlines; ++i){
      data_file >> weight;
      weights.push_back(weight);
  }
  //sort values in ascending order
  std::sort(weights.begin(), weights.end());
  std::list<std::tuple<int, int, int> > tree;
  for(int i = 0; i < nlines; ++i){
    tree.push_back(std::tuple<int, int, int>(weights[i],0, 0));
  }

  while(tree.size()> 1){
    // merge first and second element of list
    std::tuple<int, int, int> item1 = *(tree.begin());
    tree.pop_front();
    std::tuple<int, int, int> item2 = *(tree.begin());
    tree.pop_front();
    std::tuple<int, int, int> item_meta = std::tuple<int, int, int>(
      std::get<0>(item1) + std::get<0>(item2),
      std::max(std::get<1>(item1), std::get<1>(item2))+1,
      std::min(std::get<2>(item1), std::get<2>(item2))+1
    );
    //std::cout << " length "<< std::max(item1.second, item2.second)+1<< std::endl;
    bool inserted = false;
    // migrate meta-symbol up
    for(std::list<std::tuple<int, int, int> >::iterator item = tree.begin();
     item != tree.end(); ++item){
      if(std::get<0>(*item) >= std::get<0>(item_meta)){
        inserted = true;
        tree.insert(item, item_meta);
        break;
      }
    }
    if(!inserted){
      tree.insert(tree.end(), item_meta);
    }
  }
  std::cout << "Max code length is "<< std::get<1>(*(tree.begin())) << std::endl;
  std::cout << "Min code length is "<< std::get<2>(*(tree.begin())) << std::endl;
}
