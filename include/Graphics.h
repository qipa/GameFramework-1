#ifndef GRAPHICS_H_2013_12_17
#define GRAPHICS_H_2013_12_17

class Graphics
{
public:
  enum PixmapFormat
  {
    ARGB8888,
    ARGB4444,
    RGB565,
  };

  virtual Pixmap newPixmap(String fileName, PixmapFormat format)=0;
};
#endif
