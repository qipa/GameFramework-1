#include "SpriteBatcherTestScene.h"
#include "TestListsScene.h"
#include "Assets.h"

SpriteBatcherTestScene::SpriteBatcherTestScene(GLFWGame *glfwGame)
  :GLFWScene(glfwGame),
   WIDTH(4.8),
   HEIGHT(3.2)
{    
  camera = new Camera2D(glfwGame->getWindow(), SpriteBatcherTestScene::WIDTH, SpriteBatcherTestScene::HEIGHT);
  batcher = new SpriteBatcher(100); //最大100
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
  
  batcher->beginBatch(Assets::textureAtlas);  //このテクスチャアトラスを使う宣言
  float dx = WIDTH/10;
  float dy = HEIGHT/10;  
  for(int i=-5; i<5; i++)
  {    
    for(int j=-5; j<5; j++)
    {
      batcher->drawSprite((i+0.5)*dx, (j+0.5)*dy, dx, dy, Assets::virus);  //テクスチャの1部分(リージョン)を描画すると伝える
    }
  } 
  batcher->endBatch();  //最後に一括してGPUに送る
}
  

