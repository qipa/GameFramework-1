#include <Camera3D.h>

Camera3D::Camera3D(GLFWwindow *_window, float _frustumNear, float _frustumFar, float _frustumFOVY)
  :window(_window)
  ,position(Vector3(0,0,0))
  ,look(Vector3(0,0,1))
  ,up(Vector3(0,1,0))
  ,frustumNear(_frustumNear)
  ,frustumFar(_frustumFar)
  ,frustumFOVY(_frustumFOVY)
{
  glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);  //最初は, 画面いっぱいに描画する設定
  viewportX = viewportWidth/2;
  viewportY = viewportHeight/2;
}
  
Camera3D::Camera3D(GLFWwindow *_window, Vector3 _position, Vector3 _look, float _frustumNear, float _frustumFar, float _frustumFOVY)
  :window(_window)
  ,position(_position)
  ,look(_look)
  ,up(Vector3(0,1,0))
  ,frustumNear(_frustumNear)
  ,frustumFar(_frustumFar)
  ,frustumFOVY(_frustumFOVY)
{   
  glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight); //最初は, 画面いっぱいに描画する設定
  viewportX = viewportWidth/2;
  viewportY = viewportHeight/2;
}

void Camera3D::setViewportAndMatrices() const
{    
  glViewport(viewportX-viewportWidth/2, viewportY-viewportHeight/2, viewportWidth, viewportHeight);  

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  
  perspective();    
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  lookAt();
}
  
Vector3 Camera3D::screenToWorld(const Vector2 &touch) const
{
  int width, height;           
  glfwGetFramebufferSize(window, &width, &height);

  //view内が-0.5~0.5の範囲になる様変換, 左下(-0.5, -0.5)
  float screenX = (       touch.x - viewportX )/(float)viewportWidth;
  float screenY = (height-touch.y - viewportY )/(float)viewportHeight;
    
  float ratio = viewportWidth/(float)viewportHeight;

  //near平面における画面のサイズ
  float nearHeight = 2*frustumNear*tan(0.5*frustumFOVY*Vector3::TO_RADIANS);
  float nearWidth  = nearHeight*ratio;    
    
  auto axisZ = look - position;                  //カメラを中心としたZ軸
  axisZ.normalize();
  Vector3 axisY = up - axisZ.dot(up)*axisZ; //screenYに対応 Y軸
  axisY.normalize();
  Vector3 axisX = axisZ.cross(axisY);       //screenXに対応 X軸
  axisX.normalize();

  return axisY*screenY*nearHeight + axisX*screenX*nearWidth + axisZ*frustumNear;
}

void Camera3D::perspective() const
{
  double ratio = viewportWidth/(float)viewportHeight;  
  double xmin, xmax, ymin, ymax;
  ymax = frustumNear * tan(frustumFOVY * M_PI / 360.0);
  ymin = -ymax;
  xmin = ymin * ratio;
  xmax = ymax * ratio;
  glFrustum(xmin, xmax, ymin, ymax, frustumNear, frustumFar);
}
  
void Camera3D::lookAt() const
{
  Vector3 forward = look - position;
  forward.normalize();
    
  Vector3 up = this->up;
  up.normalize();

  Vector3 side = forward.cross(up);
  up = side.cross(forward);

  GLfloat m[4][4] = {{1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1} };
  
  m[0][0] = side.x;
  m[1][0] = side.y;
  m[2][0] = side.z;

  m[0][1] = up.x;
  m[1][1] = up.y;
  m[2][1] = up.z;

  m[0][2] = -forward.x;
  m[1][2] = -forward.y;
  m[2][2] = -forward.z;

  glMultMatrixf(&m[0][0]);
  glTranslated(-position.x, -position.y, -position.z);
}
