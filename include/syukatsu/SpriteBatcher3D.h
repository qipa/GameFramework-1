#ifndef SPRITE_BATCHER_3D_H_2013_12_28
#define SPRITE_BATCHER_3D_H_2013_12_28

//3Dで４点と,TextureRegionを渡すと描画してくれるクラス
#include "../math/Vector3.h"
#include "../Texture.h"

class SpriteBatcher3D
{
  float *verticesBuffer;
  unsigned int *indicesBuffer;
  int bufferIndex;
  int numSprite;
public:
  SpriteBatcher3D(int _maxSprites);
  ~SpriteBatcher3D();  
  
  void beginBatch(Texture *texture);
  
  void drawSprite(const Vector3 vertices[4], const TextureRegion *region); 
  
  void endBatch() const;
};

#endif
