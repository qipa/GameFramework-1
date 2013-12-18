#include "GLFW/glfw3.h"

#include "GLFWGame.h"
#include "GLFWInput.h"
#include "GLFWFileIO.h"
#include "GLFWAudio.h"

GLFWGame::GLFWGame(GLFWwindow* _window)
  :window(_window)
{
  scene = NULL;
  nextScene = NULL;
  elapsedTime[0] = elapsedTime[1] = 0;    
  //create member variables
  input = NULL;
  fileIO = NULL;
  audio = NULL;  
};
  
GLFWGame::~GLFWGame()
{
  //todo
  /*
  delete input;
  delete fileIO;

  delete audio;
  delete scene;
  */
};
  
bool GLFWGame::setScene(Scene *scene)
{
  //既に別の所から次のシーンを指定されていたら, 除外する
  if(this->nextScene != NULL || scene == NULL)
  {
    return false;
  }
  
  this->nextScene = scene;  //次のシーンの決定
  return true;
}

void GLFWGame::loop()
{

  float deltaTime = elapsedTime[1] - elapsedTime[0];
  elapsedTime[0] = glfwGetTime();
  scene->update(deltaTime);
  scene->render(deltaTime);
  elapsedTime[1] = glfwGetTime();
  replaceScene();
};

void GLFWGame::replaceScene()
{
  //シーンを切り変える
  if(nextScene != NULL)
  {
    delete scene;
    scene = nextScene;
    nextScene = NULL;
  }
}
