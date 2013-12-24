#include <GLFW/glfw3.h>
#include <SyukatsuGame.h>
#include <SyukatsuInput.h>
#include <SyukatsuFileIO.h>
#include <SyukatsuAudio.h>

SyukatsuGame::SyukatsuGame(GLFWwindow* _window)
  :window(_window)
{
  scene = NULL;
  nextScene = NULL;
  elapsedTime[0] = glfwGetTime();
  elapsedTime[1] = glfwGetTime();    

  input = new SyukatsuInput(window);
  fileIO = NULL;
  audio = NULL;  
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
  float deltaTime = elapsedTime[1] - elapsedTime[0];
  elapsedTime[0] = glfwGetTime();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  scene->update(deltaTime);
  scene->render(deltaTime);
  replaceScene();
  glfwSwapBuffers(window); //絶対必要
  glfwPollEvents();        //絶対必要
  elapsedTime[1] = glfwGetTime();
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
