//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"
#include "Exceptions.h"
#include "CreatePiece.h"


namespace Chess
{
  class Board {

		// Throughout, we will be accessing board positions using Position defined in Piece.h.
		// The assumption is that the first value is the column with values in
		// {'A','B','C','D','E','F','G','H'} (all caps)
		// and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

	public:
		// Default constructor
		Board();

		//copy constructor for board
		Board(const Board& other){
			for (std::map < Position, Piece*>::const_iterator it = other.occ.begin(); it != other.occ.end(); ++it){
				Position position = it->first;
				const Piece* piece = it->second;
				if (piece){
					Piece* new_piece = create_piece(piece->to_ascii());
					occ[position] = new_piece;
				}
				else{
					occ[position] = nullptr;
				}
			}
		}

		//destructor in board class
		~Board () {
			for (std::map <Position, Piece*>::iterator it = occ.begin(); it != occ.end(); ++it) {
				delete it->second;
			}
			occ.clear();
		}

		//clears board for istream overload
		void clear_board() {
			for (std::map <Position, Piece*>::iterator it = occ.begin(); it != occ.end(); ++it) {
				delete it->second;
			}
			occ.clear();
		}

		// Returns a const pointer to the piece at a prescribed location if it exists,
		// or nullptr if there is nothing there.
		const Piece* operator() (const Position& position) const;

		// Attempts to add a new piece with the specified designator, at the given position.
		// Throw exception for the following cases:
		// -- the designator is invalid, throw exception with error message "invalid designator"
		// -- the specified position is not on the board, throw exception with error message "invalid position"
		// -- if the specified position is occupied, throw exception with error message "position is occupied"
		void add_piece(const Position& position, const char& piece_designator);

		// Displays the board by printing it to stdout
		void display() const;

		// Returns true if the board has the right number of kings on it
		bool has_valid_kings() const;

		//moving pieces on the board, helper for make_move
		void move_piece(const Position& start, const Position& end);

		//helper to move piece, checks if there are pieces in the way of move (except for if knight)
		bool path_is_clear(const Position& start, const Position& end) const;

		//create iterator to iterate over the board and each position
  		class iterator {
    		private:
				Position current_pos;
        
			public:
				//constructor to start at position A1
				iterator(char column = 'A', char row = '1') : current_pos(column, row) {}
    			//overload dereference operator
				//return coordinates
				Position &operator * (){
					return current_pos;
				}
				//overload preincrement operator
				iterator &operator ++ (){
					//if the column is less than H, preincrement/ go to the next letter 
					if (current_pos.first < 'H'){
						++current_pos.first;
					}
					//if you get to H and you aren't at the last row, reset to the first 
					//column and go to the next row
					else if ((current_pos.first == 'H') && (current_pos.second < '8')){
						current_pos.first = 'A';
						++current_pos.second;
					}
					//if you are on the last element, set to equal the last element
					else {
						current_pos = {'I', '9'};
					}
					return *this; //return the position that the iterator is at 
				}
	    		//overload inequality operator
				//return true if the current position and whatever other iterator position are equal
				bool operator != (const iterator &i) const{
					return i.current_pos != current_pos;
				}
  		};
		//set the start of the iterator to the first index
		iterator begin(void) const {
			return iterator('A','1');
		}
		//set the end of the iterator to the last index
		iterator end(void) const {
			return iterator('I', '9');
		}

	private:
		// The sparse map storing the pieces, keyed off locations
		std::map<Position, Piece*> occ;


        // Write the board state to an output stream
        friend std::ostream& operator<< (std::ostream& os, const Board& board);
	};
}
#endif // BOARD_H
