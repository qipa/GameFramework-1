#ifndef CAMERA_2D_H_2013_12_18
#define CAMERA_2D_H_2013_12_18

#include "GLFW/glfw3.h"
#include "../math/Vector2.h"

class Camera2D
{  
  GLFWwindow *window; //glfwの関数に渡す為constにできない

  //画面上での位置, サイズ
  int viewportX;
  int viewportY;
  int viewportWidth;  //横幅
  int viewportHeight; //縦幅

  //ワールド座標におけるカメラの位置と視野幅,高さ
  Vector2 position;
  float frustumWidth;
  float frustumHeight;  
public:
Camera2D(GLFWwindow *_window, float _frustumWidth, float _frustumHeight)
  :window(_window)
    ,frustumWidth(_frustumWidth)
    ,frustumHeight(_frustumHeight)
  {
    position.x = 0;
    position.y = 0;
    //最初は, 画面いっぱいに描画する設定
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    viewportX = viewportWidth/2;
    viewportY = viewportHeight/2;
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
    
    glOrtho(position.x-frustumWidth/2,
            position.x+frustumWidth/2,
            position.y-frustumHeight/2,
            position.y+frustumHeight/2, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  
  Vector2 screenToWorld(const Vector2 &touch) const
  {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);  //todo 毎回呼び出したら遅い?

    float _x = (             touch.x - viewportX)/(float)viewportWidth *frustumWidth  - position.x;
    float _y = (windowHeight-touch.y - viewportY)/(float)viewportHeight*frustumHeight - position.y;

    return Vector2(_x, _y);
  }
};

#endif
