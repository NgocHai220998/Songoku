#include "HandleEffect.h"



HandleEffect::HandleEffect()
{
  is_effect_ = true;
  check_effect_ = 0;
}


HandleEffect::~HandleEffect()
{
}

void HandleEffect::displayEffect()
{
  if (is_effect_ == true) {
    background_ = effect_.at(check_effect_ / 1);
    check_effect_++;
    if (check_effect_ == effect_.size() * 1) {
      check_effect_ = 0;
      is_effect_ = false;
    }
  }
}