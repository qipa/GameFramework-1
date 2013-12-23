#include <XfileModel.h>
#include <GLFWTexture.h>
#include <GL/freeglut.h>
#include <iostream>
#include <regex>
#include <string>
#include <cstring>
using namespace std;

XfileModel::XfileModel(const char *fileName, float size)
  :Model(fileName)
{
  load(fileName, size);
}

void XfileModel::load(const char *fileName, float size)
{
  Vector3f vec3d;
  Vector4f vec4d;
  UV vec2d;
  Triangle Tri;
  Quadrangle Quad;
  Material mtl;

  vector <Vector3f> Vertex;//頂点
  vector <Vector3f> Normal;//法線
  vector <UV> uv;//UV
  vector <int> VertexIndex;
  vector <int> NormalIndex;
  vector <int> MaterialIndex;

  char key[255];
  char buf[255];
  //Xファイルを開いて内容を読み込む
  FILE* fp=NULL;

  if( (fp = fopen(fileName, "rt")) == NULL)
  {
    cout << "can not open file" << endl;
    return;
  }

  int v1=0,v2=0,v3=0, v4=0;
  int Count=0;
  bool flag=false;
  string str="";
  int row=0;
  //読み込み 
  fseek(fp,SEEK_SET,0);
  while(!feof(fp))
  {
    //キーワード 読み込み
    memset(key, 0, sizeof(key));
    fscanf(fp,"%s ",key);

    if(strcmp(key, "template") == 0)	//テンプレートの行は跳ばす
      fgets(buf,sizeof(buf),fp);

    if(strcmp(key,"Material")==0)
    {
      if(flag)
        Materials.push_back(mtl);
      
      flag=true;
      fgets(buf,sizeof(buf),fp);//直後の行にあると推定　改行する
      //ディフューズ
      fscanf(fp,"%f;%f;%f;%f;;",&vec4d.x,&vec4d.y,&vec4d.z,&vec4d.w);
      mtl.materialColor.diffuse=(const Color4f &)vec4d;
      //SHININESS  
      fscanf(fp,"%f;",&mtl.shininess);
      //スペキュラー 
      fscanf(fp,"%f;%f;%f;;",&vec4d.x,&vec4d.y,&vec4d.z);
      mtl.materialColor.specular=(const Color4f &)vec4d;
      //エミッシブ 
      fscanf(fp,"%f;%f;%f;;",&vec4d.x,&vec4d.y,&vec4d.z);
      mtl.materialColor.ambient=(const Color4f &)vec4d;
      //テクスチャー
      fscanf(fp,"%s ",key);

      mtl.texture = NULL;      
      if(strcmp(key,"TextureFilename")==0)
      {
        fgets(buf,sizeof(buf),fp);//直後の行にあると推定　改行する

        fscanf(fp,"%s",buf); //テクスチャネーム

        string texName = buf;
        regex pat("\".+\"");
        smatch res;
        regex_search(texName, res, pat, regex_constants::match_default);
        texName = res.str().substr(1, res.str().size()-2);                
        
        if(textureList.find(texName) == textureList.end())
          textureList[texName] = new GLFWTexture(texName.c_str());

        mtl.texture = textureList[texName];
      }
    }
    
    //頂点 読み込み
    if(strcmp(key,"Mesh")==0)
    {
      fgets(buf,sizeof(buf),fp);//データは2行下にあると推定　改行する
      fgets(buf,sizeof(buf),fp);
      Count=atoi(buf);
      for(int i=0;i<Count ;i++)
      {
        fscanf(fp,"%f;%f;%f;,",&vec3d.x,&vec3d.y,&vec3d.z);
        Vertex.push_back(vec3d*(float)size);
      } 
      //頂点インデックス読み込み  
      fgets(buf,sizeof(buf),fp);//データは2行下にあると推定　改行する
      fgets(buf,sizeof(buf),fp);
      while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//空行対策
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

    //法線 読み込み
    if(strcmp(key,"MeshNormals")==0)
    {
      row++;
      fgets(buf,sizeof(buf),fp);//データは2行下にあると推定　改行する
      fgets(buf,sizeof(buf),fp);
      Count=atoi(buf);
      for(int i=0;i<Count ;i++)
      {
        fscanf(fp,"%f;%f;%f;,",&vec3d.x,&vec3d.y,&vec3d.z);
        Normal.push_back(vec3d);
      }
      //法線インデックス読み込み  
      fgets(buf,sizeof(buf),fp);//データは2行下にあると推定　改行する
      fgets(buf,sizeof(buf),fp);
      while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//空行対策
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

    //テクスチャー座標 読み込み
    if(strcmp(key,"MeshTextureCoords")==0)
    {
      row++;
      fgets(buf,sizeof(buf),fp);//データは2行下にあると推定　改行する
      fgets(buf,sizeof(buf),fp);
      while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//空行対策
      Count=atoi(buf);
      for(int i=0;i<Count ;i++)
      {
        fscanf(fp,"%f;%f;,",&vec2d.u,&vec2d.v);
        uv.push_back(vec2d);
      }   
    }
    
    //マテリアルリスト
    if(strcmp(key,"MeshMaterialList")==0)
    {
      row++;
      fgets(buf,sizeof(buf),fp);//空改行
      fgets(buf,sizeof(buf),fp);//マテリアル数
      fgets(buf,sizeof(buf),fp);//リスト要素数
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

//描画
void XfileModel::render()const
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA_TEST); //アルファテスト開始
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  for(auto mat : Materials)
  {
    glPushMatrix();
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT , (const GLfloat*)&mat.materialColor.ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE , (const GLfloat*)&mat.materialColor.diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (const GLfloat*)&mat.materialColor.specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, mat.shininess);
    
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
  glDisable(GL_ALPHA_TEST); //アルファテスト開始
}
