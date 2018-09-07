#include "PublicFunction.h"


SDL_Surface* PublicFunction::LoadImage(std::string file_path)
{
  SDL_Surface * load_image = NULL;
  SDL_Surface* optimize_image = NULL;
  load_image = IMG_Load(file_path.c_str());
  if (load_image != NULL)
  {
    optimize_image = SDL_DisplayFormat(load_image);
    SDL_FreeSurface(load_image);

    if (optimize_image != NULL)
    {
      UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0x80, 0);
      SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
    }
  }
  return optimize_image;
}

void PublicFunction::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);
}


void PublicFunction::CleanUp()
{
  SDL_FreeSurface(g_screen);
  SDL_FreeSurface(g_bkground);
}

/*
* Input : số liệu hai hình chữ nhật cần xét va chạm (Kiểu dữ liệu SDL_Rect)
* Output : trả về true (2 thành phần va chạm) trả về false (ngược lại)
*/


bool PublicFunction::checkCollision(SDL_Rect  Goor_T, SDL_Rect  Goor_Y)
{


  //#define Goor_T Goor_T->getGoor()
  //#define Goor_Y Goor_Y->getGoor()

  ///////
  if (Goor_T.x + Goor_T.w >= Goor_Y.x && Goor_T.x + Goor_T.w <= Goor_Y.x + Goor_Y.w && Goor_T.y + Goor_T.h >= Goor_Y.y && Goor_T.y + Goor_T.h <= Goor_Y.y + Goor_Y.h) {
    return true;
  }
  if (Goor_T.x + Goor_T.w >= Goor_Y.x && Goor_T.x + Goor_T.w <= Goor_Y.x + Goor_Y.w && Goor_T.y >= Goor_Y.y && Goor_T.y <= Goor_Y.y + Goor_Y.h) {
    return true;
  }
  if (Goor_T.x >= Goor_Y.x && Goor_T.x <= Goor_Y.x + Goor_Y.w && Goor_T.y + Goor_T.h >= Goor_Y.y && Goor_T.y + Goor_T.h <= Goor_Y.y + Goor_Y.h) {
    return true;
  }
  if (Goor_T.x >= Goor_Y.x && Goor_T.x <= Goor_Y.x + Goor_Y.w && Goor_T.y >= Goor_Y.y && Goor_T.y <= Goor_Y.y + Goor_Y.h) {
    return true;
  }
  return false;
}
