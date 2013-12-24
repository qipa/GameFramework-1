#ifndef ASSETS_H_2013_12_22
#define ASSETS_H_2013_12_22
#include <Texture.h>
#include <Font.h>
class Assets
{
public:
  static Texture *textureAtlas;
  static TextureRegion *virus;
static Font *mincho;
  static void load();
  static void dispose();
private:
  Assets();
  Assets& operator=(const Assets& obj);
};

#endif
