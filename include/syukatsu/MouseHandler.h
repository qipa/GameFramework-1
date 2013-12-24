#ifndef MOUSE_HANDLER_H_2013_12_19
#define MOUSE_HANDLER_H_2013_12_19

#include "../Input.h"
#include "../Pool.h"
#include "../Lock.h"
#include "GLFW/glfw3.h"

#include <pthread.h>

class MouseHandler
{
  GLFWwindow *window;
  MouseEvent *mouseEvent, *mouseEventBuffer;
  pthread_mutex_t lock;
public:
MouseHandler(GLFWwindow *_window)
  :window(_window)
  {
    pthread_mutex_init(&lock, NULL);
    mouseEvent = new MouseEvent();
    mouseEventBuffer = new MouseEvent();
  }

  ~MouseHandler()
  {
    Lock lck(&lock);
    delete mouseEvent;
  }
  
  MouseEvent* const getMouseEvent()
  {
    Lock lck(&lock);

    mouseEvent->button = mouseEventBuffer->button;
    mouseEvent->action = mouseEventBuffer->action;   
    glfwGetCursorPos(window, &mouseEvent->x, &mouseEvent->y);    
    
    return mouseEvent;
  }

  void onEvent(int button, int action, int mods)
  {
    Lock lck(&lock);
    mouseEventBuffer->button = button;
    mouseEventBuffer->action = action;
  }

  void onCursorEvent(double x, double y)
  {
    
  }
};

#endif
