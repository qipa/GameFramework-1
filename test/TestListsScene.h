// -*- C++ -*-
#ifndef TEST_LISTS_SCENE_H_2013_12_22
#define TEST_LISTS_SCENE_H_2013_12_22

#include "../include/glfw/GLFWScene.h"
#include "Camera2DTestScene.h"

class TestListsScene:public GLFWScene
{
  static constexpr float WIDTH = 4.8f;
  static constexpr float HEIGHT= 3.2f;  
  Camera2D *camera;
  
public:
  TestListsScene(GLFWGame *glfwGame)
    :GLFWScene(glfwGame)
  {
    camera = new Camera2D(glfwGame->getWindow(), WIDTH, HEIGHT);    
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
