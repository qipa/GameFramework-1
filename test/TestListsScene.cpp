#include "TestListsScene.h"
#include "SpriteBatcherTestScene.h"
#include "Camera2DTestScene.h"
#include "Camera3DTestScene.h"
#include "XfileModelTestScene.h"
#include "Assets.h"
#include <syukatsu/GL/freeglut.h>
#include <string>
#include <FTGL/ftgl.h>
using namespace std;

void TestListsScene::update(float deltaTime)
{
  auto keyEvents = syukatsuGame->getInput()->getKeyEvents();
  for(auto event : keyEvents)
  {
    if(event->action != GLFW_PRESS) continue;
    switch(event->keyCode)
    {
    case GLFW_KEY_A:
      syukatsuGame->setScene(new SpriteBatcherTestScene(syukatsuGame));
      return;
    case GLFW_KEY_B:
      syukatsuGame->setScene(new Camera2DTestScene(syukatsuGame));
      return;
    case GLFW_KEY_C:
      syukatsuGame->setScene(new Camera3DTestScene(syukatsuGame));
      return;
    case GLFW_KEY_D:
      syukatsuGame->setScene(new XfileModelTestScene(syukatsuGame));
      return;
    default:
      break;
    }
  }    
}

void TestListsScene::render(float deltaTime)
{
  camera->setViewportAndMatrices();
  glPushAttrib(GL_COLOR);  
  glColor3d(1,1,1);

  glPushMatrix();
  glTranslatef(-WIDTH/2, HEIGHT/3, 0);
  glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
  Assets::mincho->render("こんにちわ");
  glPopMatrix();  
  glRasterPos2f(-WIDTH/2,HEIGHT/3);      
  glColor3d(1,1,1);  

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
  glPopAttrib();
  
}

    
  


