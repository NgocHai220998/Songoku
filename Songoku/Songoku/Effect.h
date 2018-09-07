#pragma once
#include "BaseObject.h"


class Effect : public BaseObject
{
public:
  Effect();
  ~Effect();
  void initEffect();

  vector<SDL_Surface*> getBomb() const { return bomb_; }
  vector<SDL_Surface*> getEffectBlu() const { return effect_blu_; }
  vector<SDL_Surface*> getBigBomb() const { return big_bomb_; }
  vector<SDL_Surface*> getBombBlu() const { return bomb_blu_; }
private:
  vector<SDL_Surface*> bomb_;
  vector<SDL_Surface*> effect_blu_;
  vector<SDL_Surface*> big_bomb_;
  vector<SDL_Surface*> bomb_blu_;

};

