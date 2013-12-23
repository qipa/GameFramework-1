#ifndef CAMERA_3D_H_2013_12_18
#define CAMERA_3D_H_2013_12_18

#include "GLFW/glfw3.h"
#include "../math/Vector3.h"
#include <iostream>

using namespace std;
class Camera3D
{
  GLFWwindow *window; //glfwの関数に渡す為constにできない

  //画面上での位置, サイズ
  int viewportX;
  int viewportY;
  int viewportWidth;  //横幅
  int viewportHeight; //縦幅

  //ワールド座標におけるカメラの位置と視野幅,高さ
  Vector3 position;
  Vector3 look;
  Vector3 up; //カメラの上の方向 (基本は(0,1,0))
  float frustumNear, frustumFar;
  float frustumFOVY;  //視野
public:
  Camera3D(GLFWwindow *_window, float _frustumNear, float _frustumFar, float _frustumFOVY);  
  Camera3D(GLFWwindow *_window, Vector3 _position, Vector3 _look, float _frustumNear, float _frustumFar, float _frustumFOVY);
  
  void setViewportAndMatrices() const;  
  
  Vector3 screenToWorld(const Vector2 &touch) const;

  void perspective() const;
  
  void lookAt() const;

  Vector3 getPosition() const
  {
    return position;
  }

  Vector3 getLook() const
  {
    return look;
  }
  
  void setPosition(const Vector3 &_position)
  {
    position = _position;
  }

  void setLook(const Vector3 &_look)
  {
    look = _look;
  }
  
  //:画面の場所, サイズを変える  
  void setViewportWidth(const float &width)
  {
    viewportWidth = width;
  }
  
  void setViewportHeight(const float &height)
  {
    viewportHeight = height;
  }
  
  void setViewportPosition(const int &x, const int &y)
  {
    viewportX = x;
    viewportY = y;
  }
};
#endif
