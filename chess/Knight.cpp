//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#include "Knight.h"

namespace Chess {

    //returns true if move is legal
    //knight moves in L pattern, 2 vertical, 1 horizontal
    bool Knight::legal_move_shape(const Position& start, const Position& end) const {

        //take current position indices from Position pair
        char current_col = start.first; //ABCDEFGH
        char current_row = start.second; //87654321

        //take destination indices
        char final_col = end.first;
        char final_row = end.second;

        //check if the start position is the end position/no move is being made
        if (start == end){
            return false; 
        }

        //take the difference between beginning and ending positions to compare
        int vertical = abs((int)final_col - (int)current_col);
        int horizontal = abs((int)final_row - (int)current_row);

        //check if L shape move is valid
        if ((vertical == 2 && horizontal == 1) || (horizontal == 2 && vertical == 1)){
            return true;
        }
        else{
            return false;
        }
    }

}

