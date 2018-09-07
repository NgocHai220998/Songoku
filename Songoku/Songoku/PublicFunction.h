#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;


static SDL_Surface *g_screen = NULL; // Quan ly cai man hinh
static SDL_Surface *g_bkground = NULL; // cai buc anh cua minh
static SDL_Event g_even; // Quan ly su kien

static Mix_Chunk* g_sound_all;
//static Mix_Chunk* g_sound_skill;

namespace PublicFunction
{
  bool Init();
  SDL_Surface* LoadImage(std::string file_path);
  // dau vao la 1 anh va dich den cua anh? day
  void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
  void CleanUp();
  bool checkCollision(SDL_Rect Goor_T, SDL_Rect Goor_Y);

}