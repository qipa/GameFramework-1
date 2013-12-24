// -*- C++ -*-
#ifndef TEST_LISTS_SCENE_H_2013_12_22
#define TEST_LISTS_SCENE_H_2013_12_22

#include <syukatsu/SyukatsuScene.h>
#include "Camera2DTestScene.h"

class TestListsScene:public SyukatsuScene
{
  static constexpr float WIDTH = 96.f;
  static constexpr float HEIGHT= 64.f;  
  Camera2D *camera;
  
public:
  TestListsScene(SyukatsuGame *game)
    :SyukatsuScene(game)
  {
    camera = new Camera2D(syukatsuGame->getWindow(), WIDTH, HEIGHT);    
  }

  void update(float deltaTime); 

  void render(float deltaTime); 

  void dispose()
  {
  }

  void reshape(int width, int height)
  {
  }
  
};
#endif
