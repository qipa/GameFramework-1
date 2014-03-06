#include <mutex>
#include <ScrollHandler.h>

namespace
{
  std::mutex mtx_lock;
}

ScrollHandler::ScrollHandler()
{
  scrollEvent = new ScrollEvent();
  scrollEventBuffer = new ScrollEvent();
}

ScrollHandler::~ScrollHandler()
{
  std::lock_guard<std::mutex> lock(mtx_lock);

  delete scrollEvent;
  delete scrollEventBuffer;  
}
  
ScrollEvent* const ScrollHandler::getScrollEvent()
{
  std::lock_guard<std::mutex> lock(mtx_lock);  
    
  return scrollEvent;
}

void ScrollHandler::onEvent(double offsetX, double offsetY)
{
  std::lock_guard<std::mutex> lock(mtx_lock);
  
  scrollEventBuffer->offsetX = offsetX;
  scrollEventBuffer->offsetY = offsetY;
}

void ScrollHandler::update()
{
  std::lock_guard<std::mutex> lock(mtx_lock);
  
  scrollEvent->offsetX = scrollEventBuffer->offsetX;
  scrollEvent->offsetY = scrollEventBuffer->offsetY;
  
  scrollEventBuffer->offsetX = scrollEventBuffer->offsetY = 0;  
}

