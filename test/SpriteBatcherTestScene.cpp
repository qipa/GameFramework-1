#include "SpriteBatcherTestScene.h"
#include "TestListsScene.h"

SpriteBatcherTestScene::SpriteBatcherTestScene(GLFWGame *glfwGame)
  :GLFWScene(glfwGame),
   WIDTH(4.8),
   HEIGHT(3.2)
{    
  camera = new Camera2D(glfwGame->getWindow(), SpriteBatcherTestScene::WIDTH, SpriteBatcherTestScene::HEIGHT);
  batcher = new SpriteBatcher(100); //最大100
  texture = new GLFWTexture("textureAtlas.png");
  region = new TextureRegion(texture, 0, 0, 256, 256);
}

void SpriteBatcherTestScene::update(float deltaTime)
{
  auto keyEvents = glfwGame->getInput()->getKeyEvents();
  for(auto event : keyEvents)
  {
    if(event->action != GLFW_PRESS || event->keyCode != GLFW_KEY_ENTER)
      continue;
    glfwGame->setScene(new TestListsScene(glfwGame));
    return;    
  }  
}

void SpriteBatcherTestScene::render(float deltaTime)
{   
  camera->setViewportAndMatrices();
  batcher->beginBatch(texture);
  batcher->drawSprite(0, 0, WIDTH, HEIGHT, region);
  batcher->endBatch();
}
  

