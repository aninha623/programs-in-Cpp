//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

using std::cout;
using std::endl;

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  const Piece* Board::operator()(const Position& position) const {
    std::map<Position, Piece*>::const_iterator it = occ.find(position);

    if (it != occ.end()) {
      return it -> second; //returns the piece at that position
    }

    return NULL; //if no piece found
  }
  
  void Board::add_piece(const Position& position, const char& piece_designator) {
    //checks if position is in bounds, throws exception if not
    if (position.first < 'A' || position.first > 'H' || position.second < '1' || position.second > '8') {
      throw Exception("invalid position");
    } 
    //checks if position in occupied, throws exception if is
    if (occ.find(position) != occ.end()) {
      throw Exception("position is occupied");
    }

    Piece* new_piece = create_piece(piece_designator);
    if (!new_piece) { //checking if piece_designator exists
        delete new_piece;
        throw Exception("invalid designator");
    }

    //add the piece to the map
    occ[position] = new_piece;
  }

  //displaying the chess board for users
  void Board::display() const {
    
    //creating the row and columns to iterate through
    char row;
    char col;

    //going through the rows from 8 to 1
    for(row = '8'; row >= '1'; row--) {
      //going through the columns a to h
      cout << endl;
      cout << "   "; //for alignment
      //prints column headers from A to H
      for (col = 'A'; col <= 'H'; ++col) {
        cout << col << "  ";
      }
      cout << endl;
      for(row = '8'; row >= '1'; row--) {
        cout << row << " "; //prints row numbers
        for(col = 'A'; col <= 'H'; col++) {
          //making a position based on the row and col it is on
          Position position(col, row);

          //pointer to the piece I that is in the position I am on
          const Piece* piece = (*this)(position);

          //checking that a piece exists on the position
          bool is_pink = ((col - 'A') + (row - '1')) % 2 == 0; //checks whether or not to make square pink
          if (is_pink) {
            Terminal::color_bg(Terminal::MAGENTA);
          }
          else {
            Terminal::color_bg(Terminal::BLACK);
          }

          if(piece) {
            //conveting piece to char and printing it
            cout << " " << piece->to_unicode();
          }
          else {
            //putting a dash when there is no piece
            cout << " " << '-';
          }
          //each peice has a space in between
          cout << ' ';
          Terminal::set_default();
        }
        //moving through the rows
        cout << endl;
      }
    }
  }

  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;

		//iterate over board to find position of king
		for (Board::iterator it = this->begin(); it != this->end(); ++it){
			const Piece* piece = (*this)((*it)); //store this temporary king as king
			//if the piece on the board at the iterator's position is K, king is found
			if (piece){
        if (piece->to_ascii() == 'K'){
          white_king_count += 1;
        }
        else if (piece->to_ascii() == 'k'){
          black_king_count += 1;
        }
        else{
          continue;
        }
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	const Piece* piece = board(Position(c, r));
	if (piece) {
	  os << piece->to_ascii();
	} else {
	  os << '-';
	}
      }
      os << std::endl;
    }
    return os;
  }

  void Board::move_piece(const Position& start, const Position& end) {
    Piece* piece_move = occ[start];
    const Piece* end_loc = occ[end];

    //check if legal
    if (end_loc && (end_loc -> is_white() == piece_move -> is_white())) { //checking if capture own piece
      throw Exception("cannot capture own piece"); 
    }
    if (end_loc) { //for capturing
      if (!piece_move->legal_capture_shape(start, end)) { //checking if shape of capture is legal 
        throw Exception("illegal capture shape");
      }
      if (occ[end]){ //if there is a piece already at the end, Purge it. because its capturing
        delete occ[end];
        occ[end] = nullptr;
      }
    }
    else { //for moving
      if (!(piece_move->legal_move_shape(start, end))) {
        throw Exception("illegal move shape");
      }
    }

    
    //checking if path is clear
    bool needs_clear = false;
    char piece_type = tolower(piece_move->to_ascii());
    
  
    switch (piece_type) {
      case 'r': case 'q': case 'b': case 'p': 
        needs_clear = true; //rook, queen, bishop, pawn
        break;
      case 'n': 
        needs_clear = false; //knight never needs
        break;
      case 'm':  //for mystery
        //if move is L shape vs. straight/diagonal
        if (abs(start.first - end.first) == abs(start.second - end.second) || start.first == end.first || start.second == end.second) {
          needs_clear = true;
        }
        else {
          needs_clear = false; //any non-straight path
        }
        break;
    }

    if (needs_clear && !path_is_clear(start, end)) {
      throw Exception("path is not clear");
    }


    if (end_loc) { //for capturing
      if (!piece_move->legal_capture_shape(start, end)) { //checking if shape of capture is legal 
        throw Exception("illegal capture shape");
      }
    }
    else { //for moving
      if (!(piece_move->legal_move_shape(start, end))) {
        throw Exception("illegal move shape");
      }
    }

    occ[end] = piece_move; //move to new position
    occ.erase(start); //erase from start position
    
    
    if (end_loc) { //for capturing
      if (!piece_move->legal_capture_shape(start, end)) { //checking if shape of capture is legal 
        throw Exception("illegal capture shape");
      }
    }
    else { //for moving
      if (!(piece_move->legal_move_shape(start, end))) {
        throw Exception("illegal move shape");
      }
    }
    
    //promotion logic
    if (tolower(piece_type) == 'p') {
      occ[end] = piece_move; //move to new position
      occ.erase(start); //erase from start position
      if (piece_move->is_white() && end.second == '8') {
        delete occ[end]; //remove pawn
        occ[end] = create_piece('Q'); //promote to queen
      }
      else if (!piece_move->is_white() && end.second == '1') {
        delete occ[end]; //remove pawn
        occ[end] = create_piece('q'); //promote to queen
      }
    }
  }

  bool Board::path_is_clear(const Position& start, const Position& end) const {
    char column_start = start.first;
		char row_start = start.second;
		char column_end = end.first;
		char row_end = end.second;

    int column_step = 0; //no change, don't have to increment/decrement
    if (column_end > column_start) {
      column_step = 1; //moving to the right
    }
    else if (column_start > column_end) {
      column_step = -1; //moving to the left
    }

    int row_step = 0; //no change, don't have to increment/decrement
    if (row_end > row_start) {
      row_step = 1; //moving up
    }
    else if (row_start > row_end) {
      row_step = -1; //moving down
    }

    int column = column_start + column_step;
    int row = row_start + row_step;
    while (column != column_end || row != row_end) {
      Position curr(column, row);

      if (occ.find(curr) != occ.end()) {
        return false; //found piece in the way
      }
      column += column_step;
      row += row_step;
    }
    return true; //nothing in path!
  }
}
