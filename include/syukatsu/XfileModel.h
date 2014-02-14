#ifndef X_FILE_MODEL_H_2013_12_22
#define X_FILE_MODEL_H_2013_12_22

#include <vector>
#include <string>
#include <map>
#include "SyukatsuTexture.h"
#include "../Model.h"
#include "../math/Vector3.h"
class XfileModel : public Model
{
  class Color4f
  {
  public:
    float r,g,b,a;
  };

  class UV
  {
  public:
    float u, v;
  };    

  class Mesh
  {
  public:
    Vector3 vertex;
    Vector3 normal;
    UV uv;
  };
  
  class Material
  {
  public:
    string materialName;  //�}�e���A����(�����)
    Color4f diffuse;  //�g�U�F
    Color4f ambient;  //���F
    Color4f emission; //�����F
    Color4f specular; //���ːF
    float shininess;  //�P�x    
    Texture *texture;
    GLuint bufferId; //VBO�o�b�t�@ID�i�[�p
    std::vector <Mesh> meshes;//�O�p�ʃf�[�^
  Material():texture(NULL){ }    
  };

public:
  std::vector <Material> materials;
  std::map<string, Texture*> textureList; //�e�N�X�`��
public:
  XfileModel(const string, float);
  ~XfileModel();  
  virtual void load(const string, float);
  virtual void render(const float alpha=-1) const;
  virtual void dispose();
private:
  void readMaterial(FILE *fp);
  void readMesh(FILE *fp, std::vector<Vector3> &vertices, std::vector<int> &indexis, const float &size);
  void readMeshNormal(FILE *fp, std::vector<Vector3> &normal, std::vector<int> &indexis);
  void readTexCoord(FILE *fp, std::vector<UV> &uv);
  void readMeshMaterialList(FILE *fp, std::vector<int> &indexis);
};
/* 
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

public:
  vector <Material> Materials;
  map<string, Texture*> textureList; //�e�N�X�`��  
public:
  XfileModel(const string, float);
  ~XfileModel();  
  virtual void load(const string, float);
  virtual void render(const float alpha=-1) const;
  virtual void dispose(){};
};
*/
#endif
