#include "Songoku.h"



Songoku::Songoku()
{
  x_val_ = 0;
  y_val_ = 0;
  goor_.x = 0;
  goor_.y = 0;
  goor_.w = WIDTH_MAIN;
  goor_.h = HEIGHT_MAIN;
  status_main_ = idle;
  HP_main_ = HP_MAIN;
  Mana_main_ = MANA_MAIN;
  Power_main_ = 0;
  background_ = NULL;
  check_change_ = 0;
  check_kameha_ = 0;
  check_time_event_ = 0;
  index_key_event_ = 0;
  speed_ = SPEED_SONGOKU;
  time_run_game_ = 0;
  type_goku_ = Goku;
  check_time_ = 0;
}


Songoku::~Songoku()
{
}


////////////////////////////////////////////////////////////             Update 
void Songoku::Update(SDL_Surface* g_screen, Effect* &effect, vector<HandleEffect*>& list_effect,int check_war)
{

  if (Mana_main_ < MANA_MAIN) {
    Mana_main_ += 3;
  }
  if (type_goku_ == SuperGoku1) {
    check_time_++;
    if (check_time_ == 2000) {
      check_time_ = 0;
      type_goku_ = Goku;
    }
  }

  if (status_main_ == idle) {                                           // Fly_goku
    static int index = 0;
    static vector<SDL_Surface*> Fly;
    if (type_goku_ == SuperGoku1) {
      Fly = FlySaiyan_;
    }
    else {
      Fly = idle_;
    }
    background_ = Fly.at(index / 4);
    if (++index == Fly.size()*4) {
      index = 0;
    }
  }

  if (status_main_ == right) {                                           // Fly_right
    static int index = 0;
    static vector<SDL_Surface*> right_goku;
    if (type_goku_ == SuperGoku1) {
      right_goku = FlyRightSaiyan_;
    }
    else {
      right_goku = right_;
    }
    background_ = right_goku.at(index / 6);
    if (++index == right_goku.size() * 6) {
      index = 0;
    }
  }

  if (status_main_ == left) {                                           // Fly_lèt
    static int index = 0;
    static vector<SDL_Surface*> left_goku;
    if (type_goku_ == SuperGoku1) {
      left_goku = FlyLeftSaiyan_;
    }
    else {
      left_goku = right_;
    }
    background_ = left_goku.at(index / 6);
    if (++index == left_goku.size() * 6) {
      index = 0;
    }
  }

  if (status_main_ == down) {                                           // Fly_down
    if (type_goku_ == SuperGoku1) {
      background_ = FlyDownSaiyan_;
    }
    else {
      background_ = down_;
    }
  }

  if (status_main_ == up) {                                           // Fly_up
    if (type_goku_ == SuperGoku1) {
      background_ = FlyUpSaiyan_;
    }
    else {
      background_ = up_;
    }
  }

  if (status_main_ == normal) {                                        // Normal
    static int index = 0;
    static vector<SDL_Surface*> normal_goku;
    if (type_goku_ == SuperGoku1) {
      normal_goku = ButtunLeftSaiyan_;
    }
    else {
      normal_goku = normal_;
    }
    background_ = normal_goku.at(index /2);
    if (++index == normal_goku.size()*2) {
      status_main_ = idle;
      index = 0;
    }
  }

  if (status_main_ == change) {                                       // change
    background_ = Change_.at(check_change_ / 6);
    if (++check_change_ == Change_.size() * 6) {
      type_goku_ = SuperGoku1;
      status_main_ = idle;
      check_change_ = 0;
    }
  }

  if (status_main_ == ultimate) {                                       //kameha
    static vector<SDL_Surface*> kameha_goku;
    if (type_goku_ == SuperGoku1) {
      kameha_goku = KamehaSaiyan_;
    }
    else {
      kameha_goku = Kameha_;
    }
    background_ = kameha_goku.at(check_kameha_ / 6);
    if (++check_kameha_ == kameha_goku.size() * 6) {
      status_main_ = idle;
      check_kameha_ = 0;
    }
  }
  static vector<Warning*> list_warning;
  static int check_sound = 0;
  static SDL_Rect Goor_ = goor_;
  static Mix_Chunk* sound_monster = Mix_LoadWAV("Collision.wav");
  static Mix_Chunk* sound_war = Mix_LoadWAV("soundWar.wav");
  static int id = 0;
  static int b = 0;
  if (check_war % 3500 > 2000) {
    id = rand() % 70;
    b = rand() % 350;
  }
  else {
    id = 0;
  }
  if (id == 35) {
    
 
    Warning* p_war = new Warning();
    p_war->setWarning(war_);
    p_war->setX_Val(30);
    p_war->setIsMove(true);
    p_war->setGoor(1350, 100 + rand() % 500);
    list_warning.push_back(p_war);
  }
  for (int i = 0; i < list_warning.size(); ++i) {
    if (check_sound % 100 == 5) {
      Mix_PlayChannel(-1, sound_war, 0);
    }
    
    Warning* p_war = list_warning.at(i);
    Goor_.x = goor_.x + 40;
    Goor_.y = goor_.y + 145;
    Goor_.w = WIDTH_MAIN;
    Goor_.h = HEIGHT_MAIN;
    if (PublicFunction::checkCollision(p_war->getGoor(), Goor_)) {
      HP_main_ -= p_war->getHP()*0.25;
      Mix_PlayChannel(-1, sound_monster, 0);
      HandleEffect* temp_effect = new HandleEffect();
      temp_effect->setGoor(list_warning.at(i)->getGoor().x, list_warning.at(i)->getGoor().y);
      temp_effect->setEffect(effect->getBomb());
      temp_effect->setIsEffect(true);
      list_effect.push_back(temp_effect);
      list_warning.at(i)->setIsMove(false);
    }
    if (p_war != NULL) {
      if (p_war->getIsMove() == true && p_war->getHP() > 0) {
        p_war->show(g_screen);
        p_war->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
      }
      else {
        //SDL_FreeSurface(list_monster.at(i)->getBackground());
        list_warning.erase(list_warning.begin() + i);
        p_war = NULL;
      }
    }
  }
  check_sound++;

  static vector<Boss*> list_boss;
  
  if (b == 35) {
    Boss* p_boss = new Boss();
    p_boss->setBoss(boss_);
    p_boss->setX_Val(1);
    p_boss->setIsMove(true);
    p_boss->setGoor(1500, 10 + rand() % 600);
    list_boss.push_back(p_boss);
  }
  for (int i = 0; i < list_boss.size(); ++i) {                                   //handle boss
    if (this->check_kameha_ > 40 && this->check_kameha_ < 65) {
      if (list_boss.at(i)->getGoor().y > this->getGoor().y - 50 
        && list_boss.at(i)->getGoor().y < this->getGoor().y + 130
        && list_boss.at(i)->getGoor().x > this->getGoor().x + WIDTH_MAIN) {
        HandleEffect* temp_effect = new HandleEffect();
        temp_effect->setGoor(list_boss.at(i)->getGoor().x + 50, list_boss.at(i)->getGoor().y + 60);
        temp_effect->setEffect(effect->getBomb());
        temp_effect->setIsEffect(true);
        list_effect.push_back(temp_effect);
        if (type_goku_ == Goku) {
          list_boss.at(i)->setHP(list_boss.at(i)->getHP() - 30);
        }
        else {
          list_boss.at(i)->setHP(list_boss.at(i)->getHP() - 60);
        }
      }
    }
    for (int j = 0; j < list_bullet_.size(); ++j) {
      Bullet* p_bullet =  list_bullet_.at(j);
      if (PublicFunction::checkCollision(p_bullet->getGoor(), list_boss.at(i)->getGoor()) && p_bullet->getTypeBullet() != blu) {
        list_boss.at(i)->setDisplayHP(true);
        
        list_boss.at(i)->setHP(list_boss.at(i)->getHP() - p_bullet->getHP());
        p_bullet->setHP(p_bullet->getHP() - 120);
        if (list_boss.at(i)->getHP() <= 10) {
          Power_main_ = POWER_MAIN;
          HandleEffect* temp_effect = new HandleEffect();
          temp_effect->setGoor(list_boss.at(i)->getGoor().x, list_boss.at(i)->getGoor().y);
          temp_effect->setEffect(effect->getBigBomb());
          temp_effect->setIsEffect(true);
          list_effect.push_back(temp_effect);
        }
        else {
          Power_main_ += 10;
          HandleEffect* temp_effect = new HandleEffect();
          temp_effect->setGoor(p_bullet->getGoor().x, p_bullet->getGoor().y);
          temp_effect->setEffect(effect->getBomb());
          temp_effect->setIsEffect(true);
          list_effect.push_back(temp_effect);
        }
        
        
      }
    }
    static int bc = 0;
    bc = rand() % 150;
    if (bc == 47) {
      HandleEffect* temp_effect = new HandleEffect();
      temp_effect->setGoor(list_boss.at(i)->getGoor().x - 30, list_boss.at(i)->getGoor().y + 90);
      temp_effect->setEffect(effect->getEffectBlu());
      temp_effect->setIsEffect(true);
      list_effect.push_back(temp_effect);


      list_boss.at(i)->setStatus(1);
      Bullet* p_bullet = new Bullet();
      p_bullet->setIsMove(true);

      p_bullet->setTypeBullet(TypeBullet::blu);
      p_bullet->setGoor(list_boss.at(i)->getGoor().x - 30 , list_boss.at(i)->getGoor().y + 90);
      p_bullet->setX_Val(-SPEED_BLU, time_run_game_);

      Mix_PlayChannel(-1, sound_red, 0);
      list_bullet_.push_back(p_bullet);
    }
    Boss* p_boss = list_boss.at(i);                                              //show boss
    if (p_boss != NULL) {
      if (p_boss->getIsMove() == true && p_boss->getHP() > 0) {
        p_boss->show(g_screen);
        p_boss->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT,g_screen);
      }
      else {
        //SDL_FreeSurface(list_monster.at(i)->getBackground());
        list_boss.erase(list_boss.begin() + i);
        p_boss = NULL;
      }
    }
  }


}

///////////////////////////////////////////////////                  HandleInputAction
void Songoku::handleInput(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN) {
    check_change_ = 0;
    switch (event.key.keysym.sym)
    {
    case SDLK_r: {
      if (Mana_main_ > 50 && check_kameha_ == 0 && status_main_ != change) {
        Mana_main_ -= 50;
      }
      else {
        break;
      }
      status_main_ = normal;
      Bullet* p_bullet = new Bullet();
      p_bullet->setIsMove(true);
      if (type_goku_ == Goku) {
        p_bullet->setTypeBullet(TypeBullet::red);
        p_bullet->setGoor(this->goor_.x + WIDTH_MAIN * 1.4, this->goor_.y + HEIGHT_MAIN * 1.4);
        p_bullet->setX_Val(SPEED_RED, time_run_game_);
      }
      else {
        p_bullet->setTypeBullet(TypeBullet::fire);
        p_bullet->setGoor(this->goor_.x + WIDTH_MAIN * 1.4, this->goor_.y + HEIGHT_MAIN * 1.3);
        p_bullet->setX_Val(SPEED_FIRE, time_run_game_);
      }
      
      Mix_PlayChannel(-1, sound_red, 0);
      list_bullet_.push_back(p_bullet);

      break;
    }
    case SDLK_UP: {
      if (check_kameha_ == 0) {
        status_main_ = up;
        y_val_ = -(time_run_game_*speed_);
      }  
      break;
    }
    case SDLK_DOWN: {
      if (check_kameha_ == 0) {
        status_main_ = down;
        y_val_ = (time_run_game_*speed_);
      }
      break;
    }
    case SDLK_LEFT: {
      if (check_kameha_ == 0) {
        status_main_ = left;
        x_val_ = -(time_run_game_*speed_);
      }
      break;
    }
    case SDLK_RIGHT: {
      if (check_kameha_ == 0) {
        status_main_ = right;
        x_val_ = (time_run_game_*speed_);
      }
      break;
    }
    case SDLK_LCTRL: {
      if (status_main_ != ultimate && Power_main_ > 500 && status_main_ != change) {
        Power_main_ -= 500;
        status_main_ = change;
      }
      
    }
    default:
      if (check_kameha_ != 0) {
        break;
      }
      if (index_key_event_ == 3) {
        index_key_event_ = 0; 
        key_event_.clear();
      }
      key_event_.push_back(event.key.keysym.sym);
      index_key_event_++;
      if (index_key_event_ == 3 && key_event_[0] == 'q' && key_event_[1] == 'e' && key_event_[2] == 'w' && Power_main_ > 500) {
        Power_main_ -= 500;
        Mix_PlayChannel(-1,sound_kameha, 0);
        status_main_ = ultimate;
      }
      break;
    }
  }
  //////////////////////////////////
  if (event.type == SDL_KEYUP) {
    if (check_kameha_ == 0) {
      status_main_ = idle;
    }
    switch (event.key.keysym.sym)
    {
    case SDLK_r: {
      break;
    }
    case SDLK_UP: {
      y_val_ = 0;
      break;
    }
    case SDLK_DOWN: {
      y_val_ = 0;
      break;
    }
    case SDLK_LEFT: {
      x_val_ = 0;
      break;
    }
    case SDLK_RIGHT: {
      x_val_ = 0;
      break;
    }
    case SDLK_LCTRL: {
      /*if (check_kameha == 0 && Power_goku >= 1000 && status_goku == Goku_Normal) {
      type_goku = Change;
      Power_goku -= 1000;
      }*/
    }
    default:
      break;
    }
  }
  ////////////////////////////////
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      //Todo
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
}

//////////////////////////////////////////////////////////              HandleMove
void Songoku::handleMove(const int & width, const int & height, SDL_Surface * des)
{
  if (check_time_event_ % 180 == 0) {
    index_key_event_ = 3;
  }
  check_time_event_++;
  goor_.x += x_val_;
  goor_.y += y_val_;

  if (goor_.x < -50 || goor_.x + WIDTH_MAIN > width - 40) {
    goor_.x -= x_val_;
  }
  if (goor_.y < -130 || goor_.y + HEIGHT_MAIN > height - 130) {
    goor_.y -= y_val_;
  }
}

///////////////////////////////////////////////////////////             Display
void Songoku::display(SDL_Surface * des,vector<Monster*>& list_monster, Effect* &effect, vector<HandleEffect*>& list_effect)
{

  static Mix_Chunk* sound_monster = Mix_LoadWAV("Collision.wav");
  static SDL_Rect Goor_ = goor_;
  Goor_.x = goor_.x + 40;
  Goor_.y = goor_.y + 145;
  Goor_.w = WIDTH_MAIN;
  Goor_.h = HEIGHT_MAIN;
  

  for (int j = 0; j < list_monster.size(); ++j) {

    

    if (PublicFunction::checkCollision( list_monster.at(j)->getGoor(), Goor_)) {
      HandleEffect* temp_effect = new HandleEffect();
      HP_main_ -= list_monster.at(j)->getHP();
      Mix_PlayChannel(-1, sound_monster, 0);
      temp_effect->setGoor(list_monster.at(j)->getGoor().x, list_monster.at(j)->getGoor().y);
      temp_effect->setEffect(effect->getBomb());
      temp_effect->setIsEffect(true);
      list_effect.push_back(temp_effect);
      list_monster.at(j)->setHP(list_monster.at(j)->getHP() - HP_RED *10);
    }


    if (this->check_kameha_ > 50 && this->check_kameha_ < 70 ) {
      if (list_monster.at(j)->getGoor().y > this->getGoor().y + HEIGHT_MAIN - 60
        && list_monster.at(j)->getGoor().y < this->getGoor().y + 250
        && list_monster.at(j)->getGoor().x > this->getGoor().x + WIDTH_MAIN) {
        Mix_PlayChannel(-1, sound_monster, 0);
        HandleEffect* temp_effect = new HandleEffect();
        temp_effect->setGoor(list_monster.at(j)->getGoor().x, list_monster.at(j)->getGoor().y);
        temp_effect->setEffect(effect->getBomb());
        temp_effect->setIsEffect(true);
        list_effect.push_back(temp_effect);
        if (type_goku_ == normal) {
          list_monster.at(j)->setHP(list_monster.at(j)->getHP() - HP_RED * 0.1);
        }
        else {
          list_monster.at(j)->setHP(list_monster.at(j)->getHP() - HP_RED * 0.5);
        }


        
      }
    }
  }
  for (int i = 0; i < list_bullet_.size(); ++i) {
    Bullet* p_bullet = list_bullet_.at(i);
    for (int j = 0; j < list_monster.size(); j++){
      if ((PublicFunction::checkCollision(p_bullet->getGoor(), list_monster.at(j)->getGoor()) && p_bullet->getTypeBullet() != blu)
        || (PublicFunction::checkCollision(p_bullet->getGoor(),Goor_) && p_bullet->getTypeBullet() == blu)) {
        HandleEffect* temp_effect = new HandleEffect();
        Mix_PlayChannel(-1, sound_monster, 0);
        temp_effect->setGoor(p_bullet->getGoor().x, p_bullet->getGoor().y);
        
        temp_effect->setIsEffect(true);
        

        p_bullet->setHP(p_bullet->getHP() - list_monster.at(j)->getHP());
        if (p_bullet->getTypeBullet() == blu) {
          HP_main_ -= HP_BLU;
          temp_effect->setEffect(effect->getBombBlu());
          p_bullet->setHP(p_bullet->getHP() - HP_BLU);
        }
        if (p_bullet->getTypeBullet() != blu) {
          temp_effect->setEffect(effect->getBomb());
          if (p_bullet->getTypeBullet() == red) {
            list_monster.at(j)->setHP(list_monster.at(j)->getHP() - HP_RED);
          }
          else {
            list_monster.at(j)->setHP(list_monster.at(j)->getHP() - HP_FIRE);
          }
          
        }
        list_effect.push_back(temp_effect);
       
      }
    }


    if (p_bullet != NULL) {
      if (p_bullet->getIsMove() == true && p_bullet->getHP() > 0) {
        if (p_bullet->getBackground() != NULL) {
          if (p_bullet->getTypeBullet() == red) {
            p_bullet->setX_Val(SPEED_RED, time_run_game_);
          }
          if (p_bullet->getTypeBullet() == blu) {
            p_bullet->setX_Val(-SPEED_BLU, time_run_game_);
          }
          if (p_bullet->getTypeBullet() == fire) {
            p_bullet->setX_Val(SPEED_FIRE, time_run_game_);
          }
          p_bullet->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
          p_bullet->show(des);
        }
      }
      else
      {
        // Giai phong bo nho hoan toan
        //SDL_FreeSurface(list_skill_.at(i)->getBackground());
        list_bullet_.erase(list_bullet_.begin() + i);
        p_bullet = NULL;
      }
    }
  }




  {
    static SDL_Surface* avatar_goku = PublicFunction::LoadImage("AvatarGoku.png");
    PublicFunction::ApplySurface(avatar_goku, des, 10, 10);
  }

  static SDL_Surface* Mana_ = PublicFunction::LoadImage("Mana.png");
  static SDL_Surface* HP_ = PublicFunction::LoadImage("HP.png");
  static SDL_Surface* Power_ = PublicFunction::LoadImage("Power.png");

  for (int i = 0; i < Mana_main_ / 100; ++i) {
    PublicFunction::ApplySurface(Mana_, des, 100 + (10 * i), 40);
  }
  for (int i = 0; i < HP_main_ / 500; ++i) {
    PublicFunction::ApplySurface(HP_, des, 100 + (10 * i), 20);
  }
  for (int i = 0; i < Power_main_ / 100; ++i) {
    PublicFunction::ApplySurface(Power_, des, 100 + (10 * i), 60);
  }


  show(des);
}


///////////////////////////////////////////////////////////               InitVideo
void Songoku::initVideo()
{
  /////////////////////////////////////////////                           sound
  sound_kameha = Mix_LoadWAV("kameha2018.wav");
  sound_red = Mix_LoadWAV("BulletRed.wav");


  ///////////////////////////////////////////////
  SDL_Surface* temp = new SDL_Surface();
  ////////////////////////////////////////////                            Video Fly_Goku
  temp = PublicFunction::LoadImage("Fly1.png");
  idle_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly2.png");
  idle_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly3.png");
  idle_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly4.png");
  idle_.push_back(temp);
  //////////////////////////////////////////////                          Video Fly_Right_Goku
  temp = PublicFunction::LoadImage("FlyRight1.png");
  right_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRight4.png");
  right_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRight2.png");
  right_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRight3.png");
  right_.push_back(temp);
  //////////////////////////////////////////////                          Video Fly_Left_Goku
  temp = PublicFunction::LoadImage("Fly1.png");
  left_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly2.png");
  left_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly3.png");
  left_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly4.png");
  left_.push_back(temp);
  //////////////////////////////////////////////                             down
  down_ = PublicFunction::LoadImage("FlyDown.png");
  //////////////////////////////////////////////                             up
  up_ = PublicFunction::LoadImage("FlyUp.png");            
  //////////////////////////////////////////////                             normal
  temp = PublicFunction::LoadImage("buttun1.png");
  normal_.push_back(temp);
  temp = PublicFunction::LoadImage("buttun2.png");
  normal_.push_back(temp);
  temp = PublicFunction::LoadImage("buttun3.png");
  normal_.push_back(temp);
  temp = PublicFunction::LoadImage("buttun4.png");
  normal_.push_back(temp);
  temp = PublicFunction::LoadImage("buttun5.png");
  normal_.push_back(temp);
  temp = PublicFunction::LoadImage("buttun6.png");
  normal_.push_back(temp);
  temp = PublicFunction::LoadImage("buttun7.png");
  normal_.push_back(temp);
  temp = PublicFunction::LoadImage("buttun8.png");
  normal_.push_back(temp);
  /////////////////////////////////////////////                             kameha
  temp = PublicFunction::LoadImage("Kameha1.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha2.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha3.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha4.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha5.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha6.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha7.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha8.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha9.png");
  Kameha_.push_back(temp);
  temp = PublicFunction::LoadImage("Kameha10.png");
  Kameha_.push_back(temp);
  ////////////////////////////////////////////////                            change
  temp = PublicFunction::LoadImage("Change1.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change2.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change3.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change4.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change5.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change6.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change7.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change8.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change9.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change10.png");
  Change_.push_back(temp);
  temp = PublicFunction::LoadImage("Change11.png");
  Change_.push_back(temp);

  temp = PublicFunction::LoadImage("warning1.png");
  war_.push_back(temp);
  temp = PublicFunction::LoadImage("warning2.png");
  war_.push_back(temp);
  temp = PublicFunction::LoadImage("TenLua.png");
  war_.push_back(temp);

  temp = PublicFunction::LoadImage("Dragon1.png");
  boss_.push_back(temp);
  temp = PublicFunction::LoadImage("Dragon2.png");
  boss_.push_back(temp);
  temp = PublicFunction::LoadImage("Dragon3.png");
  boss_.push_back(temp);
  temp = PublicFunction::LoadImage("Dragon4.png");
  boss_.push_back(temp);

  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlySaiyan1.png");
  FlySaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan2.png");
  FlySaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan3.png");
  FlySaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan4.png");
  FlySaiyan_.push_back(temp);

  ///////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlyRightSaiyan1.png");
  FlyRightSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSaiyan2.png");
  FlyRightSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSaiyan3.png");
  FlyRightSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSaiyan4.png");
  FlyRightSaiyan_.push_back(temp);


  //////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlySaiyan1.png");
  FlyLeftSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan2.png");
  FlyLeftSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan3.png");
  FlyLeftSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan4.png");
  FlyLeftSaiyan_.push_back(temp);


  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("KamehaSaiyan1.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan2.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan3.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan4.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan5.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan6.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan7.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan8.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan9.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan10.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan11.png");
  KamehaSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSaiyan12.png");
  KamehaSaiyan_.push_back(temp);
  ////////////////////////////////////////////////
  FlyUpSaiyan_ = PublicFunction::LoadImage("FlyUpSaiyan.png");
  ////////////////////////////////////////////////
  FlyDownSaiyan_ = PublicFunction::LoadImage("FlyUpSaiyan.png");
  ////////////////////////////////////////////////
  temp = PublicFunction::LoadImage("ButtunSaiyan1.png");
  ButtunLeftSaiyan_.push_back(temp);



}
///////////////////////////////////////////////////////////               ClearVideo
void Songoku::clearVideo()
{
  ////////////////////////////////                                        Clear Video Fly_Goku
  for (int i = 0; i < idle_.size(); ++i) {
    if (idle_.at(i) != NULL) {
      SDL_FreeSurface(idle_.at(i));
      idle_.at(i) = NULL;
    }
  }
  idle_.clear();

  for (int i = 0; i < FlySaiyan_.size(); ++i) {
    if (FlySaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlySaiyan_.at(i));
      FlySaiyan_.at(i) = NULL;
    }
  }
  FlySaiyan_.clear();
  ////////////////////////////////                                        Clear Video Fly_Right_Goku
  for (int i = 0; i < right_.size(); ++i) {
    if (right_.at(i) != NULL) {
      SDL_FreeSurface(right_.at(i));
      right_.at(i) = NULL;
    }
  }
  right_.clear();

  for (int i = 0; i < FlyRightSaiyan_.size(); ++i) {
    if (FlyRightSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlyRightSaiyan_.at(i));
      FlyRightSaiyan_.at(i) = NULL;
    }
  }
  FlyRightSaiyan_.clear();
  ////////////////////////////////                                        Clear Video Fly_Left_Goku
  for (int i = 0; i < left_.size(); ++i) {
    if (left_.at(i) != NULL) {
      SDL_FreeSurface(left_.at(i));
      left_.at(i) = NULL;
    }
  }
  left_.clear();

  for (int i = 0; i < FlyLeftSaiyan_.size(); ++i) {
    if (FlyLeftSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlyLeftSaiyan_.at(i));
      FlyLeftSaiyan_.at(i) = NULL;
    }
  }
  FlyLeftSaiyan_.clear();

  ////////////////////////////////                                         clear Down
  if (down_ != NULL) {
    SDL_FreeSurface(down_);
    down_ = NULL;
  }
  ////////////////////////////////                                         clear up
  if (up_ != NULL) {
    SDL_FreeSurface(up_);
    up_ = NULL;
  }
  ///////////////////////////////////                                          normal
  for (int i = 0; i < normal_.size(); ++i) {
    if (normal_.at(i) != NULL) {
      SDL_FreeSurface(normal_.at(i));
      normal_.at(i) = NULL;
    }
  }
  normal_.clear();
  ///////////////////////////////////                                     ClearChange
  for (int i = 0; i < Change_.size(); ++i) {
    if (Change_.at(i) != NULL) {
      SDL_FreeSurface(Change_.at(i));
      Change_.at(i) = NULL;
    }
  }
  Change_.clear();
  ///////////////////////////////////                                      ClearKameha
  for (int i = 0; i < Kameha_.size(); ++i) {
    if (Kameha_.at(i) != NULL) {
      SDL_FreeSurface(Kameha_.at(i));
      Kameha_.at(i) = NULL;
    }
  }
  Kameha_.clear();


  
  ///////////////////////////////////                                      ClearKameha
  for (int i = 0; i < KamehaSaiyan_.size(); ++i) {
    if (KamehaSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(KamehaSaiyan_.at(i));
      KamehaSaiyan_.at(i) = NULL;
    }
  }
  KamehaSaiyan_.clear();
}
