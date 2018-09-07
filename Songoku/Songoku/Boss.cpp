#include "Boss.h"



Boss::Boss()
{
  x_val_ = 0;
  y_val_ = 0;
  goor_.w = WIDTH_BOSS;
  goor_.h = HEIGHT_BOSS;
  hp_ = HP_BOSS;
  is_move_ = true;
  index = 0;
  display_hp_ = false;
}


Boss::~Boss()
{

}


void Boss::handleMove(const int & width, const int & height, SDL_Surface* g_screen)
{
  static SDL_Surface* hp = PublicFunction::LoadImage("HP.png");
  if (display_hp_ == true) {
    for (int i = 0; i < hp_ / 85 ; ++i) {
      PublicFunction::ApplySurface(hp, g_screen, goor_.x + i*10, goor_.y + 10);
    }
    display_hp_ = false;
  }

  if (goor_.x > - 300 ) {
    goor_.x -= x_val_;
  }
  else {
    is_move_ = false;
  }
  if (status_boss_ == 0) {
    background_ = boss_.at(index / 9);
    index++;
    if (index == (boss_.size() - 1) * 9) {
      index = 0;
    }
  }
  if (status_boss_ == 1) {
    background_ = boss_.at(3);
    static int check = 0;
    check++;
    if (check == 10) {
      status_boss_ = 0;
      check = 0;
    }
  }
}
