#ifndef KEYBOAD_HANDLER_H_2013_12_16
#define KEYBOAD_HANDLER_H_2013_12_16

#include "../Input.h"
#include "../Pool.h"
#include "../Lock.h"
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
  
  bool pressedKeys[350];
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
  
  ~KeyboadHandler()
  {
    delete keyEventPool;
  }
  
  bool isKeyPressed(int keyCode)
  {
    Lock lck(&lock); //ロック
    return pressedKeys[keyCode] == GLFW_PRESS;
  }

  int getKeyState(int keyCode)
  {
    Lock lck(&lock);
    return pressedKeys[keyCode];    
  }
  

  //ループの最初に一回だけ呼び出す
  const vector<KeyEvent*>& getKeyEvents()
  {
    //他の関数ではkeyEventPoolは当たらないので, ロックする必要なし
    for(auto event : keyEvents)
      keyEventPool->freeObject(event);
    
    keyEvents.clear();

    Lock lck(&lock); //ロック デストラクタでアンロックする
        
    keyEvents.insert(keyEvents.end(), keyEventBuffer.begin(), keyEventBuffer.end());
    keyEventBuffer.clear();    

    return keyEvents; 
  }
  
  void onEvent(int keyCode, int action, int mods)
  {
    KeyEvent *event = keyEventPool->newObject();
    event->keyCode = keyCode;
    event->action = action;

    Lock lck(&lock); //ロック

    if(keyCode>=0 && keyCode<350)
      pressedKeys[keyCode] = action;
    
    keyEventBuffer.push_back(event);
  }
  
};

#endif
