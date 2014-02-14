#include <XfileModel.h>
#include <SyukatsuTexture.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

XfileModel::XfileModel(const string fileName, float size)
  :Model(fileName)
{
  load(fileName, size);
}

XfileModel::~XfileModel()
{
  dispose();
}

static string spliter(string str) 
{
  int p = 0; 
  string res;

  while(str[p] != '\"') { p++; }
  p++;

  while(str[p] != '\"') { res += str[p]; p++; }

  return res;
}

static void skipBrackets(FILE *fp)
{
  char buf[255];
  // '}'������܂Ŕ�΂�
  while(strchr(buf,'}')==NULL)
    fgets(buf,sizeof(buf),fp);

  fgets(buf,sizeof(buf),fp);
}

//�}�e���A���̓ǂݍ���
void XfileModel::readMaterial(FILE *fp)
{
  Material mtl;
  char buf[255];
  fgets(buf,sizeof(buf),fp);//���s����(���̍s����f�[�^������Ɖ���)
  Color4f color;
  //�f�B�t���[�Y
  fscanf(fp,"%f;%f;%f;%f;;",&color.r,&color.g,&color.b,&color.a);
//  mtl.materialColor.diffuse = color;
    mtl.diffuse = color;
  //SHININESS  
  fscanf(fp,"%f;",&mtl.shininess);

  //�c��̓A���t�@�l�͂Ȃ��̂łƂ肠����1�ɂ��Ƃ�
  color.a = 1;
  //�X�y�L�����[ 
  fscanf(fp,"%f;%f;%f;;",&color.r, &color.g, &color.b);
  mtl.specular=color;
  
  //�G�~�b�V�u
  fscanf(fp,"%f;%f;%f;;",&color.r, &color.g, &color.b);  
  mtl.ambient=color;

  char key[255];
  //�e�N�X�`���[
  fscanf(fp,"%s ",key);

  mtl.texture = NULL;      
  if(strcmp(key,"TextureFilename")==0)
  {
    fgets(buf,sizeof(buf),fp);//����̍s�ɂ���Ɛ���@���s����
    fscanf(fp,"%s",buf); //�e�N�X�`���l�[��
    
    string texName = buf;
    texName = spliter(texName);

    //textureList�ɖ�����Βǉ�
    if(textureList.find(texName) == textureList.end())
      textureList[texName] = new SyukatsuTexture(texName.c_str());

    mtl.texture = textureList[texName];
  }
  
  materials.push_back(mtl);
}

//���b�V�����̓ǂݍ���
void XfileModel::readMesh(FILE *fp, vector<Vector3> &vertices, vector<int> &indexis, const float &size)
{
  char buf[255];
  fgets(buf,sizeof(buf),fp);  //���s����
  fgets(buf,sizeof(buf),fp);  //���_�̐����擾
  
  int vertexNum = atoi(buf);
  
  vertices.reserve(vertexNum);
  //���b�V���̐������ǂݍ���
  for(int i=0;i<vertexNum ;i++)
  {
    Vector3 vec;
    fscanf(fp,"%f;%f;%f;,",&vec.x,&vec.y,&vec.z);
    vertices.push_back(vec*size);
  }
  
  //���_�C���f�b�N�X�ǂݍ���  
  fgets(buf,sizeof(buf),fp); //���̍s��
  //���b�V���̐����擾�ł���܂�, ��s���Ƃ΂�
  fgets(buf,sizeof(buf),fp);
  while(strchr(buf,';')==NULL)
    fgets(buf,sizeof(buf),fp);
  
  int meshNum = atoi(buf);
  indexis.reserve(meshNum);
  for(int i=0;i<meshNum ;i++)
  {
    int v1,v2,v3,v4;
    int vecNum; //���b�V���̒��_��
    fscanf(fp,"%d;",&vecNum);
    indexis.push_back(vecNum);
    if(vecNum == 3)
    {
      fscanf(fp,"%d,%d,%d;,",&v1,&v2,&v3);
      indexis.push_back(v1);
      indexis.push_back(v2);
      indexis.push_back(v3);
    }
    else
    {
      fscanf(fp,"%d,%d,%d,%d;,",&v1,&v2,&v3,&v4);
      indexis.push_back(v1);
      indexis.push_back(v2);
      indexis.push_back(v3);
      indexis.push_back(v4);
    }
  }
}

void XfileModel::readMeshNormal(FILE *fp, vector<Vector3> &normal, vector<int> &indexis)
{
  char buf[255];
  //�@���f�[�^�̓ǂݍ���
  fgets(buf,sizeof(buf),fp); //���s����
  fgets(buf,sizeof(buf),fp); //�@���̐����擾
  int normalNum=atoi(buf);
  normal.reserve(normalNum);
  
  for(int i=0;i<normalNum ;i++)
  {
    Vector3 vec;
    fscanf(fp,"%f;%f;%f;,",&vec.x, &vec.y, &vec.z);
    normal.push_back(vec);
  }
  
  //�@���C���f�b�N�X(�ǂ̃|���S�����ǂ̒��_���g���Ă��邩)��ǂݍ���  
  fgets(buf,sizeof(buf),fp);//�f�[�^��2�s���ɂ���Ɛ���@���s����
  fgets(buf,sizeof(buf),fp);
  while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//��s�΍�
  int meshNum=atoi(buf);
  indexis.reserve(meshNum);
  for(int i=0;i<meshNum ;i++)
  {
    int norNum;
    int v1,v2,v3,v4;
    fscanf(fp,"%d;",&norNum);
    indexis.push_back(norNum);
    if(norNum == 3)
    {      
      fscanf(fp,"%d,%d,%d;,",&v1,&v2,&v3);
      indexis.push_back(v1);
      indexis.push_back(v2);
      indexis.push_back(v3);
    }
    else
    {
      fscanf(fp,"%d,%d,%d,%d;,",&v1,&v2,&v3,&v4);
      indexis.push_back(v1);
      indexis.push_back(v2);
      indexis.push_back(v3);
      indexis.push_back(v4);
    }
  }
}

void XfileModel::readTexCoord(FILE *fp, vector<UV> &uv)
{
  char buf[255]; 
  fgets(buf,sizeof(buf),fp);//�f�[�^��2�s���ɂ���Ɛ���@���s����
  fgets(buf,sizeof(buf),fp);
  while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//��s�΍�
  int texNum=atoi(buf);
  uv.reserve(texNum);
  for(int i=0;i<texNum ;i++)
  {
    UV vec;
    fscanf(fp,"%f;%f;,",&vec.u,&vec.v);
    uv.push_back(vec);
  }
}

void XfileModel::readMeshMaterialList(FILE *fp, vector<int> &indexis)
{
  char buf[255]; 
  fgets(buf,sizeof(buf),fp);//����s
  fgets(buf,sizeof(buf),fp);//�}�e���A����
  fgets(buf,sizeof(buf),fp);//���X�g�v�f��
  int meshNum=atoi(buf);
  for(int i=0;i<meshNum;i++)
  {
    fgets(buf,sizeof(buf),fp);
    int index=atoi(buf);
    indexis.push_back(index);
  }
}

void XfileModel::load(const string fileName, float size)
{
  Material mtl;
  vector <Vector3> Vertex;//���_
  vector <Vector3> Normal;//�@��
  vector <UV> uv;//UV
  vector <int> VertexIndex;
  vector <int> NormalIndex;
  vector <int> MaterialIndex;

  char key[255];
  //X�t�@�C�����J���ē��e��ǂݍ���
  FILE* fp=NULL;

  //���\�[�X�ւ̃p�X��""
  string name = getPath() + fileName;
  
  if( (fp = fopen(name.c_str(), "rt")) == NULL)
  {
    fprintf(stderr, "can not open file %s\n", name.c_str());
    return;
  }

  //�ǂݍ��� 
  fseek(fp,SEEK_SET,0);
  while(!feof(fp))
  {
    //�L�[���[�h �ǂݍ���
    memset(key, 0, sizeof(key));
    fscanf(fp,"%s ",key);

    //�e���v���[�g�̍s�͒��΂�
    if(strcmp(key, "template") == 0)    
      skipBrackets(fp);    
    
    if(strcmp(key,"Material")==0)    
      readMaterial(fp);  //�}�e���A����ǂݍ���    
    
    //���_ �ǂݍ���
    if(strcmp(key,"Mesh")==0)    
      readMesh(fp, Vertex, VertexIndex, size);
    
    //�@�� �ǂݍ���
    if(strcmp(key,"MeshNormals")==0)    
      readMeshNormal(fp, Normal, NormalIndex);
    
    //�e�N�X�`���[���W �ǂݍ���
    if(strcmp(key,"MeshTextureCoords")==0)    
      readTexCoord(fp, uv);
        
    //�}�e���A�����X�g
    if(strcmp(key,"MeshMaterialList")==0)    
      readMeshMaterialList(fp, MaterialIndex);    
  }  
  fclose(fp);

  int j = 0;//0�Ԗڂ̃|���S���̒��_�����i�[����Ă���Y��
  for( auto mtlIndex : MaterialIndex )
  {
    Mesh mesh;
    if ( VertexIndex[j] == 3)
    {
      for( int k=1; k<=3; k++)
      {
        Mesh mesh;
        mesh.vertex=Vertex[VertexIndex[j+k]];
        mesh.normal=Normal[NormalIndex[j+k]];
        mesh.uv=uv[VertexIndex[j+k]];        
        materials[mtlIndex].meshes.push_back(mesh);
      }
      j+=4; //���̃|���S���̒��_�����i�[����Ă���Y��
    }
    else
    {
      //4�p�`�|���S����3�p�`�ɕ������Ċi�[
      int index[] = {1, 2, 3, 1, 3, 4};
      for( int k=0; k<6; k++)
      {
        Mesh mesh;
        mesh.vertex=Vertex[VertexIndex[j+index[k]]];
        mesh.normal=Normal[NormalIndex[j+index[k]]];
        mesh.uv=uv[VertexIndex[j+index[k]]];
        materials[mtlIndex].meshes.push_back(mesh);
      }
      j+=5;//���̃|���S���̒��_�����i�[����Ă���Y��
    }
  }
    
    //VBO������,GPU�ɒu���Ă���
  for ( int i=0; i<materials.size(); i++)
  {
    glGenBuffers(1, &materials[i].bufferId);
    
    //���_
    glBindBuffer(GL_ARRAY_BUFFER, materials[i].bufferId);
    glBufferData(GL_ARRAY_BUFFER, materials[i].meshes.size()*sizeof(Mesh)
                 , (GLfloat*)&materials[i].meshes[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
  }

  return;
}

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
//�`��
void XfileModel::render(const float alpha) const
{
  glPushAttrib( GL_COLOR_MATERIAL |
                GL_CURRENT_BIT |
                GL_ENABLE_BIT |
                GL_COLOR_BUFFER_BIT |
                GL_TEXTURE_BIT);  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA_TEST); //�A���t�@�e�X�g�J�n
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  for(auto mat : materials)
  {
    //������������, ���̃|���S���������Ȃ��}�e���A�������邩������Ȃ��̂�, ����΍�
    if ( mat.meshes.size() <= 0 )
      continue;

    //�A���t�@�l�̕ύX�����邩������Ȃ��̂�, ��U�ʂ̕ϐ��ɑ��
    auto ambient = mat.ambient;
    auto diffuse = mat.diffuse;
    auto specular = mat.specular;

    //�A���t�@�l�̎w�肪�����, �����I�ɂ��̒l�ɂ���
    if ( alpha != -1 )
      ambient.a = diffuse.a = specular.a = alpha;

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT , (const GLfloat*)&ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE , (const GLfloat*)&diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (const GLfloat*)&specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, mat.shininess);

    glBindBuffer(GL_ARRAY_BUFFER, mat.bufferId);
    glVertexPointer(3, GL_FLOAT, sizeof(Mesh), BUFFER_OFFSET(0));
    glNormalPointer(GL_FLOAT,sizeof(Mesh), BUFFER_OFFSET(sizeof(Vector3)));

    //�e�N�X�`���̐ݒ�
    if(mat.texture != NULL)
    {
      mat.texture->bind();
      glTexCoordPointer(2, GL_FLOAT, sizeof(Mesh), BUFFER_OFFSET(sizeof(Vector3)+sizeof(Vector3)));
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);    
    }
    else
    {
      glDisable(GL_TEXTURE_2D);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    
    glDrawArrays(GL_TRIANGLES, 0, mat.meshes.size());
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);    
  }  

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glPopAttrib();  
}

void XfileModel::dispose()
{
  for ( int i=0; i<materials.size(); i++ )
  {
    glDeleteBuffers(1, &materials[i].bufferId);
    materials[i].meshes.clear();
  }
  materials.clear();
}
/*
#include <XfileModel.h>
#include <SyukatsuTexture.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

XfileModel::XfileModel(const string fileName, float size)
  :Model(fileName)
{
  load(fileName, size);
}

XfileModel::~XfileModel()
{
  
}

string spliter(string str) 
{
  int p = 0; 
  string res;

  while(str[p] != '\"') { p++; }
  p++;

  while(str[p] != '\"') { res += str[p]; p++; }

  return res;
}

void XfileModel::load(const string fileName, float size)
{
  Vector3f vec3d;
  Vector4f vec4d;
  UV vec2d;
  Triangle Tri;
  Quadrangle Quad;
  Material mtl;

  vector <Vector3f> Vertex;//���_
  vector <Vector3f> Normal;//�@��
  vector <UV> uv;//UV
  vector <int> VertexIndex;
  vector <int> NormalIndex;
  vector <int> MaterialIndex;

  char key[255];
  char buf[255];
  //X�t�@�C�����J���ē��e��ǂݍ���
  FILE* fp=NULL;

  string name = getPath() + fileName;
  
  if( (fp = fopen(name.c_str(), "rt")) == NULL)
  {
    fprintf(stderr, "can not open file %s\n", name.c_str());
    return;
  }

  int v1=0,v2=0,v3=0, v4=0;
  int Count=0;
  bool flag=false;
  string str="";
  int row=0;
  //�ǂݍ��� 
  fseek(fp,SEEK_SET,0);
  while(!feof(fp))
  {
    //�L�[���[�h �ǂݍ���
    memset(key, 0, sizeof(key));
    fscanf(fp,"%s ",key);

    if(strcmp(key, "template") == 0)	//�e���v���[�g�̍s�͒��΂�
      fgets(buf,sizeof(buf),fp);

    if(strcmp(key,"Material")==0)
    {
      if(flag)
        Materials.push_back(mtl);
      
      flag=true;
      fgets(buf,sizeof(buf),fp);//����̍s�ɂ���Ɛ���@���s����
      //�f�B�t���[�Y
      fscanf(fp,"%f;%f;%f;%f;;",&vec4d.x,&vec4d.y,&vec4d.z,&vec4d.w);
      mtl.materialColor.diffuse=(const Color4f &)vec4d;
      //SHININESS  
      fscanf(fp,"%f;",&mtl.shininess);
      //�X�y�L�����[ 
      fscanf(fp,"%f;%f;%f;;",&vec4d.x,&vec4d.y,&vec4d.z);
      mtl.materialColor.specular=(const Color4f &)vec4d;
      //�G�~�b�V�u 
      fscanf(fp,"%f;%f;%f;;",&vec4d.x,&vec4d.y,&vec4d.z);
      mtl.materialColor.ambient=(const Color4f &)vec4d;
      //�e�N�X�`���[
      fscanf(fp,"%s ",key);

      mtl.texture = NULL;      
      if(strcmp(key,"TextureFilename")==0)
      {
        fgets(buf,sizeof(buf),fp);//����̍s�ɂ���Ɛ���@���s����

        fscanf(fp,"%s",buf); //�e�N�X�`���l�[��

        string texName = buf;

        texName = spliter(texName);
        
        if(textureList.find(texName) == textureList.end())
          textureList[texName] = new SyukatsuTexture(texName.c_str());

        mtl.texture = textureList[texName];
      }
    }
    
    //���_ �ǂݍ���
    if(strcmp(key,"Mesh")==0)
    {
      fgets(buf,sizeof(buf),fp);//�f�[�^��2�s���ɂ���Ɛ���@���s����
      fgets(buf,sizeof(buf),fp);
      Count=atoi(buf);
      for(int i=0;i<Count ;i++)
      {
        fscanf(fp,"%f;%f;%f;,",&vec3d.x,&vec3d.y,&vec3d.z);
        Vertex.push_back(vec3d*(float)size);
      } 
      //���_�C���f�b�N�X�ǂݍ���  
      fgets(buf,sizeof(buf),fp);//�f�[�^��2�s���ɂ���Ɛ���@���s����
      fgets(buf,sizeof(buf),fp);
      while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//��s�΍�
      Count=atoi(buf);   
      for(int i=0;i<Count ;i++)
      {
        int dammy;
        fscanf(fp,"%d;",&dammy);
        VertexIndex.push_back(dammy);
        if(dammy == 3){
          fscanf(fp,"%d,%d,%d;,",&v1,&v2,&v3);
          VertexIndex.push_back(v1);
          VertexIndex.push_back(v2);
          VertexIndex.push_back(v3);
        } else{
          fscanf(fp,"%d,%d,%d,%d;,",&v1,&v2,&v3,&v4);
          VertexIndex.push_back(v1);
          VertexIndex.push_back(v2);
          VertexIndex.push_back(v3);
          VertexIndex.push_back(v4);
        }
      } 
    }

    //�@�� �ǂݍ���
    if(strcmp(key,"MeshNormals")==0)
    {
      row++;
      fgets(buf,sizeof(buf),fp);//�f�[�^��2�s���ɂ���Ɛ���@���s����
      fgets(buf,sizeof(buf),fp);
      Count=atoi(buf);
      for(int i=0;i<Count ;i++)
      {
        fscanf(fp,"%f;%f;%f;,",&vec3d.x,&vec3d.y,&vec3d.z);
        Normal.push_back(vec3d);
      }
      //�@���C���f�b�N�X�ǂݍ���  
      fgets(buf,sizeof(buf),fp);//�f�[�^��2�s���ɂ���Ɛ���@���s����
      fgets(buf,sizeof(buf),fp);
      while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//��s�΍�
      Count=atoi(buf);   
      for(int i=0;i<Count ;i++)
      {
        int dammy;
        fscanf(fp,"%d;",&dammy);
        NormalIndex.push_back(dammy);
        if(dammy == 3){
          fscanf(fp,"%d,%d,%d;,",&v1,&v2,&v3);
          NormalIndex.push_back(v1);
          NormalIndex.push_back(v2);
          NormalIndex.push_back(v3);
        } else{
          fscanf(fp,"%d,%d,%d,%d;,",&v1,&v2,&v3,&v4);
          NormalIndex.push_back(v1);
          NormalIndex.push_back(v2);
          NormalIndex.push_back(v3);
          NormalIndex.push_back(v4);
        }
      } 
    }

    //�e�N�X�`���[���W �ǂݍ���
    if(strcmp(key,"MeshTextureCoords")==0)
    {
      row++;
      fgets(buf,sizeof(buf),fp);//�f�[�^��2�s���ɂ���Ɛ���@���s����
      fgets(buf,sizeof(buf),fp);
      while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//��s�΍�
      Count=atoi(buf);
      for(int i=0;i<Count ;i++)
      {
        fscanf(fp,"%f;%f;,",&vec2d.u,&vec2d.v);
        uv.push_back(vec2d);
      }   
    }
    
    //�}�e���A�����X�g
    if(strcmp(key,"MeshMaterialList")==0)
    {
      row++;
      fgets(buf,sizeof(buf),fp);//����s
      fgets(buf,sizeof(buf),fp);//�}�e���A����
      fgets(buf,sizeof(buf),fp);//���X�g�v�f��
      Count=atoi(buf);
      for(int i=0;i<Count;i++)
      {
        fgets(buf,sizeof(buf),fp);
        int test=atoi(buf);
        MaterialIndex.push_back(test);
      }
    }
  }
  
  if(flag)
    Materials.push_back(mtl);

  fclose(fp);

  for(int i=0;i<Materials.size();i++){
    for(int j=0;j<VertexIndex.size();){
      if(VertexIndex[j] == 3){
        for( int k=1; k<=3; k++)
        {
          Tri.TriVer=Vertex[VertexIndex[j+k]];
          Tri.TriNor=Normal[NormalIndex[j+k]];
          Tri.TriUV=uv[VertexIndex[j+k]];
          Materials[i].triMeshes.push_back(Tri);
        }
        j+=4;
      } else {
        for( int k=1; k<=4; k++)
        {
          Quad.QuadVer=Vertex[VertexIndex[j+k]];
          Quad.QuadNor=Normal[NormalIndex[j+k]];
          Quad.QuadUV=uv[VertexIndex[j+k]];
          Materials[i].quadMeshes.push_back(Quad);
        }
        j+=5;
      }
    }
  } 
  return;
}

//�`��
void XfileModel::render(const float alpha)const
{
  glPushAttrib(GL_COLOR_MATERIAL | GL_CURRENT_BIT | GL_ENABLE_BIT);  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA_TEST); //�A���t�@�e�X�g�J�n
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  for(auto mat : Materials)
  {
    glPushMatrix();


    if(alpha != -1)
    {
      Material _mat = mat;
      _mat.materialColor.ambient.a = alpha;
      _mat.materialColor.diffuse.a = alpha;
      _mat.materialColor.specular.a = alpha;
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT , (const GLfloat*)&_mat.materialColor.ambient);
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE , (const GLfloat*)&_mat.materialColor.diffuse);
      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (const GLfloat*)&_mat.materialColor.specular);
      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, mat.shininess);

    }
    else
    {
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT , (const GLfloat*)&mat.materialColor.ambient);
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE , (const GLfloat*)&mat.materialColor.diffuse);
      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (const GLfloat*)&mat.materialColor.specular);
      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, mat.shininess);
    }
    
    if(mat.texture != NULL){
      mat.texture->bind();
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }else{
      glDisable(GL_TEXTURE_2D);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if(mat.triMeshes.size()>1)
    {
      glVertexPointer(3, GL_FLOAT, sizeof(Triangle) , &mat.triMeshes[0].TriVer.x);
      glNormalPointer(   GL_FLOAT, sizeof(Triangle) , &mat.triMeshes[0].TriNor.x);
      
      if(mat.texture != NULL)      
        glTexCoordPointer(2, GL_FLOAT, sizeof(Triangle), &mat.triMeshes[0].TriUV.u);
      
      
      glDrawArrays(GL_TRIANGLES, 0, mat.triMeshes.size());
    }
    
    if(mat.quadMeshes.size()>1){      
      glVertexPointer(3, GL_FLOAT,sizeof(Quadrangle) , &mat.quadMeshes[0].QuadVer.x);
      glNormalPointer(   GL_FLOAT,sizeof(Quadrangle) , &mat.quadMeshes[0].QuadNor.x);
      if(mat.texture != NULL)
         glTexCoordPointer(2, GL_FLOAT, sizeof(Quadrangle), &mat.quadMeshes[0].QuadUV.u);
      glDrawArrays(GL_QUADS,0,mat.quadMeshes.size());
    }
    glPopMatrix();   
  }  
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST); //�A���t�@�e�X�g�J�n
  glPopAttrib();  
}
*/
