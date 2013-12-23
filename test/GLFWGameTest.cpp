#include "../include/glfw/GL/freeglut.h"
#include "../include/glfw/GLFWGame.h"
#include "../include/glfw/GLFWInput.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "TestListsScene.h"
#include "XfileModelTestScene.h"
#include "Assets.h"
using namespace std;

//mainで書き換えるのはこのクラスだけ
class TestGame:public GLFWGame
{
public:
  TestGame(GLFWwindow* window)
    :GLFWGame(window)
  {
    Assets::load();    
    scene = getStartScene();
  }

  Scene* getStartScene()
  {
    return new TestListsScene(this);    
  }
};

//------------------------------------------------------------//
//こっから下は基本固定
//------------------------------------------------------------//
static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{  
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  //デバッグ用 F1で強制終了
  if (key == GLFW_KEY_F1 && action == GLFW_PRESS)    exit(2);

  ((GLFWInput*)glfwGetWindowUserPointer(window))->onKey(key, action, mods);
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
  ((GLFWInput*)glfwGetWindowUserPointer(window))->onMouse(button, action, mods);
}

#include <unistd.h>
int main()
{
  glfwSetErrorCallback(error_callback);
  
  if(!glfwInit())
  {
    exit(EXIT_FAILURE);
  }

//  GLFWwindow* window = glfwCreateWindow(640, 480, "example", glfwGetPrimaryMonitor(), NULL);  //フルスクリーン
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
    
    glfwSwapBuffers(window); //絶対必要
    glfwPollEvents();        //絶対必要
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
  
  exit(EXIT_SUCCESS);
}
