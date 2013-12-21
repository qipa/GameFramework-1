#include "Camera2DTestScene.h"
#include "TestListsScene.h"
#include "../include/glfw/GLFW/glfw3.h"
#include "SimpleObjectFactory.h"

Camera2DTestScene::Camera2DTestScene(GLFWGame* glfwGame)
  :GLFWScene(glfwGame)
{
  camera = new Camera2D(glfwGame->getWindow(), 2.0, 2.0);    //ワールド座標におけるカメラの視野の横幅を2.0, 縦幅を2.0と設定
  
  int width, height;
  glfwGetFramebufferSize(glfwGame->getWindow(), &width, &height); //windowサイズを取得
  camera->setViewportWidth(width/2);
  camera->setViewportPosition(width/4, height/2);

  pos.set(0,0);
}

void Camera2DTestScene::render(float deltaTime)
{
  glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);
  
  camera->setViewportAndMatrices();  
  glTranslatef(pos.x, pos.y, 0);
  glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
  glBegin(GL_TRIANGLES);
  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(-0.6f, -0.4f, 0.f);
  glVertex3f( 0.6f, -0.4f, 0.f);
  glVertex3f( 0.0f,  0.6f, 0.f);
  glEnd();
  
  glPopAttrib();  
}

void Camera2DTestScene::update(float deltaTime)
{
  auto keyEvents = glfwGame->getInput()->getKeyEvents();
  
  for (auto event : keyEvents)
  {
    if(event->action != GLFW_PRESS || event->keyCode != GLFW_KEY_ENTER)
      continue;    
    glfwGame->setScene(new TestListsScene(glfwGame));   
    return;
  }

  auto mouse = glfwGame->getInput()->getMouseEvent();
  auto touch = Vector2();
  touch.set(mouse->x, mouse->y);
  pos = camera->screenToWorld(touch);  
}


