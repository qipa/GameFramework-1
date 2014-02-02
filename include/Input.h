#ifndef INPUT_H_2013_11_19
#define INPUT_H_2013_11_19

#include <map>
#include <vector>

using namespace std;

class KeyEvent
{
public:  
  static const int KEY_UP   = 0;
  static const int kEY_DOWN = 1;
  static const int kEY_REPEAT = 2;
  int action;    //押したか離したか
  int keyCode;   //押したキー
  int modifier;  //Shift, Ctrl, Alt, Superキー用  
};

class MouseEvent
{
public:
  static const int MOUSE_UP     = 0;
  static const int MOUSE_DOWN   = 1;  
  static const int MOUSE_DRAGGED= 2;
  static const int MOUSE_LEFT  = 0;
  static const int MOUSE_RIGHT = 1;
    
  int action;  //押した, 離した, ドラッグ
  int button;  //右クリックか左クリックか
  int modifier;  //シフトキーとかそこらへんを押しているか
  double x, y;  //マウスの位置
};

class ScrollEvent
{
public:
  double offsetX;
  double offsetY;  
};

class LeapMotionHandler;

class Input
{
public:
  virtual bool isAnyKeyPressed() = 0;
  virtual bool isKeyPressed(int keyCode) = 0;
  virtual int getKeyState(int keyCode) = 0;
  virtual MouseEvent* const getMouseEvent() = 0;
  virtual const vector<KeyEvent*>& getKeyEvents() = 0;
  virtual ScrollEvent* const getScrollEvent() = 0;
  virtual LeapMotionHandler* getLeapMotionHandler() const = 0;  
  Input(){}
  virtual ~Input(){}
};

#endif
