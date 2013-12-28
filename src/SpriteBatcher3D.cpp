#include <SpriteBatcher3D.h>
#include <GLFW/glfw3.h>

SpriteBatcher3D::SpriteBatcher3D(int _maxSprites)
{
  verticesBuffer = new float[_maxSprites*5*4]; //x,y,z,t,u * 4点
  indicesBuffer = new unsigned int[_maxSprites*6]; // 1面あたり6点
  bufferIndex = 0;
  numSprite = 0;

  int len = _maxSprites*6;
  for(int i=0, j=0; i<len; i+=6, j+=4)
  {
    indicesBuffer[i+0] = (j+0);
    indicesBuffer[i+1] = (j+1);
    indicesBuffer[i+2] = (j+2);
    indicesBuffer[i+3] = (j+2);
    indicesBuffer[i+4] = (j+3);
    indicesBuffer[i+5] = (j+0);
  }
}

SpriteBatcher3D::~SpriteBatcher3D()
{
  delete verticesBuffer;
  delete indicesBuffer;  
}

void SpriteBatcher3D::beginBatch(Texture *texture)
{  
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA_TEST); //アルファテスト開始  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  texture->bind();  
  numSprite=0;
  bufferIndex=0;
}

void SpriteBatcher3D::endBatch() const
{  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glVertexPointer(3,  GL_FLOAT, 5*sizeof(float), verticesBuffer  );
  glTexCoordPointer(2,GL_FLOAT, 5*sizeof(float), verticesBuffer+3);
  
  glDrawElements(GL_TRIANGLES, 6*numSprite, GL_UNSIGNED_INT, indicesBuffer);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST); //アルファテスト開始  
}

void SpriteBatcher3D::drawSprite(const Vector3 vertices[4], const TextureRegion *region)
{
  verticesBuffer[bufferIndex++] = vertices[0].x;
  verticesBuffer[bufferIndex++] = vertices[0].y;
  verticesBuffer[bufferIndex++] = vertices[0].z;
  verticesBuffer[bufferIndex++] = region->u1;
  verticesBuffer[bufferIndex++] = region->v2;


  verticesBuffer[bufferIndex++] = vertices[1].x;
  verticesBuffer[bufferIndex++] = vertices[1].y;
  verticesBuffer[bufferIndex++] = vertices[1].z;
  verticesBuffer[bufferIndex++] = region->u2;
  verticesBuffer[bufferIndex++] = region->v2;

  verticesBuffer[bufferIndex++] = vertices[2].x;
  verticesBuffer[bufferIndex++] = vertices[2].y;
  verticesBuffer[bufferIndex++] = vertices[2].z;
  verticesBuffer[bufferIndex++] = region->u2;
  verticesBuffer[bufferIndex++] = region->v1;

  verticesBuffer[bufferIndex++] = vertices[3].x;
  verticesBuffer[bufferIndex++] = vertices[3].y;
  verticesBuffer[bufferIndex++] = vertices[3].z;  
  verticesBuffer[bufferIndex++] = region->u1;
  verticesBuffer[bufferIndex++] = region->v1;
  numSprite++;
}
