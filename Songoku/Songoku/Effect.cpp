#include "Effect.h"



Effect::Effect()
{

  background_ = NULL;
}


Effect::~Effect()
{
}

void Effect::initEffect()
{
  SDL_Surface* temp = new SDL_Surface();
  temp = PublicFunction::LoadImage("bomb1.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb2.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb3.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb4.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb5.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb6.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb7.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb8.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb9.png");
  bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("bomb10.png");
  bomb_.push_back(temp);


  temp = PublicFunction::LoadImage("Effect_blu1.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu1.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu2.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu2.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu3.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu3.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu4.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu4.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu5.png");
  effect_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("Effect_blu5.png");
  effect_blu_.push_back(temp);


  temp = PublicFunction::LoadImage("DragonDead1.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead2.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead3.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead4.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead5.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead6.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead7.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead8.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead9.png");
  big_bomb_.push_back(temp);
  temp = PublicFunction::LoadImage("DragonDead10.png");
  big_bomb_.push_back(temp);

  temp = PublicFunction::LoadImage("BombBlu1.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu2.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu3.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu4.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu5.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu6.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu7.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu8.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu9.png");
  bomb_blu_.push_back(temp);
  temp = PublicFunction::LoadImage("BombBlu10.png");
  bomb_blu_.push_back(temp);

}