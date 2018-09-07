
#include "BaseObject.h"

BaseObject::~BaseObject()
{

}

/*
* Input :: Surface Đích
* Output:: dán cái backgroud lên surface Đích
*/
void BaseObject::show(SDL_Surface * des)
{
  if (background_ != NULL) {
    PublicFunction::ApplySurface(background_, des, goor_.x, goor_.y);
  }
}


/*
* Input : Tên ảnh
* Output : True(load thành công) false (load không thành công)
*/
bool BaseObject::loadImage(std::string file_path)
{
  background_ = PublicFunction::LoadImage(file_path);
  if (background_ == NULL) {
    return false;
  }
  return true;
}