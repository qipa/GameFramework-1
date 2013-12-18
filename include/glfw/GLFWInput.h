#ifndef GLFWInput_H_2013_12_16
#define GLFWInput_H_2013_12_16

#include "../Input.h"
#include "GLFW/glfw3.h"

class GLFWInput : public Input
{
  vector<KeyEvent*> keyEventBuffer;
  vector<MouseEvent*> mouseEventBuffer;
public:
  GLFWInput();
  bool isKeyPressed(int keyCode)
  {
    //todo
    return false;
  }
  
  const vector<KeyEvent*>& getKeyEvents()
  {
    //todo
    return keyEventBuffer;
  }
  
  const vector<MouseEvent*>& getMouseEvents()
  {
    //todo
    return mouseEventBuffer;
  }
};

#endif
