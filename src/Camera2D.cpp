#include <Camera2D.h>

Camera2D::Camera2D(GLFWwindow *_window, float _frustumWidth, float _frustumHeight)
  :window(_window)
  ,frustumWidth(_frustumWidth)
  ,frustumHeight(_frustumHeight)
{
  position.x = 0;
  position.y = 0;

  glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);  //最初は, 画面いっぱいに描画する設定
  viewportX = viewportWidth/2;
  viewportY = viewportHeight/2;
}
  
void Camera2D::setViewportAndMatrices() const
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
  
Vector2 Camera2D::screenToWorld(const Vector2 &touch) const
{
  int windowWidth, windowHeight;
  glfwGetFramebufferSize(window, &windowWidth, &windowHeight);  //todo 毎回呼び出したら遅い?

  float _x = (             touch.x - viewportX)/(float)viewportWidth *frustumWidth  - position.x;
  float _y = (windowHeight-touch.y - viewportY)/(float)viewportHeight*frustumHeight - position.y;

  return Vector2(_x, _y);
}
