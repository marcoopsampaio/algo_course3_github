#ifndef JOBS_GREEDY_DIFFERENCE_H
#define JOBS_GREEDY_DIFFERENCE_H
#include<vector>
#include<tuple>
#include<iostream>
#include<fstream>
#include<algorithm>


// This order relation gives lower weight to larger values
template<typename T1, typename T2, typename T3>
bool compare_tuples (std::tuple< T1, T2, T3> a, std::tuple< T1, T2, T3> b) {
  if(std::get<2>(a) == std::get<2>(b)){
    return std::get<0>(a) > std::get<0>(b);
  }
  return std::get<2>(a) > std::get<2>(b);
}


#endif
