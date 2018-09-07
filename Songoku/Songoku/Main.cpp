#include <iostream>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include "PublicFunction.h"
#include "MainObject.h"
#include "Songoku.h"
#include "Monster.h"
#include "Effect.h"
#include "HandleEffect.h"
#include "Warning.h"
#include "Menu.h"

const int g_FPS = 20;

using namespace std;

vector<SDL_Surface*> InitVideoBackground();

void initAndDisplayMonster(vector<Monster*>& list_monster, const double& time_while, MainObject* &p_main);
void displayEffect(vector<HandleEffect*> &list_effect);
int menu(Menu* &p_menu);

#undef main
int main(int argc, char* argv[])
{
  

  bool is_quit = false;
  if (PublicFunction::Init() == false) {
    return 1;
  }

  Menu* p_menu = new Menu();
  p_menu->initVideo();
  int game = menu(p_menu);
  if (game == 2) {
    return 0;
  }


  vector<SDL_Surface*> video_background = InitVideoBackground();
  PublicFunction::ApplySurface(g_bkground, g_screen, 0, 0);

  Effect* effect = new Effect();
  effect->initEffect();
  vector<HandleEffect*> list_effect;


  MainObject* p_main = new Songoku();
  p_main->initVideo();
  p_main->setGoor(300, 300);

  vector<Monster*> list_monster;
  
  int FPS = 0;
  clock_t t = 0;
  //clock_t t1 = 0;
  double time_while = 0;
  static int check_war = 0;
  int x = 0;
  int y = 0;

  while (!is_quit)
  {
    FPS++;
    t = clock();
    //t1 = t;
    while (SDL_PollEvent(&g_even))
    {
      if (g_even.type == SDL_QUIT)
      {
        is_quit = true;
        break;
      }
      p_main->handleInput(g_even);

    }
    p_main->setTimeRunGame(time_while);
    
    static int index_of_background = 0;
    if (index_of_background % (16 * 50) == 0) {
      Mix_PlayChannel(-1, g_sound_all, 0); // chạy nhạc nền 
    }

    g_bkground = video_background.at(index_of_background++ % 9);
    PublicFunction::ApplySurface(g_bkground, g_screen,x,y);


    p_main->Update(g_screen, effect, list_effect,check_war);
    p_main->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT, g_screen);
    p_main->display(g_screen,list_monster,effect,list_effect);

    
    displayEffect(list_effect);
    initAndDisplayMonster(list_monster, time_while,p_main);
    check_war++;
    if (check_war % 3500 > 2000) {
      x = rand() % 10;
      y = rand() % 10;
    }
    else {
      x = 0;
      y = 0;
    }
    if (SDL_Flip(g_screen) == -1 || p_main->getHP() < 300) {
      static int dem = 0;
        while (true) {
          static SDL_Surface* dead = PublicFunction::LoadImage("OverGame.png");
          PublicFunction::ApplySurface(dead, g_screen, 0, 0);
          SDL_Flip(g_screen);
          dem++;
          if (dem == 500) {
            return 0;
          }
        }
      //break;
    }
    t = clock() - t; // Tính thời gian 1 vòng for chạy
    if (t < g_FPS) {
      SDL_Delay(g_FPS - t);
    }
    //t1 = clock() - t1;
    //cout << 1000 / t1 << endl;
    time_while = (double)g_FPS / CLOCKS_PER_SEC;
  }
  std::cout << FPS << endl;
  system("pause");
  PublicFunction::CleanUp();
  p_main->clearVideo();
  if (p_main != NULL) {
    delete p_main;
    p_main = NULL;
  }
  return 0;
}






int menu(Menu* &p_menu)
{
  bool is_quit = false;
  int exit;
  while (!is_quit)
  {
    while (SDL_PollEvent(&g_even))
    {
      if (g_even.type == SDL_QUIT)
      {
        is_quit = true;
        break;
      }
    }
    exit = p_menu->isGame(g_even, g_screen);
    if (exit != 3) {
      break;
    }
    if (SDL_Flip(g_screen) == -1) {
      return 0;
    }
  }
  return exit;
}




















bool PublicFunction::Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return false;
  }
  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  SDL_WM_SetCaption("Songoku", NULL);
  SDL_WM_SetIcon(SDL_LoadBMP("IconGoku.bmp"), NULL);
  if (g_screen == NULL)
  {
    return false;
  }

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
  {
    return false;
  }
  g_sound_all = Mix_LoadWAV("NhacNen.wav");
  //g_sound_skill = Mix_LoadWAV("skill2019.wav");
  if (g_sound_all == NULL) {
    return false;
  }
  return true;
}
vector<SDL_Surface*> InitVideoBackground()
{
  vector<SDL_Surface*> video;
  SDL_Surface* temp = new SDL_Surface;
  temp = PublicFunction::LoadImage("background1.png");
  video.push_back(temp);
  temp = PublicFunction::LoadImage("background2.png");
  video.push_back(temp);
  temp = PublicFunction::LoadImage("background3.png");
  video.push_back(temp);
  temp = PublicFunction::LoadImage("background4.png");
  video.push_back(temp);
  temp = PublicFunction::LoadImage("background5.png");
  video.push_back(temp);
  temp = PublicFunction::LoadImage("background6.png");
  video.push_back(temp);
  temp = PublicFunction::LoadImage("background7.png");
  video.push_back(temp);
  temp = PublicFunction::LoadImage("background8.png");
  video.push_back(temp);
  temp = PublicFunction::LoadImage("background9.png");
  video.push_back(temp);

  return video;
}


void initAndDisplayMonster(vector<Monster*>& list_monster, const double& time_while, MainObject* &p_main)
{
  static SDL_Surface* background_monster = PublicFunction::LoadImage("Monster.png");
  static int monster = 0;
  monster = rand() % 70;
  if (monster == 35) {
    Monster* p_monster = new Monster;
    p_monster->setBackground(background_monster);
    p_monster->setGoor(SCREEN_WIDTH + rand() % 200, 100 + rand() % (SCREEN_HEIGHT - 200));
    p_monster->setIsMove(true);
    list_monster.push_back(p_monster);
  }
  for (int i = 0; i < list_monster.size(); ++i) {
    Monster* p_monster = list_monster.at(i);
    if (p_monster != NULL) {
      if (p_monster->getIsMove() == true && p_monster->getHP() > 0) {
        p_monster->setX_Val(p_monster->getSpeed(), time_while);
        p_monster->show(g_screen);
        p_monster->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
      }
      else {
        if (p_monster->getGoor().x <= 0) {
          p_main->setHP(p_main->getHP() - 200);
        }
        //SDL_FreeSurface(list_monster.at(i)->getBackground());
        list_monster.erase(list_monster.begin() + i);
        p_monster = NULL;
      }
    }
  }
}

void displayEffect(vector<HandleEffect*>& list_effect)
{
  for (int i = 0; i < list_effect.size(); ++i) {
    HandleEffect* p_effect = list_effect.at(i);
    if (p_effect->getIsEffect() == true && p_effect != NULL) {
      p_effect->displayEffect();
      p_effect->show(g_screen);
    }
    else {
      list_effect.erase(list_effect.begin() + i);
      p_effect = NULL;
    }
  }
}

