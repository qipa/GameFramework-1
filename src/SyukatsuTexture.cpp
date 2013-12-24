#include <GLFW/glfw3.h>
#include <SyukatsuTexture.h>
#include <lodepng.h>
#include <vector>
#include <cstdlib>
using namespace std;

SyukatsuTexture::SyukatsuTexture(const string fileName)
  :Texture(fileName)
{
  load(fileName);
}

void SyukatsuTexture::load(const string fileName)
{
  vector<unsigned char> raw_image;
  unsigned int width, height;

  string name = getPath()+fileName;  
  unsigned int error = lodepng::decode(raw_image, width, height, name.c_str());   
  
  if(error != 0)
  {
    fprintf(stderr, "can not read file %s\n", name.c_str());
    exit(2);
  }

  if( (width&(width-1)) != 0 || (height&(height-1)) != 0)
  {
    fprintf(stderr, "texture size must be power of 2\n");
    exit(2);
  }

  this->width  = width;
  this->height = height;

  int size = width*height*4; //RGBAの4
  image = new unsigned char[size];
  memset(image, 0, sizeof(unsigned char)*size);	//0で初期化
  
  for(size_t i=0; i<size; i++)
    image[i] = raw_image[i];  

  glGenTextures(1, &texId);
    
  glBindTexture(GL_TEXTURE_2D, texId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glEnable(GL_TEXTURE_2D);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);   
}

inline void SyukatsuTexture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, texId);
}

inline void SyukatsuTexture::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);  
}
