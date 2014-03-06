#include <mutex>
#include <KeyboadHandler.h>
#include <GLFW/glfw3.h>

namespace
{
  std::mutex mtx_lock;
}

KeyboadHandler::KeyboadHandler()
{
  const int maxKeyEvent = 15;  
  keyEventPool = new Pool<KeyEvent>(new KeyEventFactory(), maxKeyEvent);
  for(int i=0; i<keyMapSize ;i++)
    pressedKeys[i] = GLFW_RELEASE;  

  keyEvents.reserve(maxKeyEvent);
  keyEventBuffer.reserve(maxKeyEvent);
}
  
KeyboadHandler::~KeyboadHandler()
{
  delete keyEventPool;
}

bool KeyboadHandler::isAnyKeyPressed()
{
  std::lock_guard<std::mutex> lock(mtx_lock);

  for(auto event : keyEvents)
  {
    if(event->action == GLFW_PRESS)
      return true;
  }

  return false;
}
  
bool KeyboadHandler::isKeyPressed(int keyCode)
{
  std::lock_guard<std::mutex> lock(mtx_lock);
  
  if(keyCode < 0 || keyCode>=keyMapSize)
    return false;
  
  return pressedKeys[keyCode] == GLFW_PRESS;
}

int KeyboadHandler::getKeyState(int keyCode)
{
  std::lock_guard<std::mutex> lock(mtx_lock);

  if(keyCode < 0 || keyCode>=keyMapSize)
    return GLFW_KEY_UNKNOWN;
  
  return pressedKeys[keyCode];    
}

//ループの最初に一回だけ呼び出す
const vector<KeyEvent*>& KeyboadHandler::getKeyEvents()
{
  std::lock_guard<std::mutex> lock(mtx_lock);
  
  return keyEvents; 
}
  
void KeyboadHandler::onEvent(int keyCode, int action, int mods)
{
  std::lock_guard<std::mutex> lock(mtx_lock);
  
  //KeyEventで定義している定数ががGLFWの定数と同じなのでそのまま代入
  KeyEvent *event = keyEventPool->newObject();
  event->keyCode = keyCode;
  event->action = action;
  event->modifier = mods;
    
  keyEventBuffer.push_back(event);
}

void KeyboadHandler::update()
{
  std::lock_guard<std::mutex> lock(mtx_lock);  

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

