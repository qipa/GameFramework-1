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
}

void SpriteBatcher3D::drawSprite(const Vector3 position, const Vector3 &normal, const Vector2 &size, const TextureRegion *region)
{
  //画像の上方向を表すベクトル(これがそのまま上方向になる訳ではない)
  Vector3 up;
  //通常はy軸が画像の上, 画像が上か下を向いている時はz軸が画像の上
  if( normal.x == 0 && normal.z == 0)
    up.set(0,0,1);
  else
    up.set(0,1,0);  

  //X軸
  Vector3 axis1 = up.cross(normal);
  axis1.normalize();

  //Y軸
  Vector3 axis2 = normal.cross(axis1);
  axis2.normalize();

  axis1 *= size.x/2;
  axis2 *= size.y/2;
  const Vector3 leftBottom  = position - axis1 - axis2;
  const Vector3 rightBottom = position + axis1 - axis2;
  const Vector3 rightTop    = position + axis1 + axis2;
  const Vector3 leftTop     = position - axis1 + axis2;

  verticesBuffer[bufferIndex++] = leftBottom.x;
  verticesBuffer[bufferIndex++] = leftBottom.y;
  verticesBuffer[bufferIndex++] = leftBottom.z;
  verticesBuffer[bufferIndex++] = region->u1;
  verticesBuffer[bufferIndex++] = region->v2;

  verticesBuffer[bufferIndex++] = rightBottom.x;
  verticesBuffer[bufferIndex++] = rightBottom.y;
  verticesBuffer[bufferIndex++] = rightBottom.z;
  verticesBuffer[bufferIndex++] = region->u2;
  verticesBuffer[bufferIndex++] = region->v2;

  verticesBuffer[bufferIndex++] = rightTop.x;
  verticesBuffer[bufferIndex++] = rightTop.y;
  verticesBuffer[bufferIndex++] = rightTop.z;
  verticesBuffer[bufferIndex++] = region->u2;
  verticesBuffer[bufferIndex++] = region->v1;

  verticesBuffer[bufferIndex++] = leftTop.x;
  verticesBuffer[bufferIndex++] = leftTop.y;
  verticesBuffer[bufferIndex++] = leftTop.z;  
  verticesBuffer[bufferIndex++] = region->u1;
  verticesBuffer[bufferIndex++] = region->v1;
  numSprite++;  
}

void SpriteBatcher3D::drawSprite(const Vector3 position, const Vector3 &normal, const Vector2 &size, const float &angle, const TextureRegion *region)
{
  Vector3 up;
  //通常はy軸が画像の上, 画像が上か下を向いている時はz軸が画像の上
  if( normal.x == 0 && normal.z == 0)  
    up.set(0, 0, 1);
  else
    up.set(0, 1, 0);  

  //normalの方から見てaxis1が右に見えるように
  Vector3 axis1 = up.cross(normal);
  axis1.normalize();
  
  //normalを軸にangleだけ回転させる, 回転行列の計算
  const auto A = normal.normalizedVector();
  const float C = cos(angle);
  const float S = sin(angle);
  const float oneMinusC = 1.0f - C;

  const float AxAyOneMinusC = A.x*A.y*oneMinusC;
  const float AxAzOneMinusC = A.x*A.z*oneMinusC;
  const float AyAzOneMinusC = A.y*A.z*oneMinusC;

  const float AxS = A.x*S;
  const float AzS = A.z*S;
  const float AyS = A.y*S;

  const float Ax2 = A.x*A.x;
  const float Ay2 = A.y*A.y;
  const float Az2 = A.z*A.z;
  const float Ra[3][3] =
    {
       {C + Ax2*oneMinusC  , AxAyOneMinusC - AzS, AxAzOneMinusC + AyS}
      ,{AxAyOneMinusC + AzS, C + Ay2*oneMinusC  , AyAzOneMinusC - AxS}
      ,{AxAzOneMinusC - AyS, AyAzOneMinusC + AxS, C + Az2*oneMinusC  }
    };

  //回転させる
  axis1.set( Ra[0][0]*axis1.x + Ra[0][1]*axis1.y + Ra[0][2]*axis1.z,
             Ra[1][0]*axis1.x + Ra[1][1]*axis1.y + Ra[1][2]*axis1.z,
             Ra[2][0]*axis1.x + Ra[2][1]*axis1.y + Ra[2][2]*axis1.z  );
  
  Vector3 axis2 = normal.cross(axis1);
  axis2.normalize();
  
  //長さをsizeに合わせる
  axis1 *= size.x/2;
  axis2 *= size.y/2;

  const Vector3 leftBottom  = position - axis1 - axis2;
  const Vector3 rightBottom = position + axis1 - axis2;
  const Vector3 rightTop    = position + axis1 + axis2;
  const Vector3 leftTop     = position - axis1 + axis2;

  verticesBuffer[bufferIndex++] = leftBottom.x;
  verticesBuffer[bufferIndex++] = leftBottom.y;
  verticesBuffer[bufferIndex++] = leftBottom.z;
  verticesBuffer[bufferIndex++] = region->u1;
  verticesBuffer[bufferIndex++] = region->v2;

  verticesBuffer[bufferIndex++] = rightBottom.x;
  verticesBuffer[bufferIndex++] = rightBottom.y;
  verticesBuffer[bufferIndex++] = rightBottom.z;
  verticesBuffer[bufferIndex++] = region->u2;
  verticesBuffer[bufferIndex++] = region->v2;

  verticesBuffer[bufferIndex++] = rightTop.x;
  verticesBuffer[bufferIndex++] = rightTop.y;
  verticesBuffer[bufferIndex++] = rightTop.z;
  verticesBuffer[bufferIndex++] = region->u2;
  verticesBuffer[bufferIndex++] = region->v1;

  verticesBuffer[bufferIndex++] = leftTop.x;
  verticesBuffer[bufferIndex++] = leftTop.y;
  verticesBuffer[bufferIndex++] = leftTop.z;  
  verticesBuffer[bufferIndex++] = region->u1;
  verticesBuffer[bufferIndex++] = region->v1;
  numSprite++;  
}

void SpriteBatcher3D::drawSprite(const Vector3 position, const Vector3 &rightAxis, const Vector3 &upAxis, const Vector2 &size, const TextureRegion *region)
{
  Vector3 axis1 = rightAxis.normalizedVector();
  Vector3 axis2 = upAxis.normalizedVector();

  axis1 *= size.x/2;
  axis2 *= size.y/2;
  const Vector3 leftBottom  = position - axis1 - axis2;
  const Vector3 rightBottom = position + axis1 - axis2;
  const Vector3 rightTop    = position + axis1 + axis2;
  const Vector3 leftTop     = position - axis1 + axis2;

  
  verticesBuffer[bufferIndex++] = leftBottom.x;
  verticesBuffer[bufferIndex++] = leftBottom.y;
  verticesBuffer[bufferIndex++] = leftBottom.z;
  verticesBuffer[bufferIndex++] = region->u1;
  verticesBuffer[bufferIndex++] = region->v2;

  verticesBuffer[bufferIndex++] = rightBottom.x;
  verticesBuffer[bufferIndex++] = rightBottom.y;
  verticesBuffer[bufferIndex++] = rightBottom.z;
  verticesBuffer[bufferIndex++] = region->u2;
  verticesBuffer[bufferIndex++] = region->v2;

  verticesBuffer[bufferIndex++] = rightTop.x;
  verticesBuffer[bufferIndex++] = rightTop.y;
  verticesBuffer[bufferIndex++] = rightTop.z;
  verticesBuffer[bufferIndex++] = region->u2;
  verticesBuffer[bufferIndex++] = region->v1;

  verticesBuffer[bufferIndex++] = leftTop.x;
  verticesBuffer[bufferIndex++] = leftTop.y;
  verticesBuffer[bufferIndex++] = leftTop.z;  
  verticesBuffer[bufferIndex++] = region->u1;
  verticesBuffer[bufferIndex++] = region->v1;
  numSprite++;  
}
