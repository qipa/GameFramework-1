#ifndef TEST_SCENE2_H_2013_12_20
#define TEST_SCENE2_H_2013_12_20

#include <syukatsu/SyukatsuScene.h>
#include <syukatsu/Camera2D.h>

class Camera2DTestScene: public SyukatsuScene
{
  const float WIDTH;
  const float HEIGHT;  
  Camera2D *camera;
  Camera2D *camera2;
  Vector2 pos, pos2;
  
public:
  Camera2DTestScene(SyukatsuGame* game);  
  ~Camera2DTestScene(){}
  
  void update(float deltaTime);  
  void render(float deltaTime);  
  void reshape(int width, int height) {  }  
  void dispose() {  }
};

#endif
