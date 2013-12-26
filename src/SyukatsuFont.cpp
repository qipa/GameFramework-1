#include <FTGL/ftgl.h>
#include <GLFW/glfw3.h>
#include <SyukatsuFont.h>
#include <iostream>
using namespace std;

SyukatsuFont::SyukatsuFont(const string fileName)
  :Font(fileName)
{
  load(fileName);  
}

SyukatsuFont::~SyukatsuFont()
{
  delete font;
}

void SyukatsuFont::load(const string fileName)
{
  string name = getPath() + fileName;  
  font = new FTGLPolygonFont(name.c_str());

  if(font->Error())
  {
    cout << "can not open font file " << name << endl;
    exit(2);
  }
  
  if(!font->CharMap(ft_encoding_unicode))
  {
    cout << "can not set charmap to " << name << endl;
    exit(2);
  }

  if(!font->FaceSize(size))
  {
    cout << "can not set size to " << name << endl;
    exit(2);
  }
}

void SyukatsuFont::render(const string text) const
{  
  font->Render(text.c_str()); 
}

void SyukatsuFont::setSize(float size)
{
  this->size = size;  
  if(!font->FaceSize(size))
  {
    cout << "can not set size" << endl;
    exit(2);
  }  
}


