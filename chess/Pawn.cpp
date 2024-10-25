//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#include "Pawn.h"

namespace Chess 
{
	bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
		//only moves forward, incrementing a row for white and decrementing a row for black
		//extracting position
		char column_start = start.first;
		char row_start = start.second;
		char column_end = end.first;
		char row_end = end.second;

		//for moving forward, pawn always moving in straight line, column should not change!
		if (column_start == column_end) {
			if (is_white()) {
				if (row_start == '2' && (row_end == '3' || row_end == '4')) { //pawn can move forward twice in first move
					return true;
				}
				return  row_end == row_start + 1; //for any other instance
			}
			else {
				if (row_start == '7' && (row_end == '6' || row_end == '5')) { //pawn can move forward twice in first move
					return true;
				}
				return row_end == row_start - 1; //for any other instance
			}
		}
		return false;
	}

	bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
		//extracting position
		char column_start = start.first;
		char row_start = start.second;
		char column_end = end.first;
		char row_end = end.second;

		if ((is_white() && row_end == row_start + 1) && (abs(column_end - column_start) == 1)) { //white should always increment one row when capture
			return true; //if legal, column should always change by one
		}

		else if((!is_white() && row_end == row_start - 1) && (abs(column_end - column_start) == 1)) { //white should always increment one row when capture
			return true; //if legal, column should always change by one
		}

		return false;
	}
}
