#ifndef KEYBOAD_HANDLER_H_2013_12_16
#define KEYBOAD_HANDLER_H_2013_12_16

#include "../Input.h"
#include "../Pool.h"
#include "../Lock.h"
#include <vector>
#include <pthread.h>
#include <cstring>
using namespace std;

class KeyboadHandler
{
  class KeyEventFactory:public PoolObjectFactory<KeyEvent>
  {
    KeyEvent* createObject()
    {
      return new KeyEvent();
    }
  };

  static constexpr int keyMapSize = 350; //GLFWのキー定数の最大数
  int pressedKeys[keyMapSize];

  Pool<KeyEvent> *keyEventPool;
  vector<KeyEvent*> keyEvents;
  vector<KeyEvent*> keyEventBuffer;
  pthread_mutex_t lock;

public:  
  KeyboadHandler();   
  ~KeyboadHandler();  
  bool isAnyKeyPressed();
  bool isKeyPressed(int keyCode);  
  int getKeyState(int keyCode);
  const vector<KeyEvent*>& getKeyEvents();  
  void onEvent(int keyCode, int action, int mods);
  void update();
};

#endif
