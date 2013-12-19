#ifndef GLFW_GAME_H_2013_12_17
#define GLFW_GAME_H_2013_12_17

#include "../Game.h"
#include "../Scene.h"
#include "GLFW/glfw3.h"

class GLFWGraphics;
class GLFWInput;
class GLFWFileIO;
class GLFWAudio;

class GLFWGame: public Game
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
  GLFWGame(GLFWwindow*);
  
  virtual ~GLFWGame();

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
