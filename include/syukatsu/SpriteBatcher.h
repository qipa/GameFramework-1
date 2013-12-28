#ifndef SPRITE_BATCHER_H_2013_12_21
#define SPRITE_BATCHER_H_2013_12_21

#include "../Texture.h"

//2Dテクスチャをまとめて描画する為のクラス
class SpriteBatcher
{
  float *verticesBuffer;
  unsigned int *indicesBuffer;
  int bufferIndex;
  int numSprite;
public:
  SpriteBatcher(int _maxSprites);
  ~SpriteBatcher();
  
  void beginBatch(Texture *texture);
  
  void drawSprite(const float &x, const float &y, const float &width, const float &height, const TextureRegion *region);
  
  void drawSprite(const float &x, const float &y, const float &width, const float &height, const float &angle, const TextureRegion *region);
  
  void endBatch() const;

};
#endif
