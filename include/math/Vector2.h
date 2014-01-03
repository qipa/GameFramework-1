#ifndef VECTOR2_H_2013_12_18
#define VECTOR2_H_2013_12_18

#include <cmath>
#include <string>
#include <iostream>
using namespace std;

class Vector2
{
public:
  static constexpr float TO_RADIANS = (1.0f/180.f)*M_PI;
  static constexpr float TO_DEGREE  = 180.0f/M_PI;
  float x,y;
	
  Vector2(){
    x = y = 0;
  }
	
  Vector2(float x, float y){
    this->x = x;
    this->y = y;
  }
	
  Vector2(const Vector2 &other){
    this->x = other.x;
    this->y = other.y;
  }
	
  Vector2& set(const float &x, const float &y){
    this->x = x;
    this->y = y;
    return *this;
  }
	
  Vector2& set(const Vector2 &other){
    this->x = other.x;
    this->y = other.y;
    return *this;
  }
	
  Vector2& add(const float &x,const float &y){
    this->x += x;
    this->y += y;
    return *this;
  }
	
  Vector2& add(const Vector2 &other){
    this->x += other.x;
    this->y += other.y;    
    return *this;
  }
	
  Vector2& sub(const float &x,const float &y){
    this->x -= x;
    this->y -= y;
    return *this;
  }
	
  Vector2& sub(const Vector2 &other){
    this->x -= other.x;
    this->y -= other.y;
    return *this;
  }
	
  Vector2& mul(const float &scalar){
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }
	
  float length() const{
    return sqrt(x*x + y*y);
  }
	
  Vector2& normalize(){
    float len = length();

    if(len != 0){
      x /= len;
      y /= len;
    }
    return *this;
  }

  Vector2 normalizedVector() const {
    float len = length();
    float _x=0, _y=0;
    if(len != 0){
      _x = x/len;
      _y = y/len;
    }
    return Vector2(x,y);
  }

  //radianで返る
  float angle() const{
    float angle = (float) atan2(y, x);
    if(angle < 0)
      angle += 2*M_PI;
    return angle;
  }
	
  Vector2& rotate(float degree){
    float rad = degree * TO_RADIANS;
    float _cos = cos(rad);
    float _sin = sin(rad);
		
    float newX = this->x * _cos - this->y * _sin;
    float newY = this->x * _sin + this->y * _cos;
		
    this->x = newX;
    this->y = newY;
    return *this;
  }
	
  float dist(Vector2 other) const
  {
    float distX = this->x - other.x;
    float distY = this->y - other.y;
		
    return sqrt(distX*distX + distY*distY); 
  }
	
  float dist(float x, float y) const
  {
    float distX = this->x - x;
    float distY = this->y - y;
		
    return sqrt(distX*distX + distY*distY); 
  }

  //2乗距離
  float distSquared(Vector2 other) const
  {
    float distX = this->x - other.x;
    float distY = this->y - other.y;
		
    return distX*distX + distY*distY; 
  }
	
  float distSquared(float x, float y) const
  {
    float distX = this->x - x;
    float distY = this->y - y;
		
    return distX*distX + distY*distY; 
  }

  //内積
  float dot(const Vector2 &other) const
  {
    return this->x*other.x + this->y*other.y;
  }

  //外積
  float cross(const Vector2 &other) const
  {
    return this->x*other.y - this->y*other.x;
  }

  float angleTo(const Vector2 &other) const
  {
    //thisとotherとの角度(otherがthisより反時計回りだと正)
    float ang1 = this->angle();
    float ang2 = other.angle();

    return ang2-ang1;
  }

  float distanceTo(const Vector2 &other) const
  {
    float _x = other.x - this->x;
    float _y = other.y - this->y;
    return sqrt(_x*_x + _y*_y);
  }

  Vector2& operator=(const Vector2 &other)
  {
    this->x = other.x;
    this->y = other.y;
    return *this;
  }

  Vector2& operator-=(const Vector2 &other)
  {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
  }

  Vector2& operator+=(const Vector2 &other)
  {
    this->x += other.x;
    this->y += other.y;
    return *this;
  }

  Vector2& operator*=(const float &scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }

  Vector2 operator+() const
  {
    return *this;
  }

  Vector2 operator-() const
  {
    return Vector2(-x, -y);
  }
  
  Vector2 operator+(const Vector2 &rhs) const
  {
    return Vector2(this->x+rhs.x, this->y+rhs.y);
  }

  Vector2 operator-(const Vector2 &rhs) const
  {
    return Vector2(this->x-rhs.x, this->y-rhs.y);
  }

  Vector2 operator*(const float &k) const
  {
    return Vector2(this->x*k, this->y*k);    
  }

  //friend 関数はただのグローバルだが, ヘッダに直接書いて大丈夫なのか(インクルードガードはあるけど...)
  friend Vector2 operator*(const float &k, const Vector2 &rhs)
  {
    return Vector2(k*rhs.x, k*rhs.y);
  }

  Vector2 operator/(const float &k) const
  {
    return Vector2(this->x/k, this->y/k);
  }

  //画面への出力
  friend ostream& operator<<(ostream& s, const Vector2 &v)
  {
    return s << "(" << v.x << "," << v.y << ")" << endl;
  }
};

#endif
