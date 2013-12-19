#ifndef KEYBOAD_HANDLER_H_2013_12_16
#define KEYBOAD_HANDLER_H_2013_12_16

#include "../Input.h"
#include "../Pool.h"

#include <vector>
#include <pthread.h>

class KeyboadHandler
{
  class KeyEventFactory:public PoolObjectFactory<KeyEvent>
  {
    KeyEvent* createObject()
    {
      return new KeyEvent();
    }

    void initializeObject(KeyEvent* object)
    {      
    }
  };
  
  bool pressedKeys[128];
  Pool<KeyEvent> *keyEventPool;
  vector<KeyEvent*> keyEvents;
  vector<KeyEvent*> keyEventBuffer;
  pthread_mutex_t lock;
  
public:
  KeyboadHandler()
  {
    keyEventPool = new Pool<KeyEvent>(new KeyEventFactory(), 30);
    pthread_mutex_init(&lock, NULL);
  }
  
  bool isKeyPressed(int keyCode)
  {
    bool res;
    
    pthread_mutex_lock(&lock);    
    res = pressedKeys[keyCode];    
    pthread_mutex_unlock(&lock);
    
    return res;
  }

  //ループの最初に一回だけ呼び出す
  const vector<KeyEvent*>& getKeyEvents()
  {
    //他の関数ではkeyEventPoolは当たらないので, ロックする必要なし
    for(auto event : keyEvents)
      keyEventPool->freeObject(event);    
    keyEvents.clear();

    pthread_mutex_lock(&lock);
    keyEvents.insert(keyEvents.end(), keyEventBuffer.begin(), keyEventBuffer.end());
    keyEventBuffer.clear();

    pthread_mutex_unlock(&lock);

    //keyEventsはこの関数でしか使ってないから, ロックの外に出ても大丈夫だと思う
    return keyEvents; 
  }
  
  void onEvent(int keyCode, int action, int mods)
  {
    KeyEvent *event = keyEventPool->newObject();
    event->keyCode = keyCode;
    event->action = action;
    
    pthread_mutex_lock(&lock);
    
    if(action == GLFW_PRESS && keyCode>=0 && keyCode < 128)
    {
      pressedKeys[keyCode] = true;
    }
    else if(action == GLFW_RELEASE && keyCode>=0 && keyCode < 128)
    {
      pressedKeys[keyCode] = false;
    }
    
    keyEventBuffer.push_back(event);    
    pthread_mutex_unlock(&lock);
  } 
};

#endif
