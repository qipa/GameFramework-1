#ifndef SCROLL_HANDLER_H_2013_12_19
#define SCROLL_HANDLER_H_2013_12_19

#include "../Input.h"
#include "../Pool.h"
#include "../Lock.h"
#include "GLFW/glfw3.h"
#include <pthread.h>

class ScrollHandler
{
  ScrollEvent *scrollEvent, *scrollEventBuffer;
  pthread_mutex_t lock;
public:
  ScrollHandler();  
  ~ScrollHandler();  
  ScrollEvent* const getScrollEvent();
  void onEvent(double offsetX, double offsetY);
  void update();  
};

#endif
