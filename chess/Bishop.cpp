//anna andrade aandra12
//mirabel luo mluo12
//sophie noureddine snoured1

#include "Bishop.h"

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    
    //seeing if bishop didnt move then return false
    if(start == end) {
      return false;
    }

    //initizalizing the horizontal and veritcal positions
    int horizontal = abs(start.first - end.first);
    int vertical = abs(start.second - end.second);

    //if bishop moves diagonally return true
    if(horizontal == vertical) {
      return true;
    }

    //if not diagonal return false
    return false;
  }
}
