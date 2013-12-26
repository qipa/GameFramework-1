#include <MouseHandler.h>

MouseHandler::MouseHandler(GLFWwindow *_window)
  :window(_window)
{
  pthread_mutex_init(&lock, NULL);
  mouseEvent = new MouseEvent();
  mouseEventBuffer = new MouseEvent();
}

MouseHandler::~MouseHandler()
{
  Lock lck(&lock);
  delete mouseEvent;
  delete mouseEventBuffer;  
}
  
MouseEvent* const MouseHandler::getMouseEvent()
{
  Lock lck(&lock);
    
  return mouseEvent;
}

void MouseHandler::onEvent(int button, int action, int mods)
{
  Lock lck(&lock);
  mouseEventBuffer->button = button;
  mouseEventBuffer->action = action;
  mouseEventBuffer->modifier = mods; 
}

void MouseHandler::update()
{
  Lock lck(&lock);
  
  mouseEvent->button   = mouseEventBuffer->button;  //中身をコピー
  mouseEvent->action   = mouseEventBuffer->action;  //中身をコピー
  mouseEvent->modifier = mouseEventBuffer->modifier;
  glfwGetCursorPos(window, &mouseEvent->x, &mouseEvent->y);
  
  if(mouseEventBuffer->action == GLFW_PRESS)
    mouseEventBuffer->action = GLFW_REPEAT;  
}
