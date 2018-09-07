#include "MainObject.h"



MainObject::MainObject()
{
  x_val_ = 0;
  y_val_ = 0;
  goor_.x = 0;
  goor_.y = 0;
  
  status_main_ = idle;
  HP_main_ = HP_MAIN;
  Mana_main_ = MANA_MAIN;
  Power_main_ = POWER_MAIN;
  background_ = NULL;
}


MainObject::~MainObject()
{

}





