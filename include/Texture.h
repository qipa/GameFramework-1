#ifndef TEXTURE_H_2013_11_19
#define TEXTURE_H_2013_11_19

#include "FilePath.h"
class Texture:public FilePath
{
protected:
  const string fileName;
  unsigned int width;  //pixel size (must be power of 2)
  unsigned int height;
public:
  Texture(const string _fileName)
    :fileName(_fileName)
  { }  
  virtual ~Texture(){ }
  
  virtual void load(string) = 0;
  virtual void bind() const = 0;
  virtual void unbind() const = 0;
  unsigned getWidth()  const  {  return width;  }  
  unsigned getHeight() const  {  return height; }
};

class TextureRegion
{
public:
  const Texture *texture;
  const float u1, v1;
  const float u2, v2;
  const float ratio; // height/width;
  
TextureRegion(const Texture *_texture,const float x,const float y,const float width,const float height)
  :texture(_texture),
    u1(        1.0*x/_texture->getWidth()), v1(          1.0*y/_texture->getHeight()),
    u2(1.0*(x+width)/_texture->getWidth()), v2( 1.0*(y+height)/_texture->getHeight()), ratio(height/width)
  { }

TextureRegion(const Texture *_texture)
  :texture(_texture),
    u1(0), v1(0),
    u2(1), v2(1), ratio(_texture->getHeight()/(float)texture->getWidth())
  { }

  unsigned getWidth() { return texture->getWidth(); }
  unsigned getHeight() { return texture->getHeight(); }
  float getRatio() { return ratio; }
};

#endif
