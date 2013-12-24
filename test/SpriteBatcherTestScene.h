#ifndef SPRITE_BATCHER_TEST_H_2013_12_21
#define SPRITE_BATCHER_TEST_H_2013_12_21

#include <syukatsu/SyukatsuScene.h>
#include <syukatsu/SpriteBatcher.h>
#include <syukatsu/SyukatsuTexture.h>
#include <syukatsu/Camera2D.h>

class SpriteBatcherTestScene:public SyukatsuScene
{
  const float WIDTH;  //2Dスクリーンの幅(ワールド座標系)
  const float HEIGHT;

  Camera2D *camera;
  SpriteBatcher *batcher;  
public:
  SpriteBatcherTestScene(SyukatsuGame *game);
  void update(float deltaTime);  
  void render(float deltaTime);  
  void reshape(int width, int height) {  }  
  void dispose() {  }  
};

#endif
