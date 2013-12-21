#ifndef COLOR_TEST_SCENE_H_12_21
#define COLOR_TEST_SCENE_H_12_21

#include "../include/glfw/GLFWScene.h"
#include "../include/glfw/Camera2D.h"

#include <cmath>
class ColorTestScene:public GLFWScene
{
Camera2D *camera;
public:
  ColorTestScene(GLFWGame *glfwGame):GLFWScene(glfwGame)
  {
camera = new Camera2D(glfwGame->getWindow(), 2, 2);

    
  }

void getColor(float phi, float &r, float &g, float &b)
{
  double range = 0.9; //波の振幅

  double ab_phi = phi < 0 ? -phi : phi;

  double a = ab_phi < range ? (ab_phi <  range/3.0 ? 3.0/range*ab_phi : (-3.0/4.0/range*ab_phi+1.25) ) : 0.5;
  
  r = phi > 0 ? a:0;
  b = phi < 0 ? a:0;
  g = min(1.0, max(0.0, -3*ab_phi+2));
}

  void update(float deltaTime)
  {
  }

  void render(float deltaTime)
  {
camera->setViewportAndMatrices();

glTranslatef(-1.0,0,0);

for(float A=0; A < 1; A+=0.005)
{
float r, g,b;
getColor(2*A-1, r, g, b);
glColor3f(r,g,b);
glBegin(GL_POLYGON);
  glVertex3f(-0.01f,  1.f,  0.f);
  glVertex3f(-0.01f, -1.0f, 0.f);
  glVertex3f( 0.01f, -1.0f, 0.f);
  glVertex3f( 0.01f,  1.0f, 0.f);
glEnd();
glTranslatef(0.01,0,0);
}

  }

  void reshape(int width, int height) 
  {
  }

  void dispose()
  {
  }
  

};

#endif
