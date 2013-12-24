#include "XfileModelTestScene.h"
#include "TestListsScene.h"

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

  model = new XfileModel("sampleModel.x", 1);
  texture = new SyukatsuTexture("mone._tex.png");
  region = new TextureRegion(texture);

  theta = phi = 0;  
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
