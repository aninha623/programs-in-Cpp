//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#include "King.h"

namespace Chess
{
    bool King::legal_move_shape(const Position& start, const Position& end) const {
		//king can move one step behind, in front, diagonal, to the side of itself
		//extract positions
		char column_start = start.first;
		char row_start = start.second;
		char column_end = end.first;
		char row_end = end.second;

		//calculating difference in columns/rows - should only be a difference of one
        int column_diff = abs(column_end - column_start);
        int row_diff = abs(row_end - row_start);

		return ((column_diff == 1 || row_diff == 1) && (column_diff <= 1 && row_diff <= 1));
	}	
}