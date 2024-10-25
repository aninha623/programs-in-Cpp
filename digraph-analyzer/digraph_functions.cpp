#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <sstream>

//all my usings because i don't like how std::whatever looks in the code
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::ifstream;
using std::ofstream;
using std::isalpha;
using std::isspace;
using std::tolower;
using std::sort;
using std::pair;
using std::stoi;
using std::stringstream;


//return type: string which is just whatever gets put into it but lowercase and
//without punctuation
//parameters: a word (string)
string preprocess_text ( string word ){
    int word_length = (int)word.length(); //take length of word
    string fixed; 
    char lower;
    for (int letter =0; letter<word_length; letter++){
        if (isalpha(word[letter])){
            lower = tolower(word[letter]);
            fixed = fixed + lower;
        }
    }
    return fixed;
}


//return type: map where key = di/trigraph and value is whatever words contain di/trigraph
//parameters: input file, pointer to list of di/trigraphs available/defined
map<string, vector<string> > process_text ( const string file_in ){
    ifstream input (file_in); //open file

    //error handling: if file failes to open
    if (!input.is_open()){
        std::cout << "File failed to open." << std::endl;
        return {};
    }

    map<string, vector<string> > instances; //initialize return 

    int number;
    //read in first word in file which is the number of digraphs/trigraphs
    input >> number;

    // loop thru to get the possible digraphs, each whitespace = new string
    // store these digraphs as the keys of a map of vectors
    for (int i=0; i< number; ++i){
        string temp_digraph; //temporary variable to store the digraphs
        input >> temp_digraph; //read in each digraph
        instances[temp_digraph] = vector<string>(); //store as keys with vector as value
    }
    
    string parse;
    //read in individual words from file
    while (input >> parse){
        //preprocess text using function defined above
        string clean_word = preprocess_text(parse);
        
        
        //check if digraph presnet in word
        map <string, vector<string> >::iterator i;
        for (i=instances.begin(); i != instances.end(); ++i){
            string digraph = i ->first; //take key from map
            size_t present = clean_word.find(digraph); //look for presense of digraph in each clean word

            //find returns npos if digraph is not found, so if it is found, add to vector map
            if( present != string::npos){
                instances[digraph].push_back(clean_word); //add clean word to vector
            }

        } 
    
    }
    input.close(); //close file

    return instances;
}

//sorts digraph map according to which argument was put into the command line
//if a is entered, sort keys of map in ascii order and print
void digraph_sorter_a( map<string, vector<string> > instances){
    map <string, vector<string> >::iterator i;
    //loop through each digraph in map
    for (i = instances.begin(); i!= instances.end(); ++i){
        cout << i-> first; //print out the digraph, will be automatically in ascii order due to use of iterator
        cout << ": [";
        size_t word; 
        size_t total_words = i->second.size();
        //loop through all the words in the vector
        for (word = 0; word < total_words; ++word){
            //print out word in vector
            cout << i-> second[word];
            //add comma as long as there's another word following
            if ((word+1)< total_words){ 
                cout << ", ";
            }
        }
        cout << "]" << endl; //close bracket
    }
    return;
}

//sorts digraph map according to which argument was put into the command line
//if r is entered, sort keys of map in reverse ascii order and print
void digraph_sorter_r( map<string, vector<string> > instances){
    map <string, vector<string> >::reverse_iterator i;
    //loop through each digraph in map
    for (i = instances.rbegin(); i!= instances.rend(); ++i){
        cout << i-> first; //print out the digraph, will be automatically in ascii order due to use of iterator
        cout << ": [";
        size_t word; 
        size_t total_words = i->second.size();
        //loop through all the words in the vector
        for (word = 0; word < total_words; ++word){
            //print out word in vector
            cout << i-> second[word];
            //add comma as long as there's another word following
            if ((word+1)< total_words){ 
                cout << ", ";
            }
        }
        cout << "]" << endl; //close bracket
    }
    return;
}

//helper function for sorter_c to help sort the vectors in the maps in descending order 
bool sort_descending(pair<string, vector<string> > one, pair<string, vector<string> > two){
    //return true if one has more words in the vector than two
    if (one.second.size() != two.second.size()){
        return one.second.size() > two.second.size();
    }

    //if vectors are the same size, tie broken by ascii order
    return one.first < two.first;

}

//sorts digraph map according to which argument was put into the command line
//if c is entered, sort keys of map in order from most words to least words
//ties are broken in order of ascii value
void digraph_sorter_c( map<string, vector<string> > instances){
    //make vector of pairs to store map for the sake of sorting
    vector < pair <string, vector<string> > > temp_sorted;
    map<string, vector<string> >::iterator j;
    for (j = instances.begin(); j != instances.end(); ++j){
        temp_sorted.push_back(*j); //add pointers instead of value so i dont have to completely make a copy
    }

    //use sort_descending helper function to sort
    sort(temp_sorted.begin(), temp_sorted.end(), sort_descending);

    vector < pair <string, vector<string> > >::iterator i;
    //loop through each digraph in map
    for (i = temp_sorted.begin(); i!= temp_sorted.end(); ++i){
        cout << i-> first; //print out the digraph, will be automatically in ascii order due to use of iterator
        cout << ": [";
        size_t word; 
        size_t total_words = i->second.size();
        //loop through all words in vector
        for (word = 0; word < total_words; ++word){
            //print out word in vector
            cout << i-> second[word];
            //add comma as long as there's another word following
            if ((word+1)< total_words){ 
                cout << ", ";
            }
        }
        cout << "]" << endl; //close bracket
    }
    return;
}


void queries(map<string, vector<string> > instances){
    string q; //initialize variable to store query
    //loop until exit is typed in
    while (true){
        q = ""; //refresh every single loop
        cout << "q?>"; //prompt
        cin >> q;

        //check if its a number
        bool flag = true;
        for (size_t i = 0; i<q.length(); i++){
            if (isdigit(q[i])==false){
                flag = false;
                break;
            }
        }
        
        //only process the query if its not a number
        if (flag == false){
            q = preprocess_text(q); 
        }

        if (q == "exit"){
            break;
        }

        //if the query is a number:
        if (flag == true){ 
            int number = std::stoi(q);
            bool present = false; //check if the digraph is actually there any number of times

            //loop through the instances of the digraphs to see if the size of the vector
            //matches the number
            map<string, vector<string> >::iterator i;
            for(i=instances.begin(); i!= instances.end(); ++i){
                int num_digraphs = i->second.size(); //number of digraphs
                //if the number of digraphs equals the number inputed by user
                if (num_digraphs== number){
                    present = true; //indicate that it was found
                    cout << i->first << ": ["; //print digraph
                    
                    //loop through to print all digraphs
                    for(size_t word = 0; word< i->second.size(); ++word){
                        cout << i->second[word];
                        if (word!= (i->second.size() -1)){ 
                            cout << ", "; //as long as its not the last word, print comma
                        }
                    }

                    cout << "]" << endl;
                }
            }
            //if the word wasn't found, print None.
            if (present == false){
                cout << "None" << endl;
            }
        }

        //if the query is a digraph
        else {
            map<string, vector<string> >::iterator i;
            i = instances.find(q); //look for q in the keys of instances

            if (i!= instances.end()){ //if it was found
                cout << i->second.size() << ": ["; //output the number

                //loop through to print all digraphs
                for(size_t word = 0; word< i->second.size(); ++word){
                    cout << i->second[word];
                    if (word!= (i->second.size() -1)){ 
                        cout << ", "; //as long as its not the last word, print comma
                    }
                }

                    cout << "]" << endl;
            }
            else{ //if the digraph wasn't found
                cout << "No such digraph" << endl;
            }
        }
    }
}
