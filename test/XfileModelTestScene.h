#ifndef XFILE_MODEL_TEST_SCENE_H_2013_12_22
#define XFILE_MODEL_TEST_SCENE_H_2013_12_22

#include <syukatsu/SyukatsuScene.h>
#include <syukatsu/Camera3D.h>
#include <syukatsu/Camera2D.h>
#include <syukatsu/SpriteBatcher.h>

#include "SimpleObjectFactory.h"
#include "TestXFileModel.h"
class XfileModelTestScene:public SyukatsuScene
{
  Camera3D *camera;
  Camera2D *camera2;
  TestXfileModel *model;
  Texture *texture;
  TextureRegion *region;
  SpriteBatcher *batcher;

  float theta, phi;  
public:
  XfileModelTestScene(SyukatsuGame *game);
  ~XfileModelTestScene() {   }    
  void update(float deltaTime);
  void render(float deltaTime);
  void reshape(int width, int height)  {  }
  void dispose()  {  }
};


#endif
