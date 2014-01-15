#include "Camera3DTestScene.h"
#include "TestListsScene.h"
#include "Assets.h"
#include <syukatsu/GL/freeglut.h>
#include <string>
using namespace std;

Camera3DTestScene::Camera3DTestScene(SyukatsuGame* game)
  :SyukatsuScene(game)
  ,cellSize(10)
  ,cellNum(10)
{
  camera = new Camera3D(syukatsuGame->getWindow(), 1, 1000, 45); //near, far, 視野角
  camera->setPosition( Vector3(100, 0, 0) );
  camera->setLook(Vector3(0,0,0));

  camera2 = new Camera2D(syukatsuGame->getWindow(), Camera3DTestScene::WIDTH, Camera3DTestScene::HEIGHT);
  //2D画面の位置  
  int width, height;
  glfwGetFramebufferSize(syukatsuGame->getWindow(), &width, &height);
  camera2->setViewportWidth(width/4);
  camera2->setViewportHeight(height/4);
  camera2->setViewportPosition(width/8, height/8*7);    
  
  theta = phi = 0;
  pos.set(0,0,0);
}

void Camera3DTestScene::update(float deltaTime)
{
  auto keyEvents = game->getInput()->getKeyEvents();
  const float speed = 2*M_PI;
  
  for (auto event : keyEvents)
  { 
    switch(event->keyCode)
    {
    case GLFW_KEY_ENTER:
      if(event->action != GLFW_PRESS)  continue;
      syukatsuGame->setScene(new TestListsScene(syukatsuGame));
      return;
    case GLFW_KEY_LEFT:
      theta += speed*deltaTime;
      if(theta<0) theta+=2*M_PI;
      break;
    case GLFW_KEY_RIGHT:
      theta -= speed*deltaTime;
      if(theta>2*M_PI) theta-=2*M_PI;
      break;
    case GLFW_KEY_UP:
      phi = min(phi+speed*deltaTime, (float)M_PI/3.8f);
      break;
    case GLFW_KEY_DOWN:
      phi = min(phi-speed*deltaTime, 0.0f);
      break;
    case GLFW_KEY_T:
      theta = 0;
      break;
    case GLFW_KEY_P:
      phi = 0;
      break;
    }
  }  
  float R = 100;
  camera->setPosition(Vector3(R*cos(phi)*cos(theta), R*sin(phi), R*cos(phi)*sin(theta)));

  auto mouse = game->getInput()->getMouseEvent();
  auto touch = Vector2();

  touch.set(mouse->x, mouse->y);
  Vector3 direction = camera->screenToWorld(touch);
  pos = camera->getPosition() + 100*direction;
}

void Camera3DTestScene::render(float deltaTime)
{
  camera->setViewportAndMatrices();
  
  glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
  glEnable(GL_LIGHTING);    
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
  glEnable(GL_DEPTH_TEST);
    
  GLfloat color[]     = {    1.0,    1.0,    1.0, 1.0 };
  GLfloat lightpos1[] = {  200.0, -200.0, -200.0, 1.0 };
  GLfloat lightpos2[] = { -200.0,  200.0,  200.0, 1.0 };
  GLfloat lightpos3[] = { -200.0, -200.0, -200.0, 1.0 };
  GLfloat lightpos4[] = {  200.0,  200.0,  200.0, 1.0 };
    
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
  glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
    
  glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, color);
  glLightfv(GL_LIGHT3, GL_POSITION, lightpos4);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, color);

  glColor3f(1,1,1);
  drawAxis();

  
  glPushMatrix();
  glTranslatef(pos.x, pos.y, pos.z);
  glRotatef((float) glfwGetTime() * 50.f, 0,1,0);
  glutSolidCube(5);    
  glPopMatrix();
  glPopAttrib();

  glPushMatrix();
  Assets::mincho->setSize(5);

  for(int i=0; i<10; i++)
  {
    glPushMatrix();    
    glTranslatef(5*i, 5, 5*i);
    glRotatef(30, 0.f, 1.f, 0.f);
    Assets::mincho->render("こんにちわ");
    glPopMatrix();    
  }  
  glPopMatrix();

  camera2->setViewportAndMatrices();
  glRasterPos2f(-Camera3DTestScene::WIDTH/2,Camera3DTestScene::HEIGHT/3);
}

