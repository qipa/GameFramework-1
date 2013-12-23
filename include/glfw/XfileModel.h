#ifndef X_FILE_MODEL_H_2013_12_22
#define X_FILE_MODEL_H_2013_12_22
#include <vector>
//#include <GL/glut.h>
#include "GLFWTexture.h"
#include <string>
#include <map>
#include "../Model.h"

using namespace std;
 
class XfileModel : public Model
{
  class Vector3f
  {
  public:
    float x, y, z;
    Vector3f()
      :x(0),y(0),z(0)
    {
    }
    
  Vector3f(float _x, float _y, float _z)
    :x(_x),y(_y),z(_z)
    {
    }
    
    Vector3f operator*(const float &k)
    {
      return Vector3f(this->x*k, this->y*k, this->z*k);
    };    
  };
  
  class Vector4i
  {
  public:
    int x;
    int y;
    int z;
    int w;
  };
        
  class Vector4f
  {
  public:
    float x,y,z,w;
  };
        
  class Color4f
  {
  public:
    float r,g,b,a;
  };

  class Reflection4{      
  public:
    Color4f diffuse;//4�̔���
    Color4f ambient;
    Color4f emission;
    Color4f specular;
  };

  class UV
  {
  public:
    float u, v;
  };    
    
  class Triangle
  {
  public:
    Vector3f TriVer;
    Vector3f TriNor;
    UV TriUV;      
  };

  class Quadrangle
  {
  public:
    Vector3f QuadVer;
    Vector3f QuadNor;
    UV QuadUV;
  };

  class Material{
  public:
    string materialName;  //�}�e���A����
    Reflection4 materialColor;//����
    float shininess;     //shininess
    string textureName;  //�e�N�X�`����
    Texture *texture;    
    int texNo;           //�e�N�X�`��NO.
    vector <Triangle> triMeshes;//�O�p�ʃf�[�^
    vector <Quadrangle> quadMeshes;//�l�p�ʃf�[�^
  Material():texture(NULL){ }    
  };

protected:
  vector <Material> Materials;
  map<string, Texture*> textureList; //�e�N�X�`��  
public:
  XfileModel(const char *, float);
  virtual void load(const char *, float);
  virtual void render() const;
  virtual void dispose(){};
};

#endif
