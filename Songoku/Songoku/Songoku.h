#pragma once
#include "MainObject.h"
#include "Monster.h"
#include "Warning.h"
#include "Boss.h"

#define WIDTH_SONGOKU 90
#define HEIGHT_SONGOKU 125
#define SPEED_SONGOKU 900

class Songoku :
  public MainObject
{
public:
  Songoku();
  ~Songoku();
  void Update(SDL_Surface* g_screen, Effect* &effect, vector<HandleEffect*>& list_effect, int check_war);
  void handleMove(const int& width, const int& height, SDL_Surface* des);
  void handleInput(SDL_Event event);
  void display(SDL_Surface* des,vector<Monster*>& list_monster, Effect* &effect, vector<HandleEffect*>& list_effect);
  void initVideo();
  void clearVideo();

  void setTypeGoku(const int& type) { type_goku_ = type; }
  int getTypeGoku() const { return type_goku_; }


private:
  enum TypeGoku {
    Goku,
    SuperGoku1,
    SuperGoku2,
  };
  Mix_Chunk* sound_kameha;
  Mix_Chunk* sound_red;
  int check_time_;
  int check_change_;
  int check_kameha_;
  int index_key_event_;
  int type_goku_;

  vector<SDL_Surface*> FlySaiyan_;
  vector<SDL_Surface*> FlyRightSaiyan_;
  vector<SDL_Surface*> FlyLeftSaiyan_;
  SDL_Surface* FlyUpSaiyan_;
  SDL_Surface* FlyDownSaiyan_;
  vector<SDL_Surface*> ButtunLeftSaiyan_;
  vector<SDL_Surface*> KamehaSaiyan_;
 
  vector<SDL_Surface*> Change_;
  vector<SDL_Surface*> Kameha_;
  vector<SDL_Surface*> war_;
  vector<SDL_Surface*> boss_;
};

