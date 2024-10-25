#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

#include "digraph_functions.h"

//all my usings because i don't like how std::whatever looks in the code
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

int main(int argc, char * argv[]) {
  // if number of arguments is not correct, exit with code 1!
  if (argc != 3) {
    cout<<"Invalid arguments";
    return 1;
  }

  // if the "order" argument is not valid, exit with code 1!
  string order(argv[2]);
  if (order != "r" && order != "a" && order != "c") {
    cout<<"Invalid arguments";
    return 1;
  }

  //take the input file from argv
  string input_file = argv[1];
  //process the file and store the instances of di/trigraphs in a map
  map<string, vector<string> > instances = process_text(input_file); //print all instances of digraphs
  
  //print in the order designated by user
  if (order == "a"){
    digraph_sorter_a(instances);
  }
  else if (order == "r"){
    digraph_sorter_r(instances);
  }
  else if (order == "c"){
    digraph_sorter_c(instances);
  }

  queries(instances); //handle queries

  return 0;
}