#include "../include/glfw/GLFWGame.h"
#include "../include/glfw/GLFWScene.h"
#include "../include/glfw/Camera2D.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

static bool flag = false;


class TestScene2 :public GLFWScene
{
  Camera2D *camera2;
public:
  TestScene2(GLFWGame* glfwGame):GLFWScene(glfwGame)
  {

    camera2 = new Camera2D(glfwGame->getWindow(), 2.0, 2.0);    //ワールド座標におけるカメラの視野の横幅を2.0, 縦幅を2.0と設定
    
    int width, height;
    glfwGetFramebufferSize(glfwGame->getWindow(), &width, &height); //windowサイズを取得

    camera2->setViewportWidth(width/4);
    camera2->setViewportHeight(height/4);
    camera2->setViewportPosition(width/4*3, height/2); //viewの中心位置

  }

  ~TestScene2(){}
  void update(float deltaTime);

  
  void render(float deltaTime)
  {   
    glClear(GL_COLOR_BUFFER_BIT);

    camera2->setViewportAndMatrices();
    glColor3f(0.0, 1,0);
    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
  }
  
  void reshape(int width, int height)
  {
   
  }
  
  void dispose() 
  {
  }
};

class TestScene1: public GLFWScene
{
  Camera2D *camera1;

public:
  TestScene1(GLFWGame* glfwGame):GLFWScene(glfwGame)
  {
    camera1 = new Camera2D(glfwGame->getWindow(), 2.0, 2.0);    //ワールド座標におけるカメラの視野の横幅を2.0, 縦幅を2.0と設定

    int width, height;
    glfwGetFramebufferSize(glfwGame->getWindow(), &width, &height); //windowサイズを取得    
    
    //画面の1/4の大きさに
    camera1->setViewportWidth(width/4);
    camera1->setViewportHeight(height/4);
    camera1->setViewportPosition(width/4, height/2); //viewの中心位置(画面上での)
  }

  ~TestScene1(){}
  
  void update(float deltaTime);
  
  void render(float deltaTime)
  {   
    glClear(GL_COLOR_BUFFER_BIT);
    camera1->setViewportAndMatrices();
    glColor3f(1.0, 0,0);
    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
  }
  
  void reshape(int width, int height)
  {
   
  }
  
  void dispose() 
  {
  }
};

//循環してるクラス関係を1つのファイルで表す為に,こんな書き方してる
//TestScene2でのupdate 
void TestScene2::update(float deltaTime)
{
  if(!flag)
  {
    glfwGame->setScene(new TestScene1(glfwGame));
  }
}

void TestScene1::update(float deltaTime)
{
  if(flag)
  {
    glfwGame->setScene(new TestScene2(glfwGame));
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
  if(action == GLFW_PRESS)
    flag = !flag;
  
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  
    glfwSetWindowShouldClose(window, GL_TRUE);

  //デバッグ用 F1で強制終了
  if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    exit(2);

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
  glfwSetWindowUserPointer(window, game);
  
  glfwSetKeyCallback(window, key_callback);

  glClearColor(0.0, 0.0, 0.0, 1.0);

  while(!glfwWindowShouldClose(window))
  {
    game->loop();
    glfwSwapBuffers(window);
    glfwPollEvents(); //絶対必要
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
  
  exit(EXIT_SUCCESS);
}
