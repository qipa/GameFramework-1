#include "Assets.h"
#include <syukatsu/SyukatsuTexture.h>
#include <syukatsu/SyukatsuFont.h>

Texture   *Assets::textureAtlas = NULL;
TextureRegion *Assets::virus = NULL;
Font* Assets::mincho = NULL;

void Assets::load()
{
  textureAtlas = new SyukatsuTexture("textureAtlas.png");
  int size = 64;  
  virus = new TextureRegion(textureAtlas, 7*size, 10*size, 2*size, 2*size);
  mincho = new SyukatsuFont("UtsukushiMincho.ttf");
}

void Assets::dispose()
{
  delete textureAtlas;
  delete virus;
  delete mincho;  
}

