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
    Color4f(const float &_r, const float &_g, const float &_b, const float _a=1)
      :r(_r),g(_g),b(_b),a(_a)
    {
    }
  Color4f()
      :r(),g(),b(),a()
    {
    }
    float r,g,b,a;
    
    Color4f operator+(const Color4f &other)
    {
      return Color4f(r+other.r, g+other.g, b+other.b, a+other.a);
    }
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
    string materialName;  //マテリアル名(あれば)
    Color4f diffuse;  //拡散色
    Color4f ambient;  //環境色
    Color4f emission; //発光色
    Color4f specular; //反射色
    float shininess;  //輝度    
    Texture *texture;
    GLuint bufferId; //VBOバッファID格納用
    std::vector <Mesh> meshes;//三角面データ
  Material():texture(NULL){ }    
  };

public:
  std::vector <Material> materials;
  std::map<string, Texture*> textureList; //テクスチャ
public:
  XfileModel(const string, float);
  ~XfileModel();  
  virtual void load(const string, float);
  virtual void render(const float alpha=-1) const;
  virtual void renderAddColor(const float &red,
                      const float &green,
                      const float &blue,
                      const float alpha = -1) const;
  virtual void dispose();
private:
  void readMaterial(FILE *fp);
  void readMesh(FILE *fp, std::vector<Vector3> &vertices, std::vector<int> &indexis, const float &size);
  void readMeshNormal(FILE *fp, std::vector<Vector3> &normal, std::vector<int> &indexis);
  void readTexCoord(FILE *fp, std::vector<UV> &uv);
  void readMeshMaterialList(FILE *fp, std::vector<int> &indexis);
};

#endif
