#include "Bullet.h"



Bullet::Bullet()
{
  type_bullet_ = red;
  x_val_ = 0;
  y_val_ = 0;
  is_move_ = false;
  HP_ = HP_RED;
  goor_.w = WIDTH_BULLET;
  goor_.h = HEIGHT_BULLET;
}


Bullet::~Bullet()
{
}

void Bullet::handleMove(const int & width, const int & height)
{
  goor_.x += x_val_;
  goor_.y += y_val_;
  if (goor_.x < 0 || goor_.x > width + 50 || goor_.y < 0 || goor_.y > height + 50) {
    is_move_ = false;
  }
}

void Bullet::setTypeBullet(const int & type)
{
  type_bullet_ = type;
  static SDL_Surface* bullet_red_ = PublicFunction::LoadImage("Bullet_red.png");
  static SDL_Surface* bullet_blu_ = PublicFunction::LoadImage("Bullet_blu.png");
  static SDL_Surface* bullet_fire_ = PublicFunction::LoadImage("SkillSaiyan.png");
  if (type_bullet_ == red) {
    background_ = bullet_red_;
    HP_ = HP_RED;
  }
  if (type_bullet_ == blu) {
    HP_ = HP_BLU;
    background_ = bullet_blu_;
  }
  if (type_bullet_ == fire) {
    HP_ = HP_FIRE;
    background_ = bullet_fire_;
  }
}
