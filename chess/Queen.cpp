//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#include "Queen.h"

namespace Chess {
    bool Queen::legal_move_shape(const Position& start, const Position& end) const {

        //seeing if the queen didnt move then return false
        if(start == end) {
            return false;
        }

        int horizontal = abs(start.first - end.first);
        int vertical = abs(start.second - end.second);

        //for a vertical move is valid for queen
        if(horizontal == 0 && vertical != 0) {
            return true;
        }

        //a horizontal move which is valid for a queen
        else if(horizontal !=0 && vertical == 0) {
            return true;
        }

        //diagonal move for a queen which is valid
        else if(horizontal == vertical) {
            return true;
        }

        //returning false if the move is not horizontal, vertical, or diagonal
        return false;
    }
}