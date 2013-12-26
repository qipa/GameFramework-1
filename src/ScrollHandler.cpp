#include <ScrollHandler.h>

ScrollHandler::ScrollHandler()
{
  pthread_mutex_init(&lock, NULL);
  scrollEvent = new ScrollEvent();
  scrollEventBuffer = new ScrollEvent();
}

ScrollHandler::~ScrollHandler()
{
  Lock lck(&lock);
  delete scrollEvent;
  delete scrollEventBuffer;  
}
  
ScrollEvent* const ScrollHandler::getScrollEvent()
{
  Lock lck(&lock);
    
  return scrollEvent;
}

void ScrollHandler::onEvent(double offsetX, double offsetY)
{
  Lock lck(&lock);
  scrollEventBuffer->offsetX = offsetX;
  scrollEventBuffer->offsetY = offsetY;
}

void ScrollHandler::update()
{
  Lock lck(&lock);
  scrollEvent->offsetX = scrollEventBuffer->offsetX;
  scrollEvent->offsetY = scrollEventBuffer->offsetY;
  
  scrollEventBuffer->offsetX = scrollEventBuffer->offsetY = 0;  
}

