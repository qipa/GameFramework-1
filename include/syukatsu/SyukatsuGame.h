#ifndef SYUKATSU_GAME_H_2013_12_17
#define SYUKATSU_GAME_H_2013_12_17
#include "GLFW/glfw3.h"

#include "../Game.h"
#include "../Scene.h"
#include "SyukatsuInput.h"
#include "SyukatsuFileIO.h"
#include "SyukatsuAudio.h"

class SyukatsuGame: public Game
{
protected:
  GLFWwindow *window;
  Input *input;
  FileIO *fileIO;
  Audio *audio;
  Scene *scene,*nextScene;
  float elapsedTime[2];  
  void replaceScene();  //次のシーンがあれば入れ替える
  
public:
  SyukatsuGame(GLFWwindow*);  
  virtual ~SyukatsuGame();

  void loop();
  bool setScene(Scene *scene);
  
  Input* getInput() const
  {
    return input;
  }

  FileIO* getFileIO() const
  {
    return fileIO;
  }

  Audio*  getAudio()  const
  {
    return audio;
  }

  //グラフィックはglfwをそのままたたくからいらない
  Graphics* getGraphics() const
  {
    return NULL;
  }
  
  const Scene* getCurrentScene() const
  {
    return scene;
  }

  //glfwの関数を扱う関係でconstにできない
  GLFWwindow* getWindow() const
  {
    return window;
  }
};

#endif
