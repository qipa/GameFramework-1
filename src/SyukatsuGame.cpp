#include <GLFW/glfw3.h>
#include <SyukatsuGame.h>
#include <SyukatsuInput.h>
#include <SyukatsuFileIO.h>
#include <SyukatsuAudio.h>
#include <SyukatsuScene.h>
#include <iostream>

namespace
{
  //GLFW用のコールバック設定
  void error_callback(int error, const char* description)
  {
    fputs(description, stderr);
  }
  
  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    SyukatsuGame*   game = (SyukatsuGame*)glfwGetWindowUserPointer(window);
    SyukatsuInput* input = (SyukatsuInput*)game->getInput();
    input->onKey(key, action, mods);
  }
  
  void mouseCallback(GLFWwindow* window, int button, int action, int mods)
  {
    SyukatsuGame*   game = (SyukatsuGame*)glfwGetWindowUserPointer(window);
    SyukatsuInput* input = (SyukatsuInput*)game->getInput();
    input->onMouse(button, action, mods);
  }
  
  void scrollCallback(GLFWwindow* window, double offsetX, double offsetY)
  {
    SyukatsuGame*   game = (SyukatsuGame*)glfwGetWindowUserPointer(window);
    SyukatsuInput* input = (SyukatsuInput*)game->getInput();
    input->onScroll(offsetX, offsetY);
  }

  void resize_callback(GLFWwindow* window, int width, int height)
  {
    SyukatsuGame* game = (SyukatsuGame*)glfwGetWindowUserPointer(window);
    auto scene = game->getCurrentScene();
    scene->reshape(width, height);
  }

  GLFWwindow* getWindow(std::string title, int width, int height, bool is_fullscreen)
  {
    
  }
}

SyukatsuGame::SyukatsuGame
(std::string window_title, int window_width, int window_height, bool is_fullscreen)
  :scene(NULL), nextScene(NULL)
{ 
  glfwSetErrorCallback(error_callback);

  if(!glfwInit())
  {
    exit(EXIT_FAILURE);
  }

  elapsedTime[0] = glfwGetTime();
  elapsedTime[1] = glfwGetTime();

  auto _monitor = is_fullscreen ? glfwGetPrimaryMonitor() : NULL;
  window = glfwCreateWindow(window_width, window_height, window_title.c_str(), _monitor, NULL);
  
  if(!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwMakeContextCurrent(window);
  glfwSetWindowUserPointer(window, this); //このwindowにコールバック用にインプットを登録
  
  input = new SyukatsuInput(window);
  fileIO = NULL;
  audio  = NULL;
  
  glfwSetKeyCallback(window, keyCallback);
  glfwSetMouseButtonCallback(window, mouseCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetFramebufferSizeCallback (window, resize_callback);
};

SyukatsuGame::~SyukatsuGame()
{
  //todo  
  delete input;
  /*
  delete fileIO;
  delete audio;
  */
  scene->dispose();  
  delete scene;
};
  
bool SyukatsuGame::setScene(Scene *scene)
{
  //NULLを指定しようとしたらfalse
  if(scene == NULL)
  {
    return false;
  }

  //既に別の所から次のシーンを指定されていたら, 除外する
  if(this->nextScene != NULL)
  {
    delete scene; //削除しておく
    return false;
  }

  this->nextScene = scene;  //次のシーンの決定
  return true;
}

void SyukatsuGame::loop()
{
  while(!glfwWindowShouldClose(window))
  {
    float deltaTime = elapsedTime[1] - elapsedTime[0];
    elapsedTime[0] = glfwGetTime();
    input->update();  
    scene->update(deltaTime);
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    scene->render(deltaTime);
  
    replaceScene();
    glFlush();  
    glfwSwapBuffers(window); //絶対必要
    glfwPollEvents();        //絶対必要
    elapsedTime[1] = glfwGetTime();
  }  
  glfwDestroyWindow(window);
  glfwTerminate();  
  exit(EXIT_SUCCESS);
};

void SyukatsuGame::replaceScene()
{
  //シーンを切り変える
  if(nextScene != NULL)
  {
    delete scene;
    scene = nextScene;
    nextScene = NULL;
  }
}

Input* SyukatsuGame::getInput() const
{
  return input;
}

FileIO* SyukatsuGame::getFileIO() const
{
  return fileIO;
}

Audio* SyukatsuGame::getAudio()  const
{
  return audio;
}

//グラフィックはglfwをそのままたたくからいらない
Graphics* SyukatsuGame::getGraphics() const
{
  return NULL;
}
  
Scene* const SyukatsuGame::getCurrentScene() const
{
  return scene;
}

//glfwの関数を扱う関係でconstにできない
GLFWwindow* SyukatsuGame::getWindow() const
{
  return window;
}
