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

  float edge = 900;

  GLfloat lightpos1[] = { 0.0, edge/2, 0.0, 1.0 };
  GLfloat lightdir1[] = { 1.0, -1.0, 1.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightdir1);
  
  GLfloat lightpos2[] = { edge, edge/2, edge, 1.0 };
  GLfloat lightdir2[] = { -1.0, -1.0, -1.0, 1.0 };
  glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightdir2);
 
  GLfloat lightpos3[] = { 0.0, edge/2, edge, 1.0 };
  GLfloat lightdir3[] = { 1.0, -1.0, -1.0, 1.0 };
  glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightdir3);
 
  GLfloat lightpos4[] = { edge, edge/2, 0.0, 1.0 };
  GLfloat lightdir4[] = { -1.0, -1.0, 1.0, 1.0 };
  glLightfv(GL_LIGHT4, GL_POSITION, lightpos4);
  glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lightdir4); 
}

XfileModelTestScene::XfileModelTestScene(SyukatsuGame *game)
  :SyukatsuScene(game)
{
  camera = new Camera3D(syukatsuGame->getWindow(), 1, 1000, 45);
  camera->setPosition( Vector3(500, 500, 500) );
  camera->setLook(Vector3(0,0,0));

  camera2 = new Camera2D(syukatsuGame->getWindow(), 4, 4);

  int width, height;
  glfwGetFramebufferSize(syukatsuGame->getWindow(), &width, &height);  
  camera2->setViewportWidth(width/4);
  camera2->setViewportHeight(height/4);
  camera2->setViewportPosition(width/8, height/8);
  batcher = new SpriteBatcher(10);

//  model = new TestXfileModel("dragon2.x", 1);
  model = new TestXfileModel("sampleModel.x", 1);
  
  texture = new SyukatsuTexture("mone._tex.png");
  region = new TextureRegion(texture);

  theta = phi = 0;
  // LightSetting();
}

void XfileModelTestScene::update(float deltaTime)
{
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
      theta -= 100*deltaTime;
      if(theta<0) theta+=2*M_PI;
      break;
    case GLFW_KEY_RIGHT:
      theta += 100*deltaTime;
      if(theta>2*M_PI) theta-=2*M_PI;
      break;
    case GLFW_KEY_UP:
      phi = min(phi+100*deltaTime, (float)M_PI/3.8f);
      break;
    case GLFW_KEY_DOWN:
      phi = min(phi-100*deltaTime, 0.0f);
      break;
    case GLFW_KEY_T:
      theta = 0;
      break;
    case GLFW_KEY_P:
      phi = 0;
      break;
    }
  }
  float R = 800;
  camera->setPosition(Vector3(R*cos(phi)*cos(theta), R*sin(phi), R*cos(phi)*sin(theta)));
}

void XfileModelTestScene::render(float deltaTime)
{
  camera->setViewportAndMatrices();
  
  glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);

  glEnable(GL_DEPTH_TEST);
  
  drawAxis();
  model->render();
  glPopAttrib();

  camera2->setViewportAndMatrices();
  batcher->beginBatch(texture);
  batcher->drawSprite(0,0, 4, 4, region);
  batcher->endBatch();
}
