#ifndef TEST_SCENE1_H_2013_12_20
#define TEST_SCENE1_H_2013_12_20

#include <syukatsu/GLFW/glfw3.h>
#include <syukatsu/SyukatsuScene.h>
#include <syukatsu/Camera3D.h>
#include <syukatsu/Camera2D.h>
#include "SimpleObjectFactory.h"

class Camera3DTestScene :public SyukatsuScene
{
  static constexpr float WIDTH  = 4.8;
  static constexpr float HEIGHT = 3.2;
  Camera3D *camera;  
  Camera2D *camera2;  
  Vector3 pos;
  Vector2 target;
  const int cellSize;
  const int cellNum;
  float theta, phi;
public:
  Camera3DTestScene(SyukatsuGame* game);  
  ~Camera3DTestScene(){}  
  void update(float deltaTime);     
  void render(float deltaTime);    
  void reshape(int width, int height) {  }  
  void dispose() {  }
};

#endif
