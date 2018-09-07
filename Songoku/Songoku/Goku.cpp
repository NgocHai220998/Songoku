#include "Goku.h"



Goku::Goku()
{
  x_val_ = 0;
  y_val_ = 0;
  goor_.x = 0;
  goor_.y = 0;
  goor_.w = WIDTH_MAIN;
  goor_.h = HEIGHT_MAIN;
  background_ = NULL;
  HP_goku = MAX_HP_GOKU;
  index_hp = INDEX_HP_MAX*0.6;
  Mana_goku = MAX_MANA_GOKU;
  Power_goku = 101;
  type_goku = Fly;
  status_goku = Goku_Normal;
  check_kameha = 0;
  check_change = 0;
  time_change = MAX_TIME_CHANGE;

}


Goku::~Goku()
{
  if (background_ != NULL) {
    SDL_FreeSurface(background_);
  }
}

void Goku::handleInput(SDL_Event event, Mix_Chunk* g_sound_skill, Mix_Chunk* g_sound_kameha)
{
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym)
    {
    case SDLK_UP: {
      check_change = 0;
      if (check_kameha == 0) {
        y_val_ = -15;
        type_goku = FlyUp;
      }
      break;
    }
    case SDLK_DOWN: {
      check_change = 0;
      if (check_kameha == 0) {
        y_val_ = 15;
        type_goku = FlyDown;
      }
      break;
    }
    case SDLK_LEFT: {
      check_change = 0;
      if (check_kameha == 0) {
        x_val_ = -15;
        type_goku = FlyLeft;
      }
      break;
    }
    case SDLK_RIGHT: {
      check_change = 0;
      if (check_kameha == 0) {
        x_val_ = 15;
        type_goku = FlyRight;
      }  
      break;
    }
    case SDLK_RCTRL: {
      check_change = 0;
      if (check_kameha == 0 && Power_goku >= 1000 && status_goku == Goku_Normal) {
        type_goku = Change;
      }
    }
    default:
      break;
    }
  }
  //////////////////////////////////
  if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym)
    {
    case SDLK_UP: {
      if (check_kameha == 0) {
        y_val_ = 0;
        type_goku = Fly;
      }      
      break;
    }
    case SDLK_DOWN: {
      if (check_kameha == 0){
        y_val_ = 0;
        type_goku = Fly;
      }      
      break;
    }
    case SDLK_LEFT: {
      if (check_kameha == 0) {
        x_val_ = 0;
        type_goku = Fly;
      }      
      break;
    }
    case SDLK_RIGHT: {
      if (check_kameha == 0) {
        x_val_ = 0;
        type_goku = Fly;
      }   
      break;
    }
    case SDLK_RCTRL: {
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
    if (event.button.button == SDL_BUTTON_LEFT & Mana_goku > 200 && check_kameha == 0) {
      check_change = 0;
      static int index_mana;
      type_goku = ButtunLeft;
      Mix_PlayChannel(-1, g_sound_skill, 0);
      static SDL_Surface* bk1 = PublicFunction::LoadImage("Skill.png");
      static SDL_Surface* bk2 = PublicFunction::LoadImage("SkillSaiyan.png");
      Skill* p_skill = new Skill;
      if (status_goku == Goku_Saiyan1) {
        p_skill->setBackground(bk2);
        index_mana = 95;
      }
      else if (status_goku == Goku_Normal) {
        p_skill->setBackground(bk1);
        index_mana = 70;
      }
      
      Mana_goku -= index_mana;
      
      p_skill->setGoor(this->goor_.x + WIDTH_MAIN * 1.4, this->goor_.y + HEIGHT_MAIN*1.4);
      p_skill->setIsMove(true);
      p_skill->setX_Val(40);
      list_skill_.push_back(p_skill);

    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      check_change = 0;
      if (type_goku == Fly && Mana_goku > 700 && Power_goku > 150) {
        Mana_goku -= 900;
        Power_goku -= 100;
        type_goku = Kameha;
        Mix_PlayChannel(-1, g_sound_kameha, 0);
      }
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


void Goku::handleMove(const int & width, const int & height, SDL_Surface* des, vector<MonsterObject*> &list_monster)
{
  static vector<SDL_Surface*> Fly_goku = Fly_;
  static vector<SDL_Surface*> FlyRight_goku = FlyRight_;
  static vector<SDL_Surface*> FlyLeft_goku = FlyLeft_;
  static vector<SDL_Surface*> Kameha_goku = Kameha_;
  if (status_goku == Goku_Saiyan1) {
    time_change--;
    index_hp = INDEX_HP_MAX * 1.1;
    Fly_goku = FlySaiyan_;
    FlyRight_goku = FlyRightSaiyan_;
    FlyLeft_goku = FlyLeftSaiyan_;
    Kameha_goku = KamehaSaiyan_;
    if (time_change <= 0) {
      Fly_goku = Fly_;
      FlyRight_goku = FlyRight_;
      FlyLeft_goku = FlyLeft_;
      Kameha_goku = Kameha_;
      index_hp = INDEX_HP_MAX*0.6;
      status_goku = Goku_Normal;
      Power_goku = 101;
      type_goku = Fly;
      status_goku = Goku_Normal;
      check_kameha = 0;
      check_change = 0;
      time_change = MAX_TIME_CHANGE;
    }
  }
  if (Mana_goku < MAX_MANA_GOKU) {
    if (status_goku == Goku_Normal) {
      Mana_goku += 3;
    }
    else if (status_goku == Goku_Saiyan1) {
      Mana_goku += 5;
    }
  }
  goor_.x += x_val_;
  goor_.y += y_val_;

  if (goor_.x < -50 || goor_.x + WIDTH_MAIN > width - 40) {
    goor_.x -= x_val_;   
  }
  if (goor_.y < -130 || goor_.y + HEIGHT_MAIN > height - 130) {
    goor_.y -= y_val_;
  }
  /////////////////////
  if (type_goku == Fly) {
    static int fly = 0;
    background_ = Fly_goku.at(fly / 10);
    fly++;
    if (fly == Fly_goku.size()*10) {
      fly = 0;
    }
  }
  /////////////////////
  if (type_goku == FlyRight) { 
    static int fly_right = 0;
    background_ = FlyRight_goku.at(fly_right / 8);
    fly_right++;
    if (fly_right == FlyRight_goku.size()*8) {
      fly_right = 0;
    }
  }
  /////////////////////
  if (type_goku == FlyLeft) {
    static int fly_left = 0;
    background_ = FlyLeft_goku.at(fly_left / 10);
    fly_left++;
    if (fly_left == FlyLeft_goku.size()*10) {
      fly_left = 0;
    }
  }
  /////////////////////
  if (type_goku == FlyUp) {
    background_ = FlyUp_;
    if (status_goku == Goku_Saiyan1) {
      background_ = FlyUpSaiyan_;
    }
    else if (status_goku == Goku_Normal) {
      background_ = FlyUp_;
    }
  }
  /////////////////////
  if (type_goku == FlyDown) {
    background_ = FlyDown_;
    if (status_goku == Goku_Saiyan1) {
      background_ = FlyDownSaiyan_;
    }
  }
  /////////////////////
  if (type_goku == ButtunLeft) {
    static int hihi = 0;
    background_ = ButtunLeft_;
    if (status_goku == Goku_Saiyan1) {
      background_ = ButtunLeftSaiyan_;
    }
    else if (status_goku == Goku_Normal) {
      background_ = ButtunLeft_;
    }
    hihi++;
    if (hihi == 7) {
      type_goku = Fly;
      hihi = 0;
    }
  }
  /////////////////////
  if (type_goku == Kameha) {
    background_ = Kameha_goku.at(check_kameha / 6);
    if (check_kameha > 40) {
      for (int i = 0; i < list_monster.size(); ++i) {
        if ((list_monster.at(i)->getGoor().y > goor_.y + WIDTH_MAIN && list_monster.at(i)->getGoor().y < goor_.y + 250 && status_goku == Goku_Normal)
          ||(list_monster.at(i)->getGoor().y > goor_.y + WIDTH_MAIN - 100 && list_monster.at(i)->getGoor().y < goor_.y + 200 && status_goku == Goku_Saiyan1)) {
          list_monster.at(i)->setHP(list_monster.at(i)->getHP() - index_hp*0.2);
          if (list_monster.at(i)->getHP() <= 0) {
            static Mix_Chunk* sound_monster = Mix_LoadWAV("Monster2018.wav");
            Mix_PlayChannel(-1, sound_monster, 0);
            list_monster.at(i)->setDead(Dead_);
            list_monster.at(i)->setTypeMonster(1);
          }
          else {
            list_monster.at(i)->setTemp(StatusBomb_);
            list_monster.at(i)->setTypeMonster(3);
          }
        }
      }
    }
    check_kameha++;
    if (check_kameha == Kameha_goku.size()*6) {
      type_goku = Fly;
      check_kameha = 0;
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  if (type_goku == Change) {
    static vector<SDL_Surface*> Change_goku = Change_;
    //if (status_goku == Goku_Saiyan1) {
    //  Change_goku = ChangeSaiyan_;
    //}
    background_ = Change_goku.at(check_change / 7);
    Power_goku -= 12;
    check_change++;
    if (check_change == Change_goku.size() * 7) {
      type_goku = Fly;
      status_goku = Goku_Saiyan1;
      check_change = 0;
      
    }
  }





  /////////////////////////////////////////////Mana////////////////////////////////////////////////
  {
    static SDL_Surface* avatar = PublicFunction::LoadImage("AvatarGoku.png");
    PublicFunction::ApplySurface(avatar, des, 10, 10);
  }
  for (int i = 0; i < Mana_goku / 100; ++i) {
    PublicFunction::ApplySurface(Mana_,des, 100 + (10 * i), 40);  
  }
  for (int i = 0; i < HP_goku / 100; ++i) {
    PublicFunction::ApplySurface(HP_, des, 100 + (10 * i), 20);
  }
  for (int i = 0; i < Power_goku / 100; ++i) {
    PublicFunction::ApplySurface(Power_, des, 100 + (10 * i), 60);
  }

}



void Goku::displaySkill(SDL_Surface * des, vector<MonsterObject*> &list_monster)
{
  static Mix_Chunk* sound_monster = Mix_LoadWAV("Monster2018.wav");
  static SDL_Rect Goor_;
  for (int i = 0; i < list_monster.size(); ++i) {
    SDL_Rect b = list_monster.at(i)->getGoor();
    Goor_.x = goor_.x + 60;
    Goor_.y = goor_.y + 150;
    Goor_.w = WIDTH_MAIN - 20;
    Goor_.h = HEIGHT_MAIN;
    
    if (PublicFunction::checkCollision(b, Goor_) == true && list_monster.at(i)->getTypeMonster() == 2) {
      Mix_PlayChannel(-1, sound_monster, 0);
      HP_goku -= 100;
      list_monster.at(i)->setDead(Dead_);
      list_monster.at(i)->setTypeMonster(1);
    }
  }
  for (int i = 0; i < list_skill_.size(); ++i) {
    Skill* p_skill = list_skill_.at(i);
    for (int j = 0; j < list_monster.size(); j++) {
      
      SDL_Rect a = p_skill->getGoor();
      SDL_Rect b = list_monster.at(j)->getGoor();
      if (PublicFunction::checkCollision(a, b) == true) {
        if (Power_goku < MAX_POWER_GOKU) {
          Power_goku += 20;
        }
        
        Mix_PlayChannel(-1, sound_monster, 0);
        p_skill->setIsMove(false);
        list_monster.at(j)->setHP(list_monster.at(j)->getHP() - index_hp);
        if (list_monster.at(j)->getHP() <= 0) {
          list_monster.at(j)->setDead(Dead_);
          list_monster.at(j)->setTypeMonster(1);
        }
        else {
          list_monster.at(j)->setTemp(StatusBomb_);
          list_monster.at(j)->setTypeMonster(3);
        }
        
      }
    }

    if (p_skill != NULL) {
      if (p_skill->getIsMove() == true) {
        p_skill->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        p_skill->show(des);
      }
      else
      {
        // Giai phong bo nho hoan toan
        //SDL_FreeSurface(list_skill_.at(i)->getBackground());
        list_skill_.erase(list_skill_.begin() + i);
        p_skill = NULL;
      }
    }
  }
}

void Goku::initVideo()
{
  SDL_Surface* temp = new SDL_Surface;
  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("Fly1.png");
  Fly_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly4.png");
  Fly_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly2.png");
  Fly_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly3.png");
  Fly_.push_back(temp);
  ////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlyRight1.png");
  FlyRight_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRight4.png");
  FlyRight_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRight2.png");
  FlyRight_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRight3.png");
  FlyRight_.push_back(temp);
  ////////////////////////////////////////////
  temp = PublicFunction::LoadImage("Fly1.png");
  FlyLeft_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly4.png");
  FlyLeft_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly2.png");
  FlyLeft_.push_back(temp);
  temp = PublicFunction::LoadImage("Fly3.png");
  FlyLeft_.push_back(temp);
  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlyUp.png");
  FlyUp_ = temp;
  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlyDown.png");
  FlyDown_ = temp;
  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("Buttun1.png");
  ButtunLeft_ = temp;
  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlySaiyan1.png");
  FlySaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan2.png");
  FlySaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan3.png");
  FlySaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan4.png");
  FlySaiyan_.push_back(temp);
  //////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlySSaiyan1.png");
  FlySSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySSaiyan2.png");
  FlySSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySSaiyan3.png");
  FlySSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySSaiyan4.png");
  FlySSaiyan_.push_back(temp);
  //////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlySaiyan1.png");
  FlyLeftSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan2.png");
  FlyLeftSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan3.png");
  FlyLeftSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySaiyan4.png");
  FlyLeftSaiyan_.push_back(temp);
  //////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlySSaiyan1.png");
  FlyLeftSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySSaiyan2.png");
  FlyLeftSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySSaiyan3.png");
  FlyLeftSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlySSaiyan4.png");
  FlyLeftSSaiyan_.push_back(temp);
  ///////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlyRightSaiyan1.png");
  FlyRightSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSaiyan2.png");
  FlyRightSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSaiyan3.png");
  FlyRightSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSaiyan4.png");
  FlyRightSaiyan_.push_back(temp);
  ///////////////////////////////////////////////
  temp = PublicFunction::LoadImage("FlyRightSSaiyan1.png");
  FlyRightSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSSaiyan2.png");
  FlyRightSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSSaiyan3.png");
  FlyRightSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("FlyRightSSaiyan4.png");
  FlyRightSSaiyan_.push_back(temp);
  ////////////////////////////////////////////////
  FlyUpSaiyan_ = PublicFunction::LoadImage("FlyUpSaiyan.png");
  ////////////////////////////////////////////////
  FlyDownSaiyan_ = PublicFunction::LoadImage("FlyUpSaiyan.png");
  ////////////////////////////////////////////////
  ButtunLeftSaiyan_ = PublicFunction::LoadImage("ButtunSaiyan1.png");
  ////////////////////////////////////////////////
  FlyUpSSaiyan_ = PublicFunction::LoadImage("FlyUpSSaiyan.png");
  ////////////////////////////////////////////////
  FlyDownSSaiyan_ = PublicFunction::LoadImage("FlyUpSSaiyan.png");
  ////////////////////////////////////////////////
  ButtunLeftSSaiyan_ = PublicFunction::LoadImage("ButtunSSaiyan1.png");
  ////////////////////////////////////////////////
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
  //////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////
  Mana_ = PublicFunction::LoadImage("Mana.png");
  /////////////////////////////////////////////
  HP_ = PublicFunction::LoadImage("HP.png");
  /////////////////////////////////////////////
  Power_ = PublicFunction::LoadImage("Power.png");
  /////////////////////////////////////////////
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
  //temp = PublicFunction::LoadImage("KamehaSaiyan13.png");
  //KamehaSaiyan_.push_back(temp);
  //temp = PublicFunction::LoadImage("KamehaSaiyan14.png");
  //KamehaSaiyan_.push_back(temp);
  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("KamehaSSaiyan1.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan2.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan3.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan4.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan5.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan6.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan7.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan8.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan9.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan10.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan11.png");
  KamehaSSaiyan_.push_back(temp);
  temp = PublicFunction::LoadImage("KamehaSSaiyan12.png");
  KamehaSSaiyan_.push_back(temp);
  //temp = PublicFunction::LoadImage("KamehaSaiyan13.png");
  //KamehaSaiyan_.push_back(temp);
  //temp = PublicFunction::LoadImage("KamehaSaiyan14.png");
  //KamehaSaiyan_.push_back(temp);
  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("Bomb1.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb2.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb3.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb4.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb5.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb6.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb7.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb8.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb9.png");
  Dead_.push_back(temp);
  temp = PublicFunction::LoadImage("Bomb10.png");
  Dead_.push_back(temp);
  /////////////////////////////////////////////
  temp = PublicFunction::LoadImage("MonsterTemp1.png");
  StatusBomb_.push_back(temp);
  temp = PublicFunction::LoadImage("MonsterTemp1.png");
  StatusBomb_.push_back(temp);
  temp = PublicFunction::LoadImage("MonsterTemp1.png");
  StatusBomb_.push_back(temp);
  temp = PublicFunction::LoadImage("MonsterTemp2.png");
  StatusBomb_.push_back(temp);
  temp = PublicFunction::LoadImage("MonsterTemp2.png");
  StatusBomb_.push_back(temp);
  temp = PublicFunction::LoadImage("MonsterTemp2.png");
  StatusBomb_.push_back(temp);

}

void Goku::clearVideo()
{
  ////////////////////ClearFly/////////////////
  for (int i = 0; i < Fly_.size(); ++i) {
    if (Fly_.at(i) != NULL) {
      SDL_FreeSurface(Fly_.at(i));
      Fly_.at(i) = NULL;
    }
  }
  Fly_.clear();
  ////////////////ClearFlyRight/////////////////
  for (int i = 0; i < FlyRight_.size(); ++i) {
    if (FlyRight_.at(i) != NULL) {
      SDL_FreeSurface(FlyRight_.at(i));
      FlyRight_.at(i) = NULL;
    }
  }
  FlyRight_.clear();
  ///////////////ClearFlyLeft///////////////////
  for (int i = 0; i < Fly_.size(); ++i) {
    if (Fly_.at(i) != NULL) {
      SDL_FreeSurface(Fly_.at(i));
      Fly_.at(i) = NULL;
    }
  }
  Fly_.clear();
  /////////////////ClearFlyUp///////////////////
  if (FlyUp_ != NULL) {
    SDL_FreeSurface(FlyUp_);
    FlyUp_ = NULL;
  }
  /////////////////ClearFlyDown/////////////////
  if (FlyDown_ != NULL) {
    SDL_FreeSurface(FlyDown_);
    FlyDown_ = NULL;
  }
  /////////////////ClearMana////////////////////
  if (Mana_ != NULL) {
    SDL_FreeSurface(Mana_);
    Mana_ = NULL;
  }
  /////////////////ClearHP////////////////////
  if (HP_ != NULL) {
    SDL_FreeSurface(HP_);
    HP_ = NULL;
  }
  /////////////////ClearPower////////////////////
  if (Power_ != NULL) {
    SDL_FreeSurface(Power_);
    Power_ = NULL;
  }
  ///////////////////ClearButtunLeft////////////
  if (ButtunLeft_ != NULL) {
    SDL_FreeSurface(ButtunLeft_);
    ButtunLeft_ = NULL;
  }
  ////////////////////ClearKameha///////////////
  for (int i = 0; i < Kameha_.size(); ++i) {
    if (Kameha_.at(i) != NULL) {
      SDL_FreeSurface(Kameha_.at(i));
      Kameha_.at(i) = NULL;
    }
  }
  Kameha_.clear();
  ////////////////////ClearDead///////////////
  for (int i = 0; i < Dead_.size(); ++i) {
    if (Dead_.at(i) != NULL) {
      SDL_FreeSurface(Dead_.at(i));
      Dead_.at(i) = NULL;
    }
  }
  Dead_.clear();
  ////////////////////ClearStatusBomb///////////////
  for (int i = 0; i < StatusBomb_.size(); ++i) {
    if (StatusBomb_.at(i) != NULL) {
      SDL_FreeSurface(StatusBomb_.at(i));
      StatusBomb_.at(i) = NULL;
    }
  }
  StatusBomb_.clear();

  ////////////////ClearChange/////////////////////
  for (int i = 0; i < Change_.size(); ++i) {
    if (Change_.at(i) != NULL) {
      SDL_FreeSurface(Change_.at(i));
      Change_.at(i) = NULL;
    }
  }
  Change_.clear();
  /////////////////ClearFlySaiyan//////////////////
  for (int i = 0; i < FlySaiyan_.size(); ++i) {
    if (FlySaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlySaiyan_.at(i));
      FlySaiyan_.at(i) = NULL;
    }
  }
  FlySaiyan_.clear();
  /////////////////ClearFlySSaiyan//////////////////
  for (int i = 0; i < FlySSaiyan_.size(); ++i) {
    if (FlySSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlySSaiyan_.at(i));
      FlySSaiyan_.at(i) = NULL;
    }
  }
  FlySSaiyan_.clear();
  /////////////////ClearFlyLeftSaiYan//////////////
  for (int i = 0; i < FlyLeftSaiyan_.size(); ++i) {
    if (FlyLeftSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlyLeftSaiyan_.at(i));
      FlyLeftSaiyan_.at(i) = NULL;
    }
  }
  FlyLeftSaiyan_.clear();
  /////////////////ClearFlyLeftSSaiYan//////////////
  for (int i = 0; i < FlyLeftSSaiyan_.size(); ++i) {
    if (FlyLeftSSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlyLeftSSaiyan_.at(i));
      FlyLeftSSaiyan_.at(i) = NULL;
    }
  }
  FlyLeftSSaiyan_.clear();
  //////////////////ClearFlyRightSaiYan////////////
  for (int i = 0; i < FlyRightSaiyan_.size(); ++i) {
    if (FlyRightSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlyRightSaiyan_.at(i));
      FlyRightSaiyan_.at(i) = NULL;
    }
  }
  FlyRightSaiyan_.clear();
  //////////////////ClearFlyRightSSaiYan////////////
  for (int i = 0; i < FlyRightSSaiyan_.size(); ++i) {
    if (FlyRightSSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(FlyRightSSaiyan_.at(i));
      FlyRightSSaiyan_.at(i) = NULL;
    }
  }
  FlyRightSSaiyan_.clear();
  ///////////////////ClearFlyUpSaiyan///////////////
  if (FlyUpSaiyan_ != NULL) {
    SDL_FreeSurface(FlyUpSaiyan_);
    FlyUpSaiyan_ = NULL;
  }
  ///////////////////ClearDownSaiyan////////////////
  if (FlyDownSaiyan_ != NULL) {
    SDL_FreeSurface(FlyDownSaiyan_);
    FlyDownSaiyan_ = NULL;
  }
  ///////////////////ClearButtunSaiyan////////////////
  if (ButtunLeftSaiyan_ != NULL) {
    SDL_FreeSurface(ButtunLeftSaiyan_);
    ButtunLeftSaiyan_ = NULL;
  }
  ///////////////////ClearFlyUpSSaiyan///////////////
  if (FlyUpSSaiyan_ != NULL) {
    SDL_FreeSurface(FlyUpSSaiyan_);
    FlyUpSSaiyan_ = NULL;
  }
  ///////////////////ClearDownSSaiyan////////////////
  if (FlyDownSSaiyan_ != NULL) {
    SDL_FreeSurface(FlyDownSSaiyan_);
    FlyDownSSaiyan_ = NULL;
  }
  ///////////////////ClearButtunSSaiyan////////////////
  if (ButtunLeftSSaiyan_ != NULL) {
    SDL_FreeSurface(ButtunLeftSSaiyan_);
    ButtunLeftSSaiyan_ = NULL;
  }
  ///////////////////ClearKamehaSaiyan////////////////
  for (int i = 0; i < KamehaSaiyan_.size(); ++i) {
    if (KamehaSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(KamehaSaiyan_.at(i));
      KamehaSaiyan_.at(i) = NULL;
    }
  }
  KamehaSaiyan_.clear();
  ///////////////////ClearKamehaSSaiyan////////////////
  for (int i = 0; i < KamehaSSaiyan_.size(); ++i) {
    if (KamehaSSaiyan_.at(i) != NULL) {
      SDL_FreeSurface(KamehaSSaiyan_.at(i));
      KamehaSSaiyan_.at(i) = NULL;
    }
  }
  KamehaSSaiyan_.clear();
}
