#pragma once
#include "BaseObject.h"
class HandleEffect : public BaseObject
{
public:
  HandleEffect();
  ~HandleEffect();
  vector<SDL_Surface*> getEffect() const { return effect_; }
  void setEffect(vector<SDL_Surface*> effect) { effect_ = effect; }


  void displayEffect();
  void setIsEffect(const bool &effect) { is_effect_ = effect; }
  bool getIsEffect() const { return is_effect_; }


private:
  int check_effect_;
  bool is_effect_;
  vector<SDL_Surface*> effect_;
};

