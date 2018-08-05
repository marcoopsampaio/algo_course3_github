#include "jobs_greedy_difference.hpp"

int main(){
    using t1 = std::tuple<int, int, int> ;
    using t2 = std::tuple<int, int, double> ;

    std::vector< t1 > jobs;
    std::vector< t2 > jobs_ratio;
    std::ifstream filein("assignment1_docs/jobs.txt");

    int nlines;
    filein >> nlines;
    std::cout << "nlines is "<< nlines << '\n';
    int read_val1, read_val2;
    while((filein >> read_val1) && (filein >> read_val2)){
      jobs.push_back(t1(read_val1, read_val2, read_val1 - read_val2));

      jobs_ratio.push_back(t2(read_val1, read_val2, read_val1*1.0/read_val2));
    }

    filein.close();



    // Apply scheduling algorithm by sorting diffs
    std::sort( jobs.begin(), jobs.end(), compare_tuples<int, int, int>);

    long long sum = 0, comp_time = 0;
    for(auto & it: jobs){
      // std::cout << "( "
      //           << std::get<0>(it) << ", "
      //           << std::get<1>(it) << ", "
      //           << std::get<2>(it) << ")" << std::endl;
      comp_time += std::get<1>(it);
      sum += std::get<0>(it) * comp_time;
    }

    std::cout << "The weighted sum of completions times for the diff is  "
              << sum << std::endl;

    // Apply scheduling algorithm by sorting ratios
    std::sort( jobs_ratio.begin(), jobs_ratio.end(), compare_tuples<int, int, double>);
    sum = 0;
    comp_time = 0;
    for(auto & it: jobs_ratio){
      // std::cout << "( "
      //           << std::get<0>(it) << ", "
      //           << std::get<1>(it) << ", "
      //           << std::get<2>(it) << ")" << std::endl;
      comp_time += std::get<1>(it);
      sum += std::get<0>(it) * comp_time;
    }

    std::cout << "The weighted sum of completions times for the ratio is "
              << sum << std::endl;


}
