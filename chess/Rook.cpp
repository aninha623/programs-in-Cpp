//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#include "Rook.h"

namespace Chess{ 

    //return true if move shape is legal by checking final position
    bool Rook::legal_move_shape(const Position& start, const Position& end) const {
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
        //rooks can only move vertically/horizontally, so either the columns match
        //or the rows match, they both can't match
        else if (current_row != final_row && current_col != final_col){
            return false;
        }
        //if moving vertically (up/down a column)
        else if (current_col == final_col){
            return true;
        }
        //if moving horizontally (across a row)
        else if (current_row == final_row){
            return true;
        }
        else{
            return false;
        }
    }

}