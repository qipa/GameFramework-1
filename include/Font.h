#ifndef FONT_H_2013_12_23
#define FONT_H_2013_12_23

#include "FilePath.h"
#include<string>
using namespace std;

class Font :public FilePath
{
protected:
  string fileName;
  float size;
  virtual void load(string name) = 0;
public:
Font(string _fileName)
  :fileName(_fileName), size(3.0){  }
  ~Font() { }      
  virtual void render(string str) const = 0;
  virtual void setSize(float size)
  {
    this->size = size;
  }

};
#endif
