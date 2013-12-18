#include "Vector2.h"

Vector2  operator+(const Vector2 &u, const Vector2 &v)
{
  Vector2 w;
  w.x = u.x+v.x;
  w.y = u.y+v.y;
  return w;
}

Vector2  operator-(const Vector2 &u, const Vector2 &v)
{
  Vector2 w;
  w.x = u.x-v.x;
  w.y = u.y-v.y;
  return w;
}

Vector2  operator*(const Vector2 &u, const float &k)
{
  Vector2 w;
  w.x = u.x*k;
  w.y = u.y*k;
  return w;
}

Vector2  operator*(const float &k, const Vector2 &u)
{
  Vector2 w;
  w.x = u.x*k;
  w.y = u.y*k;
  return w;
}

//内積
float  operator*(const Vector2 &u, const Vector2 &v)
{
  return u.x*v.x + u.y*v.y;
}

Vector2 operator/(const Vector2 &u, const float &k)
{
  Vector2 w;
  w.x = u.x/k;
  w.y = u.y/k;
  return w;
}

#include <iostream>
using namespace std;
ostream& operator<<(ostream& s, const Vector2 &v)
{
  return s << "(" << v.x << "," << v.y << ")";
}

