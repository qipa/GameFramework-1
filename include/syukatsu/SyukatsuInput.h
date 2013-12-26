#ifndef SYUKATSU_INPUT_H_2013_12_16
#define SYUKATSU_INPUT_H_2013_12_16
#include "GLFW/glfw3.h"

#include "../Input.h"
#include "KeyboadHandler.h"
#include "MouseHandler.h"
#include "ScrollHandler.h"

class SyukatsuInput : public Input
{  
  GLFWwindow *window;
  MouseHandler   *mouseHandler;
  KeyboadHandler *keyboadHandler;
  ScrollHandler   *scrollHandler;  
public:
SyukatsuInput(GLFWwindow *_window)
  :window(_window)
  {
    mouseHandler   = new MouseHandler(window);
    keyboadHandler = new KeyboadHandler();
scrollHandler = new ScrollHandler();
  }
  
  ~SyukatsuInput()
  {
    delete mouseHandler;
    delete keyboadHandler;
delete scrollHandler;
  }

  void update()
  {
    keyboadHandler->update();
    mouseHandler->update();
scrollHandler->update();
  }  
  
  bool isKeyPressed(int keyCode)
  {
    return keyboadHandler->isKeyPressed(keyCode);
  }

  int getKeyState(int keyCode)
  {
    return keyboadHandler->getKeyState(keyCode);
  }  
  
  const vector<KeyEvent*>& getKeyEvents()
  {
    return keyboadHandler->getKeyEvents();
  }
  
  MouseEvent* const getMouseEvent()
  {
    return mouseHandler->getMouseEvent();
  }

ScrollEvent* const getScrollEvent()
{
return scrollHandler->getScrollEvent();
}


  void getCursorPos(double &x, double &y)
  {
    glfwGetCursorPos(window, &x, &y);
  }
  
  void onMouse(int button, int action, int mods)
  {
    mouseHandler->onEvent(button, action, mods);
  }

  void onKey(int keyCode, int action, int mods)
  {
    keyboadHandler->onEvent(keyCode, action, mods);
  }

void onScroll(double offsetX, double offsetY)
{
scrollHandler->onEvent(offsetX, offsetY);
}

};

#endif
