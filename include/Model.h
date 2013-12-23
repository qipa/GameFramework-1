#ifndef MODEL_H_2013_12_22
#define MODEL_H_2013_12_22

#include <string>
using namespace std;

class Model
{
protected:
  string fileName;  
  Texture *texture;  
public:
  Model(const char *_fileName)
    :fileName(_fileName){  }
  ~Model(){  }  
  virtual void render() const = 0;
  virtual void load(const char *, float) = 0;
  virtual void dispose() = 0;  
};

#endif
