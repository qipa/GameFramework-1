#ifndef ASSETS_H_2013_12_22
#define ASSETS_H_2013_12_22

#include <GLFWTexture.h>

class Assets
{
public:
  static GLFWTexture *textureAtlas;
  static TextureRegion *virus;
  static void load();
  static void dispose();
private:
  Assets();
  Assets& operator=(const Assets& obj);
};

#endif
