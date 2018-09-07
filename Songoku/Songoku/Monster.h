#pragma once
#include "BaseObject.h"

#define SPEED_MONSTER 250
#define HP_MONSTER 100
#define WIDTH_MONSTER 100
#define HEIGHT_MONSTER 50


class Monster : public BaseObject
{
public:
  Monster();
  ~Monster();

  inline void setX_Val(const int& x, const double& time_speed) { x_val_ = x * time_speed; }
  inline void setY_Val(const int& y, const double& time_speed) { y_val_ = y * time_speed; }
  int getX_Val() const { return x_val_; }
  int getY_Val() const { return y_val_; }

  void setSpeed(const int& speed) { speed_monster_ = speed; }
  int getSpeed() const { return speed_monster_; }

  void setHP(const int& hp) { hp_monster_ = hp; }
  int getHP() const { return hp_monster_; }

  void setIsMove(const bool& is_move) { is_move_ = is_move; }
  bool getIsMove() const { return is_move_; }

  void handleMove(const int &width,const int& height);

  void setTypeMonster(const int& type) { type_monster_ = type; }
  int getTypeMonster() const { return type_monster_; }

private:
  int speed_monster_;
  int hp_monster_;
  bool is_move_;
  int type_monster_;
  enum TypeMonster {
    Normal,
    Dead,
    Bomb,
  };
  int x_val_;
  int y_val_;

};


