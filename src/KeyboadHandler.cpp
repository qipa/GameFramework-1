#include <KeyboadHandler.h>
#include <GLFW/glfw3.h>

KeyboadHandler::KeyboadHandler()
{
  const int maxKeyEvent = 15;  
  keyEventPool = new Pool<KeyEvent>(new KeyEventFactory(), maxKeyEvent);
  for(int i=0; i<keyMapSize ;i++)
    pressedKeys[i] = GLFW_RELEASE;  

  keyEvents.reserve(maxKeyEvent);
  keyEventBuffer.reserve(maxKeyEvent);
  
  pthread_mutex_init(&lock, NULL);
}
  
KeyboadHandler::~KeyboadHandler()
{
  delete keyEventPool;
}

bool KeyboadHandler::isAnyKeyPressed()
{
  Lock lck(&lock);
  for(int i = 0; i < keyMapSize; ++i) {
    if(pressedKeys[i] == GLFW_PRESS) return true;
  }

  return false;
}
  
bool KeyboadHandler::isKeyPressed(int keyCode)
{
  Lock lck(&lock); //ロック
  if(keyCode < 0 || keyCode>=keyMapSize)
    return false;
  
  return pressedKeys[keyCode] == GLFW_PRESS;
}

int KeyboadHandler::getKeyState(int keyCode)
{
  Lock lck(&lock);  
  if(keyCode < 0 || keyCode>=keyMapSize)
    return GLFW_KEY_UNKNOWN;
  
  return pressedKeys[keyCode];    
}

//ループの最初に一回だけ呼び出す
const vector<KeyEvent*>& KeyboadHandler::getKeyEvents()
{
  Lock lck(&lock); //ロック デストラクタでアンロックする  
  return keyEvents; 
}
  
void KeyboadHandler::onEvent(int keyCode, int action, int mods)
{
  Lock lck(&lock); //ロック
  
  //KeyEventで定義している定数ががGLFWの定数と同じなのでそのまま代入
  KeyEvent *event = keyEventPool->newObject();
  event->keyCode = keyCode;
  event->action = action;
  event->modifier = mods;
    
  keyEventBuffer.push_back(event);
}

#include <iostream>
using namespace std;

void KeyboadHandler::update()
{
  Lock lck(&lock); //ロック デストラクタでアンロックする        

  for(auto event : keyEvents)
    keyEventPool->freeObject(event);
  keyEvents.clear();

  for(int i=0; i<keyMapSize; i++)
  {    
    if(pressedKeys[i] == GLFW_PRESS)    
      pressedKeys[i] = GLFW_REPEAT;
  }  
  
  for( auto event : keyEventBuffer)
  {
    pressedKeys[event->keyCode] = event->action;   
  }  
  keyEvents.insert(keyEvents.end(), keyEventBuffer.begin(), keyEventBuffer.end());
  keyEventBuffer.clear();
}

