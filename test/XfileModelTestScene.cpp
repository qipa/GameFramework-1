#include "XfileModelTestScene.h"
#include "TestListsScene.h"

//光源の設定
static void LightSetting()
{
  glEnable(GL_LIGHTING);    
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);

  float edge = -900;

  for(float i=-1; i<2; i+=2)
    for(float j=-1; j<2; j+=2)
        for(float k=-1; k<2; k+=2)
        {
          GLfloat lightpos[] = { i*edge/2, j*edge/2, k*edge/2, 1.0 };
          GLfloat lightdir[] = { -i, -j, -k, 1.0 };
          int ind = 2*(i+1) + (j+1) + (k+1)/2;
          glLightfv(GL_LIGHT0+ind, GL_POSITION, lightpos);
          glLightfv(GL_LIGHT0+ind, GL_SPOT_DIRECTION, lightdir);

        }
  /*
  GLfloat lightpos1[] = { 0.0, edge/2, 0.0, 1.0 };
  GLfloat lightdir1[] = { 1.0, 1.0, 1.0, 1.0 };
  
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightdir1);
  
  GLfloat lightpos2[] = { edge, edge/2, edge, 1.0 };
  GLfloat lightdir2[] = { -1.0, 1.0, -1.0, 1.0 };
  glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightdir2);
 
  GLfloat lightpos3[] = { 0.0, edge/2, edge, 1.0 };
  GLfloat lightdir3[] = { 1.0, 1.0, -1.0, 1.0 };
  glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightdir3);
 
  GLfloat lightpos4[] = { edge, edge/2, 0.0, 1.0 };
  GLfloat lightdir4[] = { -1.0, 1.0, 1.0, 1.0 };
  glLightfv(GL_LIGHT4, GL_POSITION, lightpos4);
  glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lightdir4); 
  */
}

XfileModelTestScene::XfileModelTestScene(SyukatsuGame *game)
  :SyukatsuScene(game)
{
  camera = new Camera3D(syukatsuGame->getWindow(), 1, 10000, 120);
  camera->setPosition( Vector3(500, 500, 500) );
  camera->setLook(Vector3(0,0,0));

  camera2 = new Camera2D(syukatsuGame->getWindow(), 4, 4);

  int width, height;
  glfwGetFramebufferSize(syukatsuGame->getWindow(), &width, &height);  
  camera2->setViewportWidth(width/4);
  camera2->setViewportHeight(height/4);
  camera2->setViewportPosition(width/8, height/8);
  batcher = new SpriteBatcher(10);

  model = new TestXfileModel("dragon.x", 1);
//  model = new TestXfileModel("field.x", 1);
  for (auto mtl : model->materials )
  {
    cout << mtl.meshes.size() << endl;
  }
  
  texture = new SyukatsuTexture("mone._tex.png");
  region = new TextureRegion(texture);

  theta = phi = 0;
  LightSetting();
}

void XfileModelTestScene::update(float deltaTime)
{
  static float R = 800;
  auto keyEvents = syukatsuGame->getInput()->getKeyEvents();
  for (auto event : keyEvents)
  { 
    switch(event->keyCode)
    {
    case GLFW_KEY_ENTER:
      if(event->action != GLFW_PRESS)  continue;
      syukatsuGame->setScene(new TestListsScene(syukatsuGame));
      return;
    case GLFW_KEY_LEFT:
      theta -= 10*deltaTime;
      if(theta<0) theta+=2*M_PI;
      break;
    case GLFW_KEY_RIGHT:
      theta += 10*deltaTime;
      if(theta>2*M_PI) theta-=2*M_PI;
      break;
    case GLFW_KEY_UP:
      phi = min(phi+10*deltaTime, (float)M_PI/3.8f);
      break;
    case GLFW_KEY_DOWN:
      phi = min(phi-10*deltaTime, 0.0f);
      break;
    case GLFW_KEY_T:
      theta = 0;
      break;
    case GLFW_KEY_P:
      phi = 0;
      break;
    case GLFW_KEY_W:
      R -= 1000*deltaTime;
      break;
    case GLFW_KEY_S:
      R += 1000*deltaTime;
      break;
    }
  }

  camera->setPosition(Vector3(R*cos(phi)*cos(theta), R*sin(phi), R*cos(phi)*sin(theta)));
}

void XfileModelTestScene::render(float deltaTime)
{
  camera->setViewportAndMatrices();
  
  glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  drawAxis();
  model->render();
  glPopAttrib();

  camera2->setViewportAndMatrices();
  batcher->beginBatch(texture);
  batcher->drawSprite(0,0, 4, 4, region);
  batcher->endBatch();
}
