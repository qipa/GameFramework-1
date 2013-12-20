#ifndef TEST_SCENE2_H_2013_12_20
#define TEST_SCENE2_H_2013_12_20

#include "../include/glfw/GLFWScene.h"
#include "../include/glfw/GLFW/glfw3.h"
#include "SimpleObjectFactory.h"
#include "../include/glfw/Camera2D.h"

class TestScene2: public GLFWScene
{
  Camera2D *camera;
  Vector2 pos;
public:
  TestScene2(GLFWGame* glfwGame):GLFWScene(glfwGame)
  {
    camera = new Camera2D(glfwGame->getWindow(), 2.0, 2.0);    //ワールド座標におけるカメラの視野の横幅を2.0, 縦幅を2.0と設定
   
    int width, height;
    glfwGetFramebufferSize(glfwGame->getWindow(), &width, &height); //windowサイズを取得
    camera->setViewportWidth(width/2);
    camera->setViewportPosition(width/4, height/2);

    pos.set(0,0);
  }

  ~TestScene2(){}
  
  void update(float deltaTime);
  
  void render(float deltaTime)
  {   
    camera->setViewportAndMatrices();
    
    glColor3f(1.0, 0,0);
    glTranslatef(pos.x, pos.y, 0);
    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glVertex3f( 0.6f, -0.4f, 0.f);
    glVertex3f( 0.0f,  0.6f, 0.f);
    glEnd();
  }
  
  void reshape(int width, int height)
  {
   
  }
  
  void dispose() 
  {
  }
};

#endif
