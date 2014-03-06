#ifndef MOUSE_HANDLER_H_2013_12_19
#define MOUSE_HANDLER_H_2013_12_19

#include "../Input.h"
#include "../Pool.h"
#include "GLFW/glfw3.h"

class MouseHandler
{
  GLFWwindow *window;
  MouseEvent *mouseEvent, *mouseEventBuffer;

public:
  MouseHandler(GLFWwindow *_window);  
  ~MouseHandler();  
  MouseEvent* const getMouseEvent();
  void onEvent(int button, int action, int mods);
  void update();  
};

#endif
