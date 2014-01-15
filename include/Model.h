#ifndef MODEL_H_2013_12_22
#define MODEL_H_2013_12_22

#include "FilePath.h"
#include <string>
using namespace std;

class Model: public FilePath
{
protected:  
  const string fileName;  
  Texture *texture;  
public:
  Model(const string _fileName)
    :fileName(_fileName){  }
  ~Model(){  }
  
  virtual void render(const float alpha = -1) const = 0;
  virtual void load(const string, float) = 0;
  virtual void dispose() = 0;
private:
  string& Path()
  {
    static string path = "";
    return path;    
  }
  
};

#endif
