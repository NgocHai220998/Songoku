#pragma once
#include "BaseObject.h"
#include "Bullet.h"
#define HP_BOSS 2000
#define WIDTH_BOSS 250
#define HEIGHT_BOSS 180

class Boss : public BaseObject
{
public:
  Boss();
  ~Boss();

  void setX_Val(const int& x) { x_val_ = x; }
  void setY_Val(const int& y) { y_val_ = y; }
  int getX_Val() const { return x_val_; }
  int getY_Val() const { return y_val_; }

  void setIsMove(const bool& is_move) { is_move_ = is_move; }
  bool getIsMove() const { return is_move_; }

  void setHP(const int& hp) { hp_ = hp; }
  int getHP() const { return hp_; }

  void setStatus(const int& stt) { status_boss_ = stt; }
  int getStatus() const { status_boss_; }

  void handleMove(const int &width, const int& height, SDL_Surface* g_screen);
  void setBoss(vector<SDL_Surface*> boss) { boss_ = boss; }

  vector<Bullet*> getListBullet() const { return list_bullet_; }
  void setListBullet(vector<Bullet*> list) { list_bullet_ = list; }

  void setDisplayHP(const bool& is) { display_hp_ = is; }
  bool getDisplayHP() const { return display_hp_; }

private:
  bool display_hp_;
  int x_val_;
  int y_val_;
  bool is_move_;
  int status_boss_;
  int hp_;
  int index;

  vector<SDL_Surface*> boss_;
  vector<Bullet*> list_bullet_;
};

