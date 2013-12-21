#ifndef TEST_SCENE2_H_2013_12_20
#define TEST_SCENE2_H_2013_12_20

#include "../include/glfw/GLFWScene.h"
#include "../include/glfw/Camera2D.h"

class Camera2DTestScene: public GLFWScene
{
  Camera2D *camera;
  Vector2 pos;
public:
  Camera2DTestScene(GLFWGame* glfwGame);
  
  ~Camera2DTestScene(){}
  
  void update(float deltaTime);
  
  void render(float deltaTime);  
  
  void reshape(int width, int height) {  }
  
  void dispose() {  }
};

#endif
