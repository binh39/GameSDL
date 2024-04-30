#include "CommonFunction.h"

using namespace std;

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
  int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;

  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  /*if (left_a > left_b && left_a < right_b)
  {

  }*/

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  /*if (right_a > left_b && right_a < right_b)
  {

  }*/

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  /*if (left_b > left_a && left_b < right_a)
  {

  }*/

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  /*if (right_b > left_a && right_b < right_a)
  {

  }*/

   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}

bool SDLCommonFunc::CheckVaQuai(const SDL_Rect& player, const SDL_Rect& object){
    int left_a = player.x;
    int right_a = player.x + player.w;
    int top_a = player.y;
    int bottom_a = player.y + player.h;

    int left_b = object.x;
    int right_b = object.x + object.w;
    int top_b = object.y;
    int bottom_b = object.y + object.h;

    if(0<=(bottom_a-top_b) &&(bottom_a-top_b)<10 && (left_a<right_b && right_a>left_b)) return true;

    return false;
}
