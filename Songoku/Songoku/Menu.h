#pragma once
#include "PublicFunction.h"

class Menu
{
public:
  Menu();
  ~Menu();
  void initVideo();
  void clearVideo();
  int isGame(SDL_Event event, SDL_Surface* g_screen);


private:
  vector<SDL_Surface*> bk_;
  SDL_Rect Start;
  SDL_Rect Exit;


};

