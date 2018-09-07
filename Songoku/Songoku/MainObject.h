#pragma once
#include "BaseObject.h"
#include "Bullet.h"
#include "Monster.h"
#include "Effect.h"
#include "HandleEffect.h"
#define HP_MAIN 5000
#define MANA_MAIN 1000
#define POWER_MAIN 1000



class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  void setX_Val(const int& x, const double &time_speed) { x_val_ = x*time_speed; }
  void setY_Val(const int& y, const double &time_speed) { y_val_ = y*time_speed; }

  int getX_Val() const { return x_val_; }
  int getY_Val() const { return y_val_; }
  void setHP(const int& hp) { HP_main_ = hp;}
  int getHP() const { return HP_main_; }

  void setMana(const int& Mana) { Mana_main_ = Mana; }
  int getMana() const { return Mana_main_; }

  void setPower(const int& Power) { Power_main_ = Power; }
  int getPower() const { return Power_main_; }

  int getMove() const { return status_main_; }
  void setMove(const int& status_main) { status_main_ = status_main; }

  void setSpeed(const int &speed) { speed_ = speed; }
  int getSpeed() const { return speed_; }

  void setTimeRunGame(const double &time_run) { time_run_game_ = time_run; }
  double getTimeRunGame() const { return time_run_game_; }

  

  virtual void Update(SDL_Surface* g_screen, Effect* &effect, vector<HandleEffect*>& list_effect, int check_war) = 0;
  virtual void handleMove(const int& width, const int& height, SDL_Surface* des) = 0;
  virtual void handleInput(SDL_Event event) = 0;
  virtual void display(SDL_Surface* des,vector<Monster*> &list_monster,Effect* &effect , vector<HandleEffect*>& list_effect) = 0;
  virtual void initVideo() = 0;
  virtual void clearVideo() = 0;
  virtual vector<Bullet*> getListBullet() const { return list_bullet_; }
  virtual void setListBullet(vector<Bullet*> list) { list_bullet_ = list; }

protected:
  enum Status_Main {
    idle = 1,
    right,
    left,
    down,
    up,
    flash,
    attack_normal,
    attack_skill_1,
    attack_skill_2,
    attack_ultimate,
    change,
    injuries,
    dead,
    normal,
    skill_1,
    skill_2,
    ultimate,
  };
  int speed_;
  int status_main_;
  int x_val_;
  int y_val_;
  int HP_main_;
  int Mana_main_;
  int Power_main_;
  int check_time_event_;
  double time_run_game_;
  vector<char> key_event_;

  vector<SDL_Surface*> idle_;
  vector<SDL_Surface*> right_;
  vector<SDL_Surface*> left_;
  vector<SDL_Surface*> normal_;
  vector<Bullet*> list_bullet_;
  SDL_Surface* up_;
  SDL_Surface* down_;
  
};

