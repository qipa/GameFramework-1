#ifndef KEYBOAD_HANDLER_H_2013_12_16
#define KEYBOAD_HANDLER_H_2013_12_16

#include "../Input.h"
#include "../Pool.h"
#include <vector>
#include <cstring>

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
  std::vector<KeyEvent*> keyEvents;
  std::vector<KeyEvent*> keyEventBuffer;

public:  
  KeyboadHandler();   
  ~KeyboadHandler();  
  bool isAnyKeyPressed();
  bool isKeyPressed(int keyCode);  
  int getKeyState(int keyCode);
  const std::vector<KeyEvent*>& getKeyEvents();  
  void onEvent(int keyCode, int action, int mods);
  void update();
};

#endif
