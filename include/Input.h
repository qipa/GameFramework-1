#ifndef INPUT_H_2013_11_19
#define INPUT_H_2013_11_19

#include <map>
#include <vector>

using namespace std;

class KeyEvent
{
public:
  static const int KEY_DOWN = 0;
  static const int kEY_UP = 1;

  int action;
  int keyCode;
  char keyChar;
};

class MouseEvent
{
public:
  static const int MOUSE_DOWN   = 0;  
  static const int MOUSE_UP     = 1;
  static const int MOUSE_DRAGGED= 2;

  static const int MOUSE_LEFT  = 0;
  static const int MOUSE_RIGHT = 1;
    
  int action;
  int button;
  double x, y;
};

class Input
{
public:
  virtual bool isKeyPressed(int keyCode) = 0;
  virtual int getKeyState(int keyCode) = 0;
  virtual MouseEvent* const getMouseEvent() = 0;
  virtual const vector<KeyEvent*>& getKeyEvents() = 0;

  Input(){}
  virtual ~Input(){}
};

#endif
