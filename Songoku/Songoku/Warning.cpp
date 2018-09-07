#include "Warning.h"



Warning::Warning()
{
  is_move_ = false;
  speed_ = SPEED_WARNING;
  hp_ = HP_WARNING;
  index = 0;
}


Warning::~Warning()
{
}


void Warning::handleMove(const int & width, const int & height)
{

  background_ = warning_.at(index % 2);
  if (index > 150) {
    goor_.x -= x_val_;
    background_ = warning_.at(2);
  }
  index++;
  if (goor_.x < -50) {
    is_move_ = false;
  }
}