#include "TestListsScene.h"
#include "SpriteBatcherTestScene.h"
#include "Camera2DTestScene.h"
#include "Camera3DTestScene.h"
#include "XfileModelTestScene.h"
#include <glfw/GL/freeglut.h>
#include <string>
using namespace std;

void TestListsScene::update(float deltaTime)
{
  auto keyEvents = glfwGame->getInput()->getKeyEvents();
  for(auto event : keyEvents)
  {
    if(event->action != GLFW_PRESS) continue;
    switch(event->keyCode)
    {
    case GLFW_KEY_A:
      glfwGame->setScene(new SpriteBatcherTestScene(glfwGame));
      return;
    case GLFW_KEY_B:
      glfwGame->setScene(new Camera2DTestScene(glfwGame));
      return;
    case GLFW_KEY_C:
      glfwGame->setScene(new Camera3DTestScene(glfwGame));
      return;
    case GLFW_KEY_D:
      glfwGame->setScene(new XfileModelTestScene(glfwGame));
      return;
    default:
      break;
    }
  }    
}

void TestListsScene::render(float deltaTime)
{
  camera->setViewportAndMatrices();
    
  glRasterPos2f(-WIDTH/2,HEIGHT/3);
  string scenes[] = {"A : SpriteBatcherTest",
                     "B : Camera2DTest",
                     "C : Camera3DTest",
                     "D : XFileModelTest"};
  int i=0;    
  for(auto str : scenes)
  {
    glRasterPos2f(-WIDTH/2, HEIGHT*0.4-HEIGHT/10*i++);
    for(int i=0; i<str.size(); i++)
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);    
  }
}

    
  


