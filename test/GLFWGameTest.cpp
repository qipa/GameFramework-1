#include "../include/glfw/GL/freeglut.h"
#include "../include/glfw/GLFWGame.h"
#include "../include/glfw/GLFWInput.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "TestScene1.h"
#include "TestScene2.h"
using namespace std;

//循環してるクラス関係を1つのファイルで表す為に,updateをこっちに書いてる
//TestScene1でのupdate 
void TestScene1::update(float deltaTime)
{
  auto keyEvents = glfwGame->getInput()->getKeyEvents();
  for (auto event : keyEvents)
  { 
    if(event->action != GLFW_PRESS)
      continue;

    if(event->keyCode == GLFW_KEY_ENTER)
    {
      glfwGame->setScene(new TestScene2(glfwGame));
      return;
    }
  }

  auto mouse = glfwGame->getInput()->getMouseEvent();
  auto touch = Vector2();

  touch.set(mouse->x, mouse->y);
  Vector3 direction = camera->screenToWorld(touch);
  pos = camera->getPosition() + 100*direction;  
}

//TestScene2でのupdate
void TestScene2::update(float deltaTime)
{
  auto keyEvents = glfwGame->getInput()->getKeyEvents();
  
  for (auto event : keyEvents)
  {
    if(event->action != GLFW_PRESS || event->keyCode != GLFW_KEY_RIGHT)
      continue;    
    glfwGame->setScene(new TestScene1(glfwGame));   
    return;
  }

  auto mouse = glfwGame->getInput()->getMouseEvent();
  auto touch = Vector2();
  if(mouse->action == GLFW_PRESS)
  {
    touch.set(mouse->x, mouse->y);   
    pos = camera->screenToWorld(touch);
  }
}


class TestGame:public GLFWGame
{
public:
  TestGame(GLFWwindow* window)
    :GLFWGame(window)
  {
    scene = getStartScene();
  }

  Scene* getStartScene()
  {
    return new TestScene1(this);
  }
};

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{  
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  
    glfwSetWindowShouldClose(window, GL_TRUE);

  //デバッグ用 F1で強制終了
  if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    exit(2);

  ((GLFWInput*)glfwGetWindowUserPointer(window))->onKey(key, action, mods);
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
  ((GLFWInput*)glfwGetWindowUserPointer(window))->onMouse(button, action, mods);
}


static void cursor_callback(GLFWwindow *window, double x, double y)
{
// ((GLFWInput*)glfwGetWindowUserPointer(window))->onCursor(x, y);
}

#include <unistd.h>
int main()
{
  glfwSetErrorCallback(error_callback);
  
  if(!glfwInit())
  {
    exit(EXIT_FAILURE);
  }

//  GLFWwindow* window = glfwCreateWindow(640, 480, "example", glfwGetPrimaryMonitor(), NULL);
  GLFWwindow* window = glfwCreateWindow(640, 480, "example", NULL, NULL);
  if(!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwMakeContextCurrent(window);
  TestGame* game = new TestGame(window);
  
  glfwSetWindowUserPointer(window, game->getInput()); //このwindowにコールバック用にインプットを登録
  
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_callback);
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  
  while(!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    game->loop();
/*
    int width, height;           
    glfwGetFramebufferSize(window, &width, &height);

    float ratio = width / (float) height;

    glViewport(0, 0, width, height);  

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -10, 0,    0, 0, 0,   0.0, 1.0, 0.0);
    
    drawAxis();
*/  
    glfwSwapBuffers(window); //絶対必要
    glfwPollEvents();        //絶対必要
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
  
  exit(EXIT_SUCCESS);
}
