#pragma once
#include "BaseObject.h"

#define HP_RED 70
#define HP_BLU 100
#define HP_FIRE 120
#define SPEED_RED 2500
#define SPEED_BLU 1000 
#define SPEED_FIRE 3000
#define WIDTH_BULLET 30
#define HEIGHT_BULLET 30

enum TypeBullet {
  red = 1,
  blu = 2,
  fire = 3,

};
class Bullet : public BaseObject
{
public:
  Bullet();
  ~Bullet();
  inline void setX_Val(const int& x, const double& time_speed) { x_val_ = x*time_speed; }
  inline void setY_Val(const int& y, const double& time_speed) { y_val_ = y* time_speed; }
  int getX_Val() const { return x_val_; }
  int getY_Val() const { return y_val_; }

  void setIsMove(const bool& is_move) { is_move_ = is_move; }
  bool getIsMove() const { return is_move_; }

  void setHP(const int& hp) { HP_ = hp; }
  int getHP() const { return HP_; }

  void setTypeBullet(const int& type);
  int getTypeBullet() const { return type_bullet_; }

  void handleMove(const int & width, const int & height);


private:
  int HP_;
  int type_bullet_;
  bool is_move_;
  int x_val_;
  int y_val_;
};

