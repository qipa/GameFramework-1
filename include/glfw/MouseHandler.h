#ifndef MOUSE_HANDLER_H_2013_12_19
#define MOUSE_HANDLER_H_2013_12_19

#include "../Input.h"
#include "../Pool.h"

#include <pthread.h>

class MouseHandler
{
  MouseEvent *mouseEvent;
  pthread_mutex_t lock;
public:
  MouseHandler()
  {
    pthread_mutex_init(&lock, NULL);
    mouseEvent = new MouseEvent();
  }
  
  MouseEvent* const getMouseEvent() const
  {
    return mouseEvent;
  }

  void onEvent(int button, int action, int mods)
  {
    mouseEvent->button = button;
    mouseEvent->action = action; 
  }
};
#endif
