#ifndef MOUSE_HANDLER_H_2013_12_19
#define MOUSE_HANDLER_H_2013_12_19

#include "../Input.h"
#include "../Pool.h"
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
    pthread_mutex_lock(&lock);
    delete mouseEvent;
    pthread_mutex_unlock(&lock);
  }
  
  MouseEvent* const getMouseEvent()
  {
    pthread_mutex_lock(&lock);
    mouseEvent->button = mouseEventBuffer->button;
    mouseEvent->action = mouseEventBuffer->action;   
    glfwGetCursorPos(window, &mouseEvent->x, &mouseEvent->y);    
    pthread_mutex_unlock(&lock);
    
    return mouseEvent;
  }

  void onEvent(int button, int action, int mods)
  {
    pthread_mutex_lock(&lock);
    mouseEventBuffer->button = button;
    mouseEventBuffer->action = action;
    pthread_mutex_unlock(&lock);
  }

  void onCursorEvent(double x, double y)
  {
    
  }

};
#endif
