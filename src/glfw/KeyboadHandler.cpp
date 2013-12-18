#include "KeyboadHandler.h"
#include <GLFW/glfw3.h>

KeyboadHandler::KeyboadHandler()
{
  class KeyEventFactory:public PoolObjectFactory<KeyEvent>
  {
    inline KeyEvent* createObject()
    {
      return new KeyEvent();
    }

    inline void initializeObject(KeyEvent *object)
    {
    }
  };
  memset(pressedKeys, 0, sizeof(pressedKeys));
  KeyEventFactory *factory = new KeyEventFactory();
  keyEventPool = new Pool<KeyEvent>(factory, 50);    //同時に押すキーは50個もあれば多分十分

  pthread_mutex_init(&lock, NULL);
};

const inline bool KeyboadHandler::isKeyPressed(int keyCode) const
{
  if(keyCode<0 || keyCode>127)
    return false;
  return pressedKeys[keyCode];
}

const vector<KeyEvent*>& KeyboadHandler::getKeyEvents()
{
  pthread_mutex_lock(&lock);    //排他制御

  int len = keyEvents.size();
  for(int i=0; i<len; i++)    
    keyEventPool->freeObject(keyEvents[i]);
    
  keyEvents.clear();
  keyEvents.insert(keyEvents.end(), keyEventBuffer.begin(), keyEventBuffer.end());
    
  pthread_mutex_unlock(&lock);

  return keyEvents; //ここで, 同時処理が起きると困る?
}

void onKey(int keyCode, int action);

void KeyboadHandler::onKey(int keyCode, int action)
{
  pthread_mutex_lock(&lock);
  KeyEvent *keyEvent = keyEventPool->newObject();
  keyEvent->keyCode = keyCode;
  keyEvent->action = action;

  if(keyCode >= 0 || keyCode < 128)
    pressedKeys[keyCode] = (action == GLFW_PRESS); //PRESSで無ければ, RELEASEのはず!
  keyEventBuffer.push_back(keyEvent);
  pthread_mutex_unlock(&lock);  
}


