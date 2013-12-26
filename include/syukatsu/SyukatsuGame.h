#ifndef SYUKATSU_GAME_H_2013_12_17
#define SYUKATSU_GAME_H_2013_12_17

#include "GLFW/glfw3.h"
#include "../Game.h"

#include "SyukatsuInput.h"

class SyukatsuAudio;
class SyukatsuFileIO;

class SyukatsuGame: public Game
{
protected:
  GLFWwindow *window;
  SyukatsuInput *input;
  SyukatsuFileIO *fileIO;
  SyukatsuAudio *audio;
  Scene *scene,*nextScene;
  
  float elapsedTime[2];  
  void replaceScene();  //次のシーンがあれば入れ替える  
public:
  SyukatsuGame(GLFWwindow*);  
  virtual ~SyukatsuGame();

  void loop();
  
  bool setScene(Scene *scene);  
  Input* getInput() const;  
  FileIO* getFileIO() const;  
  Audio*  getAudio()  const; 
  Graphics* getGraphics() const;  
  const Scene* getCurrentScene() const;  
  GLFWwindow* getWindow() const;   //glfwの関数を扱う関係でconstにできない
};

#endif
