#include "Triangulate.h"

Triangulate::Triangulate()
{

}


Vector2d::Vector2d(float x, float y)
{
  Set(x,y);
}

float Vector2d::GetX() const { return mX; }

float Vector2d::GetY() const { return mY; }

void Vector2d::Set(float x, float y)
{
  mX = x;
  mY = y;
}
