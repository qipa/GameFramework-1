#ifndef SYUKATSU_FONT_H_2013_12_24
#define SYUKATSU_FONT_H_2013_12_24
#include "../Font.h"
#include "FTGL/ftgl.h"

class SyukatsuFont: public Font
{
  FTFont *font;
  void load(const string fileName);  
public:
  SyukatsuFont(const string fileName);
  ~SyukatsuFont();
  void render(string text) const;  
};

#endif

