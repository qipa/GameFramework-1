#ifndef SYUKATSU_SCENE_H_2013_12_18
#define SYUKATSU_SCENE_H_2013_12_18

#include "../Scene.h"
#include "SyukatsuGame.h"

class SyukatsuScene:public Scene
{
protected:
  SyukatsuGame *syukatsuGame;
public:
  SyukatsuScene(SyukatsuGame *game)
    :Scene(game)
    ,syukatsuGame(game)
  {    
  }  
  virtual void update(float deltaTime) = 0;
  virtual void render(float deltaTime) = 0;
  virtual void reshape(int width, int height) = 0;
  virtual void dispose() = 0;  
};
#endif
