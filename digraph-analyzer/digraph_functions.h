#ifndef DIGRAPH_FUNCTIONS_H
#define DIGRAPH_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

//function that will take in a word and output the word in lowercase and without punctuation
std::string preprocess_text ( std::string word );

//function that will read in a file and output the digraphs/trigraphs in the file and in which words they occur
std::map<std::string, std::vector<std::string> > process_text ( const std::string file_in);

//function that will print out all instances of the digraph taking input from process text and print them in ascii order
void digraph_sorter_a( std::map<std::string, std::vector<std::string> > instances);

//function will print out all instances of digraphs in reverse ascii order
void digraph_sorter_r( std::map<std::string, std::vector<std::string> > instances);

//helper function to compare lengths of vectors to help with sorting in counting order
bool sort_descending(std::pair<std::string, std::vector<std::string> > one, std::pair<std::string, std::vector<std::string> > two);

//function that will print out all instances of digraphs in count order with ties split with ascii values
void digraph_sorter_c( std::map<std::string, std::vector<std::string> > instances);

//function that handles queries inputed by the user and prints
void queries(std::map<std::string, std::vector<std::string> > instances);

#endif