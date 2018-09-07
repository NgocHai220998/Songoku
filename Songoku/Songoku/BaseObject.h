#pragma once
//#ifndef BASE_OBJECT_
//#define BASE_OBJECT_
#include <vector>
#include "PublicFunction.h"


#define WIDTH_MAIN 90
#define HEIGHT_MAIN 110


class BaseObject
{
public:
  BaseObject() { goor_.x = 0; goor_.y = 0; background_ = NULL; }
  ~BaseObject();
  void show(SDL_Surface *des);
  bool loadImage(std::string file_path);
  void setGoor(const int& x, const int& y) { goor_.x = x; goor_.y = y; }
  SDL_Rect getGoor() const { return goor_; }
  SDL_Surface* getBackground() const { return background_; };
  void setBackground(SDL_Surface* bk) { background_ = bk; }

protected:
  SDL_Rect goor_;
  SDL_Surface *background_;
};




//#endif // !BASE_OBJECT_



