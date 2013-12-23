#ifndef CAMERA_3D_H_2013_12_18
#define CAMERA_3D_H_2013_12_18

#include "GL/freeglut.h"
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
  float frustumFOV;  //視野
  public:

  Camera3D(GLFWwindow *_window, float _frustumNear, float _frustumFar, float _frustumFOV)
    :window(_window)
    ,frustumFar(_frustumFar)
    ,frustumNear(_frustumNear)
    ,frustumFOV(_frustumFOV)
  {
    position.set(0,0,0);
        look.set(0,0,1);
          up.set(0,1,0);
    //最初は, 画面いっぱいに描画する設定
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    viewportX = viewportWidth/2;
    viewportY = viewportHeight/2;
  }
  
  Camera3D(GLFWwindow *_window, Vector3 _position, Vector3 _look, float _frustumNear, float _frustumFar, float _frustumFOV)
    :window(_window)
    ,frustumFar(_frustumFar)
    ,frustumNear(_frustumNear)
    ,frustumFOV(_frustumFOV)
    ,position(_position)
    ,look(_look)
  {
    up.set(0,1,0);
    //最初は, 画面いっぱいに描画する設定
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    viewportX = viewportWidth/2;
    viewportY = viewportHeight/2;
  }

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

  void setViewportAndMatrices() const
  {    
    float ratio = viewportWidth/(float)viewportHeight;

    glViewport(viewportX-viewportWidth/2, viewportY-viewportHeight/2, viewportWidth, viewportHeight);  

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //GLKMatrix4MakePerspective(frustumFOV, ratio, frustumNear, frustumFar);
    gluPerspective(frustumFOV, ratio, frustumNear, frustumFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //GLKMatrix4MakeLookAt(position.x, position.y, position.z,   look.x, look.y, look.z,   up.x, up.y, up.z);
    gluLookAt(position.x, position.y, position.z,   look.x, look.y, look.z,   up.x, up.y, up.z);
  }
  
  Vector3 screenToWorld(const Vector2 &touch) const
  {
    int width, height;           
    glfwGetFramebufferSize(window, &width, &height);

    //view内が-0.5~0.5の範囲になる様変換, 左下(-0.5, -0.5)
    float screenX = (       touch.x - viewportX )/(float)viewportWidth;
    float screenY = (height-touch.y - viewportY )/(float)viewportHeight;
    
    float ratio = viewportWidth/(float)viewportHeight;

    //near平面における画面のサイズ
    float nearHeight = 2*frustumNear*tan(0.5*frustumFOV*Vector3::TO_RADIANS);
    float nearWidth  = nearHeight*ratio;    
    
    auto cDirection = look - position;   //カメラの方向ベクトル(z軸に対応)    
    cDirection.normalize();    
    Vector3 axisY = up - cDirection.dot(up)*cDirection; //screenYに対応
    axisY.normalize();
    Vector3 axisX = cDirection.cross(axisY); //screenXに対応
    axisX.normalize();
    
    return axisY*screenY*nearHeight + axisX*screenX*nearWidth + cDirection*frustumNear;
  }
};
#endif
