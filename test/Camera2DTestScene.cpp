#include "Camera2DTestScene.h"
#include "TestListsScene.h"
#include "SimpleObjectFactory.h"
#include <syukatsu/GLFW/glfw3.h>

Camera2DTestScene::Camera2DTestScene(SyukatsuGame* game)
  :SyukatsuScene(game)
  ,WIDTH(4.8)
  ,HEIGHT(3.2)
{
  camera  = new Camera2D(syukatsuGame->getWindow(), WIDTH, HEIGHT);    //ワールド座標におけるカメラの視野の横幅を2.0, 縦幅を2.0と設定
  camera2 = new Camera2D(syukatsuGame->getWindow(), WIDTH, HEIGHT);    //ワールド座標におけるカメラの視野の横幅を2.0, 縦幅を2.0と設定
  
  int width, height;
  glfwGetFramebufferSize(syukatsuGame->getWindow(), &width, &height); //windowサイズを取得

  //左半分
  camera->setViewportWidth(width/2);
  camera->setViewportPosition(width/4, height/2);

  //右半分
  camera2->setViewportWidth(width/2);
  camera2->setViewportPosition(width/4*3, height/2);
  pos.set(0,0);
  pos2.set(0,0);
}

void Camera2DTestScene::render(float deltaTime)
{
  glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);

  //camera1->左半分に描画
  camera->setViewportAndMatrices();
  glPushMatrix();  
  glTranslatef(pos.x, pos.y, 0);
  glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
  glBegin(GL_TRIANGLES);
  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(-0.6f, -0.4f, 0.f);
  glVertex3f( 0.6f, -0.4f, 0.f);
  glVertex3f( 0.0f,  0.6f, 0.f);
  glEnd();
  glPopMatrix();

  //camera2->右半分に描画
  camera2->setViewportAndMatrices();
  
  glPushMatrix();  
  glTranslatef(pos2.x, pos2.y, 0);
  glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);  //時間で回転させてるだけ
  glBegin(GL_TRIANGLES);
  glColor3f(0.f, 0.f, 1.f);
  glVertex3f(-0.6f, -0.4f, 0.f);
  glVertex3f( 0.6f, -0.4f, 0.f);
  glVertex3f( 0.0f,  0.6f, 0.f);
  glEnd();
  glPopMatrix();
  
  glPopAttrib();  
}

void Camera2DTestScene::update(float deltaTime)
{
  auto keyEvents = game->getInput()->getKeyEvents();
  
  for (auto event : keyEvents)
  {
    if(event->action != GLFW_PRESS || event->keyCode != GLFW_KEY_ENTER)
      continue;    
    syukatsuGame->setScene(new TestListsScene(syukatsuGame));   
    return;
  }

  auto mouse = syukatsuGame->getInput()->getMouseEvent();
  auto touch = Vector2();
  touch.set(mouse->x, mouse->y);
  pos = camera->screenToWorld(touch);  //camera1から見た,マウスの場所
  pos2= camera2->screenToWorld(touch); //camera2から見た,マウスの場所
  
}


