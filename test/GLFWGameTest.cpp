#include "../include/glfw/GLFWGame.h"
#include "../include/glfw/GLFWScene.h"
#include "../include/glfw/Camera2D.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

class TestScene: public GLFWScene
{
  Camera2D *camera;
public:
  TestScene(GLFWGame* game):GLFWScene(game)
  {
    camera = new Camera2D(game->getWindow(), 4.8, 3.2);
  }

  ~TestScene(){}
  void update(float deltaTime)
  {
  }
  
  void render(float deltaTime)
  {
    cout << "TestScene render" << endl;
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    camera->setViewportAndMatrices();
    glColor4f(1, 0, 0,1);
    glBegin(GL_POLYGON);
    glVertex2d(1.0, 0.0);
    glVertex2d(2.0, 0.0);
    glVertex2d(1.5, 1.0);
    glVertex2d(1.5, 1.5);
    glEnd();
  }
  
  void reshape(int width, int height)
  {
   
  }
  
  void dispose() 
  {
  }
};

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
    return new TestScene(this);
  }
};

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  cout << "key pushed" << endl;
  
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  
    glfwSetWindowShouldClose(window, GL_TRUE);

  //デバッグ用 F1で強制終了
  if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    exit(2);

}

int main()
{
  glfwSetErrorCallback(error_callback);
  
  if(!glfwInit())
  {
    exit(EXIT_FAILURE);
  }

//  GLFWwindow* window = glfwCreateWindow(640, 480, "example", glfwGetPrimaryMonitor(), NULL);
  GLFWwindow* window = glfwCreateWindow(640, 480, "example", NULL, NULL);
  glfwMakeContextCurrent(window);
  TestGame* game = new TestGame(window);
  glfwSetWindowUserPointer(window, game);
  glfwSetKeyCallback(window, key_callback);

  glClearColor(0.0, 0.0, 0.0, 1.0);

  while(!glfwWindowShouldClose(window))
  {
    game->loop();
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
  
  exit(EXIT_SUCCESS);
}
