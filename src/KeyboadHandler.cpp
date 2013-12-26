#include <KeyboadHandler.h>
#include <GLFW/glfw3.h>

KeyboadHandler::KeyboadHandler()
{
  const int maxKeyEvent = 15;  
  keyEventPool = new Pool<KeyEvent>(new KeyEventFactory(), maxKeyEvent);
  for(int i=0; i<keyMapSize ;i++)
    pressedKeys[i] = false;    

  keyEvents.reserve(maxKeyEvent);
  keyEventBuffer.reserve(maxKeyEvent);
  
  pthread_mutex_init(&lock, NULL);
}
  
KeyboadHandler::~KeyboadHandler()
{
  delete keyEventPool;
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
  
  if( keyCode >= 0 && keyCode < keyMapSize)
    pressedKeys[keyCode] = action;
    
  keyEventBuffer.push_back(event);
}

void KeyboadHandler::update()
{
  Lock lck(&lock); //ロック デストラクタでアンロックする        

  for(auto event : keyEvents)
    keyEventPool->freeObject(event);
  keyEvents.clear();

  keyEvents.insert(keyEvents.end(), keyEventBuffer.begin(), keyEventBuffer.end());
  keyEventBuffer.clear();
}

