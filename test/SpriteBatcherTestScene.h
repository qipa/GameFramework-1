#ifndef SPRITE_BATCHER_TEST_H_2013_12_21
#define SPRITE_BATCHER_TEST_H_2013_12_21

#include "../include/glfw/GLFWScene.h"
#include "../include/glfw/SpriteBatcher.h"
#include "../include/glfw/Camera2D.h"
#include "../include/glfw/GLFWTexture.h"

class SpriteBatcherTestScene:public GLFWScene
{
  const float WIDTH;  //2Dスクリーンの幅(ワールド座標系)
  const float HEIGHT;

  Camera2D *camera;
  SpriteBatcher *batcher;
  
public:
  SpriteBatcherTestScene(GLFWGame *glfwGame);
  
  void update(float deltaTime);
  
  void render(float deltaTime);  
  
  void reshape(int width, int height) {  }
  
  void dispose() {  }  
};

#endif
