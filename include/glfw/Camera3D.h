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
  float frustumNear, frustumFar;
  float frustumFOV;  //視野
  public:

  Camera3D(GLFWwindow *_window, float _frustumNear, float _frustumFar, float _frustumFOV)
    :window(_window)
    ,frustumFar(_frustumFar)
    ,frustumNear(_frustumNear)
    ,frustumFOV(_frustumFOV)
  {
    
    position.x = position.y = position.z = 0;
    look.x = look.y = 0; look.z = 1;
    
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
    gluPerspective(frustumFOV, ratio, frustumNear, frustumFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z,   look.x, look.y, look.z,   0.0, 1.0, 0.0);
  }
  
  Vector3 screenToWorld(const Vector2 &touch) const
  {
    int width, height;           
    glfwGetFramebufferSize(window, &width, &height);

    //view内が-0.5~0.5の範囲になる様変換, 左下(-0.5, -0.5)
    float screenX = (       touch.x - viewportX )/(float)viewportWidth;
    float screenY = (height-touch.y - viewportY )/(float)viewportHeight;
    
    float ratio = viewportWidth/(float)viewportHeight;

    //near平面におけるタッチした場所
    float nearHeight = 2*frustumNear*tan(0.5*frustumFOV*Vector3::TO_RADIANS);
    float nearWidth  = nearHeight*ratio;    
  
    auto cDirection = look - position;
    cDirection.normalize();  //カメラの方向ベクトル

    // カメラが, z方向を向いているのか -zを向いているのかで基準ベクトルが変わる
    float dir_z = cDirection.z > 0 ? 1 : -1;
    
    //右手系だから, +zの方を向くと右が負になる
    //z方向により, x軸の向きも変わる(y軸はカメラは常に, 上を向いている設定なので変わらず
    Vector3 baseDirection = Vector3(0, 0, dir_z);    
    Vector3 nearVec = Vector3( -dir_z*screenX*nearWidth, screenY*nearHeight, dir_z*frustumNear);

    //基準ベクトルとカメラの向いてる方向との角度を求める
    auto rad = acos(cDirection.z*dir_z); //(基準ベクトルはz成分しか持たない, かつどちらも正規化されているので, z成分だけ見ればよい
    auto A   = baseDirection.cross(cDirection).normalize();  //回転軸を計算
    auto P         = nearVec.normalize();
    auto Q         = A.cross(P);
    auto projA_P   = A.dot(P)*A;
    auto perpA_P   = P - A.dot(P)*A;
    auto direction = perpA_P*cos(rad) + Q*sin(rad) + projA_P;

    return direction.normalize();
  }
};
#endif
