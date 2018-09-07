#include "Monster.h"



Monster::Monster()
{
  x_val_ = 0;
  y_val_ = 0;
  speed_monster_ = SPEED_MONSTER;
  background_ = NULL;
  type_monster_ = Normal;
  goor_.h = HEIGHT_MONSTER;
  goor_.w = WIDTH_MONSTER;
  hp_monster_ = HP_MONSTER;
}


Monster::~Monster()
{
}





void Monster::handleMove(const int & width, const int & height)
{

  if (type_monster_ == Normal) {
    goor_.x -= x_val_;
    goor_.y += y_val_;
  }





  if (goor_.x < -50) {
    is_move_ = false;
  }
  //Todo
}