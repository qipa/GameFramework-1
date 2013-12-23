#include "Assets.h"
#include <GLFWTexture.h>

GLFWTexture   *Assets::textureAtlas = NULL;
TextureRegion *Assets::virus = NULL;

void Assets::load()
{
  textureAtlas = new GLFWTexture("textureAtlas.png");
  int size = 64;  
  virus = new TextureRegion(textureAtlas, 7*size, 10*size, 2*size, 2*size);  
}

void Assets::dispose()
{
  delete textureAtlas;
  delete virus;  
}

