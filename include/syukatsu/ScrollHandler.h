#ifndef SCROLL_HANDLER_H_2013_12_19
#define SCROLL_HANDLER_H_2013_12_19

#include "../Input.h"
#include "../Pool.h"

#include "GLFW/glfw3.h"

class ScrollHandler
{
  ScrollEvent *scrollEvent, *scrollEventBuffer;

public:
  ScrollHandler();  
  ~ScrollHandler();  
  ScrollEvent* const getScrollEvent();
  void onEvent(double offsetX, double offsetY);
  void update();  
};

#endif
