//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#include <cassert>
#include "Game.h"
#include "Mystery.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

	void Game::make_move(const Position& start, const Position& end) {
		//checkng if position is on board
		if (start.first < 'A' || start.first > 'H' || start.second < '1' || start.second > '8') {
			throw Exception("start position is not on board");
		}
		if (end.first < 'A' || end.first > 'H' || end.second < '1' || end.second > '8') {
			throw Exception("end position is not on board");
		}

		//checking if piece is on board position
		const Piece* piece = board(start);
		if (!piece) {
			throw Exception("no piece at start position");
		}
		//check if turn and color match
		if ((piece->is_white() && !is_white_turn) || (!piece->is_white() && is_white_turn)) {
        	throw Exception("piece color and turn do not match");
    	}

		Game temp_game(*this);
		
		temp_game.board.move_piece(start, end); //trying the move on the temp board
		if (temp_game.in_check(is_white_turn)) {
			throw Exception("move exposes check");
		}

		board.move_piece(start, end);
		is_white_turn = !is_white_turn;
	}

	//helper function to find the position of the king since you have to find the king
	//in in_check, in_mate, and in_stalemate to improve readibility
	Position Game::find_king( const bool& white) const {
		//initialize Position variable for king's location
		Position position_king;

		//find king depending on which color player
		char king_id; //initialize variable
		if (white){
			king_id = 'K';
		}
		else{
			king_id = 'k';
		}

		//iterate over board to find position of king
		for (Board::iterator it = board.begin(); it != board.end(); ++it){
			const Piece* temp_king = board(*it); //store this temporary king as king
			//if the piece on the board at the iterator's position is K, king is found
			if(temp_king && ((temp_king -> to_ascii()) == king_id)){
				position_king = *it;
				break; //end the loop because king is found
			}
		}
		return position_king;
	}

	bool Game::in_check(const bool& white) const {
		//initialize Position variable for the king's location
		Position position_king = find_king(white);

		//iterate again to see if king is in check
		for (Board::iterator it = board.begin(); it != board.end(); ++it){
			const Piece* piece = board(*it); //temporary piece, will be null if no piece is present
			Position start_position = *it;
			//check if piece is null and that it is the opponent's piece
			if (piece && !(piece->is_white()==white)){ 
				//check legal_capture_shape to see if that piece can get the king
				if (piece->legal_capture_shape(*it, position_king)){
					//rook, bishop, queen, pawn check if something is in the way
					//checking if path is clear
					
					bool needs_clear = false;
					char piece_type = tolower(piece->to_ascii());
					switch (piece_type) {
						case 'r': case 'q': case 'b': case 'p': 
							needs_clear = true; //rook, queen, bishop, pawn
							break;
						case 'n': 
							needs_clear = false;
							return true;
						case 'm':  //for mystery
						//if move is L shape vs. straight/diagonal
							if (abs(start_position.first - position_king.first) == abs(start_position.second - position_king.second) || start_position.first == position_king.first || start_position.second == position_king.second) {
								needs_clear = true;
							}
							else {
								needs_clear = false; //any non-straight path
								return true;
							}
							break;
					}

					if (needs_clear && board.path_is_clear(*it, position_king)) {
						return true; //path is no clear, king is in check
					}
				}
			}
		}
		return false;
	}


	bool Game::in_mate(const bool& white) const {
		//if the player is not in a checked position to start, they are not in checkmate
		if (!in_check(white)){
			return false;
		}

		//iterate over the board to check if any move will put the king in check
		for (Board::iterator it = board.begin(); it != board.end(); ++it){
			const Piece* piece = board(*it); //temporary piece, will be null if no piece is present
			Position start_position = *it;
			//check if piece is null and that it is the player's piece
			if (piece && piece->is_white() == white){
				//check legal moves for piece
				for (Board::iterator j = board.begin(); j != board.end(); ++j){
					Position end_position = *j;
					//check if the piece moving or capturing another piece puts it in check
					if (piece -> legal_capture_shape(start_position, end_position) || piece->legal_move_shape(start_position, end_position)){
						//check if move gets the king out of check by calling in_check
						try{
							Game temp_game(*this);
							temp_game.board.move_piece(start_position, end_position); //trying the move on the temp board
							//check if the move will take the king out of check
							if (!temp_game.in_check(white)){
								return false; //move successfully took king out of check
							}
						}
						//move_piece will raise exceptions if the move fails so this will catch it to just continue to
						//the next position
						catch(const Exception &e){
							continue;
						}
					}
				}
			}
		}
		return true; //if no move will take the king out of check, player is in a checkmate
	}


	bool Game::in_stalemate(const bool& white) const {
		//if the player is in a checked position to start, they are not in a stalemate
		if (in_check(white)){
			return false;
		}

		//iterate over the board to check if any move will put the king in check
		for (Board::iterator it = board.begin(); it != board.end(); ++it){
			const Piece* piece = board(*it); //temporary piece, will be null if no piece is present
			Position start_position = *it;
			//check if piece is null and that it is the player's piece
			if (piece && piece->is_white() == white){
				//check legal moves for piece
				for (Board::iterator j = board.begin(); j != board.end(); ++j){
					Position end_position = *j;
					//check if the piece moving or capturing another piece puts it in check
					if (piece -> legal_capture_shape(start_position, end_position) || piece->legal_move_shape(start_position, end_position)){
						//check if move gets the king out of check by calling in_check
						try{
							Game temp_game(*this);
							temp_game.board.move_piece(start_position, end_position); //trying the move on the temp board
							//check if the move will take the king out of check
							if (!temp_game.in_check(white)){
								return false; //move successfully took king out of check
							}
						}
						//move_piece will raise exceptions if the move fails so this will catch it to just continue to
						//the next position
						catch(const Exception &e){
							continue;
						}
					}
				}
			}
		}
		return true; //if no move will keep the king out of check, player is in a stalemate
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
		//initializing total points
		int point_value = 0;

		//Iterating through the whole board
		for (Board::iterator it = board.begin(); it != board.end(); ++it){
			const Piece* piece = board(*it);//finding the piece at the current position on the board
						
			//checking that the piece is the right color and that it exists
			if(piece && piece->is_white() == white) {
				//checking which piece it is to add the correct value to the point value
				//adding 1 point for pawn 
				if(tolower(piece->to_ascii()) == 'p') {
					point_value += 1;
				}
				//adding 3 points for knight
				if(tolower(piece->to_ascii()) == 'n') {
					point_value += 3;
				}
				//adding 3 points for bishop
				if(tolower(piece->to_ascii()) == 'b') {
					point_value += 3;
				}
				//adding 5 points for rook
				if(tolower(piece->to_ascii()) == 'r') {
					point_value += 5;
				}
				//adding 9 points for queen
				if(tolower(piece->to_ascii()) == 'q') {
					point_value += 9;
				}
				if(tolower(piece->to_ascii()) == 'm') {
					point_value += dynamic_cast<const Mystery *>(piece)->point_value();
				}
			}
		}
		//returning total number of points for a side
		return point_value;
    }


    std::istream& operator>> (std::istream& is, Game& game) {
		//initialize variables
		std::string line;
		char piece;
		char player;

		game.board.clear_board(); //clears default board state

		//read in board state
		for (int row = 8; row > 0; --row) {
			std::getline(is, line);
			std::stringstream ss(line);

			for (char col = 'A'; col <= 'H'; ++col){
				ss >> piece;
				if (piece != '-') { //if not empty square, then piece is there
					Position position(col, '1' + (row - 1));
					game.board.add_piece(position, piece);
				}
			}
		}

		is >> player;
		game.is_white_turn = (player == 'w'); //figures out whose turn
		return is;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
