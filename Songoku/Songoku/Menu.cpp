#include "Menu.h"



Menu::Menu()
{
  Start.x = 1152;
  Start.y = 147;
  Start.w = 1400 - 1152;
  Start.h = 332 - 147;
  
  Exit.x = 1152;
  Exit.y = 342;
  Exit.w = 1400 - 1152;
  Exit.h = 535 - 342;
}


Menu::~Menu()
{
}

int Menu::isGame(SDL_Event event,SDL_Surface* g_screen)
{
  static int index = 0;
  PublicFunction::ApplySurface(bk_.at(index++ % 12), g_screen, 0, 0);
  static SDL_Rect Goor;
  if (event.type == SDL_MOUSEMOTION) { //
    cout << event.motion.x << " " << event.motion.y << endl;
  }

  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      Goor.x = event.button.x;
      Goor.y = event.button.y;
      Goor.w = 0;
      Goor.h = 0;
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      //Todo
    }
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      //Todo
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      //Todo
    }
  }

  cout << Goor.x << endl;

  if (PublicFunction::checkCollision(Goor, Start) == true) {

    return 1;
  }
  if (PublicFunction::checkCollision(Goor, Exit) == true) {
    return 2;
  }
  return 3;
}

void Menu::initVideo()
{
  SDL_Surface* temp = new SDL_Surface();
  temp = PublicFunction::LoadImage("Menu1.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu2.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu3.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu4.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu5.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu6.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu7.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu8.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu9.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu10.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu11.png");
  bk_.push_back(temp);
  temp = PublicFunction::LoadImage("Menu12.png");
  bk_.push_back(temp);
}

void Menu::clearVideo()
{
  for (int i = 0; i < bk_.size(); ++i) {
    if (bk_.at(i) != NULL) {
      SDL_FreeSurface(bk_.at(i));
      bk_.at(i) = NULL;
    }
  }
  bk_.clear();
}