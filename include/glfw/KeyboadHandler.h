#ifndef KEYBOAD_HANDLER_H_2013_12_16
#define KEYBOAD_HANDLER_H_2013_12_16

#include "../Input.h"
#include "../Pool.h"

#include <vector>
#include <pthread.h>

class KeyboadHandler
{
  bool pressedKeys[128];
  Pool<KeyEvent> *keyEventPool;
  vector<KeyEvent*> keyEvents;
  vector<KeyEvent*> keyEventBuffer;
  pthread_mutex_t lock;
  
public:
  KeyboadHandler();
  const inline bool isKeyPressed(int keyCode) const;
  const vector<KeyEvent*>& getKeyEvents();
  void onKey(int keyCode, int action);
};

#endif
