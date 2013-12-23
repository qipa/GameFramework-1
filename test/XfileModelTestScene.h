#ifndef XFILE_MODEL_TEST_SCENE_H_2013_12_22
#define XFILE_MODEL_TEST_SCENE_H_2013_12_22

#include "../include/glfw/GLFWScene.h"
#include "../include/glfw/Camera3D.h"
#include "../include/glfw/Camera2D.h"

#include "../include/glfw/XfileModel.h"
#include "../include/glfw/SpriteBatcher.h"
#include "SimpleObjectFactory.h"

class XfileModelTestScene:public GLFWScene
{
  Camera3D *camera;
  Camera2D *camera2;
  Model *model;
  Texture *texture;
  TextureRegion *region;
  SpriteBatcher *batcher;

  float theta, phi;  
public:
  XfileModelTestScene(GLFWGame *glfwGame);
  ~XfileModelTestScene() {   }    
  void update(float deltaTime);
  void render(float deltaTime);
  void reshape(int width, int height)  {  }
  void dispose()  {  }
};


#endif
