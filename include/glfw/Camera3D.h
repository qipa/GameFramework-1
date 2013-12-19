#ifndef CAMERA_3D_H_2013_12_18
#define CAMERA_3D_H_2013_12_18

#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "../math/Vector3.h"

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
    glViewport(viewportX-viewportWidth/2, viewportY-viewportHeight/2, viewportWidth, viewportHeight);  

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio = viewportWidth / (float) viewportHeight;
    gluPerspective(frustumFOV, ratio, frustumNear, frustumFar);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z, look.x, look.y, look.z, 0.0, 1.0, 0.0);
  }
  
  Vector3 screenToWorld(const Vector2 &touch) const
  {
    int width, height;           
    glfwGetFramebufferSize(window, &width, &height);
  
    float screenX = (       touch.x - viewportWidth )/(float)viewportWidth;
    float screenY = (height-touch.y - viewportHeight)/(float)viewportHeight;
    float ratio = viewportWidth/(float)viewportHeight;
    
    float nearHeight = frustumNear*tan(M_PI*frustumFOV/180.0);
    float nearWidth  = nearHeight*ratio;
    float farHeight  = frustumFar*tan(M_PI*frustumFOV/180.0);
    float farWidth   = farHeight*ratio;
  
    auto cDirection = look - position;
    cDirection.normalize();  //カメラの方向ベクトル

    Vector3 baseDirection;
    Vector3 nearVec, farVec;
    
    if( cDirection.z < 0)
    {
      //カメラが-zの方面を向いてるときは, 基準ベクトルはv(0,0,-1)を使う
      baseDirection = Vector3(0,0,-1);
      nearVec = Vector3( screenX*nearWidth, screenY*nearHeight, -frustumNear);
      farVec  = Vector3( screenX*farWidth , screenY*farHeight , -frustumFar);
    } else
    {
      //カメラが+zの方面を向いてるときは, 基準ベクトルはv(0,0,+1)を使う
      baseDirection = Vector3(0,0,+1);
      //右手系だから, +zの方を向くと右が負になる
      nearVec = Vector3( -screenX*nearWidth, screenY*nearHeight, frustumNear);
      farVec  = Vector3( -screenX*farWidth , screenY*farHeight , frustumFar);
    }

    //カメラが実際に向いている方向にあわせて回転させる
    auto rad = baseDirection.angleTo(cDirection);    //回転角度  
    auto A = baseDirection.cross(cDirection).normalize();        //回転軸を計算

    auto P = (farVec-nearVec).normalize();
    auto Q = A.cross(P);
    auto projA_P = A.dot(P)*A;
    auto perpA_P = P - A.dot(P)*A;
    auto direction = perpA_P*cos(rad) + Q*sin(rad) + projA_P;
  
    return direction.normalize();
  }
};
#endif
