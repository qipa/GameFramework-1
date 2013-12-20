#ifndef TEST_SCENE1_H_2013_12_20
#define TEST_SCENE1_H_2013_12_20

#include "../include/glfw/GLFWScene.h"
#include "../include/glfw/GLFW/glfw3.h"
#include "../include/glfw/Camera3D.h"
#include "SimpleObjectFactory.h"

class TestScene1 :public GLFWScene
{
  Camera3D *camera;
  Vector3 pos;
  Vector2 target;
  const int cellSize;
  const int cellNum;
  float theta, phi;
public:
  TestScene1(GLFWGame* glfwGame)
    :GLFWScene(glfwGame)
    ,cellSize(10)
    ,cellNum(10)
  {
    camera = new Camera3D(glfwGame->getWindow(), 1, 1000, 45); //near, far, 視野角
    camera->setPosition( Vector3(100, 0, 0) );
    camera->setLook(Vector3(0,0,0));

    theta = phi = 0;
    //画面右半分
    int width, height;
    glfwGetFramebufferSize(glfwGame->getWindow(), &width, &height); //windowサイズを取得    
//    camera->setViewportWidth(width/2);
//    camera->setViewportPosition(width/4*3, height/2); //viewの中心位置(画面上での)

    pos.set(0,0,0);
  }

  ~TestScene1(){}
  
  void update(float deltaTime);
  
  void render(float deltaTime)
  {
    camera->setViewportAndMatrices();

    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
    glEnable(GL_LIGHTING);    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_DEPTH_TEST);
    
    GLfloat color[]     = {    1.0,    1.0,    1.0, 1.0 };
    GLfloat lightpos1[] = {  200.0, -200.0, -200.0, 1.0 };
    GLfloat lightpos2[] = { -200.0,  200.0,  200.0, 1.0 };
    GLfloat lightpos3[] = { -200.0, -200.0, -200.0, 1.0 };
    GLfloat lightpos4[] = {  200.0,  200.0,  200.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
    
    glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT3, GL_POSITION, lightpos4);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, color);


    glColor3f(1,1,1);
    drawAxis();
    
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef((float) glfwGetTime() * 50.f, glfwGetTime(), glfwGetTime()*2, glfwGetTime()*3);
    glutSolidCube(5);    
    glPopMatrix();
    /*
    glPushMatrix();
    for(int i=0; i<cellNum; i++)
    {
      glPushMatrix();
      for(int j=0; j<cellNum; j++)
      {
        glutSolidCube(5);
        glTranslatef(0,0,cellSize);
      }
      glPopMatrix();
      glTranslatef(cellSize,0,0);
    }
    glPopMatrix();
    */
    glPopAttrib();
  }
  
  void reshape(int width, int height)
  {
   
  }
  
  void dispose() 
  {
  }
};

#endif
