#pragma once
#include "BaseObject.h"

#define SPEED_WARNING 2000
#define HP_WARNING 400
class Warning : public BaseObject
{
public:
  Warning();
  ~Warning();

  void setX_Val(const int& x) { x_val_ = x; }
  void setY_Val(const int& y) { y_val_ = y; }
  int getX_Val() const { return x_val_; }
  int getY_Val() const { return y_val_; }

  void setIsMove(const bool& is_move) { is_move_ = is_move; }
  bool getIsMove() const { return is_move_; }

  void setHP(const int& hp) { hp_ = hp; }
  int getHP() const { return hp_;}

  void setStatus(const int& stt) { status_warning_ = stt; }
  int getStatus() const { status_warning_; }

  void handleMove(const int &width, const int& height);

  void setSpeed(const int& speed) { speed_ = speed; }
  int getSpeed() const { return speed_; }

  void setWarning(const vector<SDL_Surface*> warning) {warning_ = warning;}
  vector<SDL_Surface*> getWarning() const { return warning_; }

private:
  int index;
  int x_val_;
  int y_val_;
  int speed_;
  bool is_move_;
  int hp_;
  int status_warning_;

  vector<SDL_Surface*> warning_;
};

