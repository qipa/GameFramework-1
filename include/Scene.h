#ifndef SCENE_H_2013_11_19
#define SCENE_H_2013_11_19

class Game;

class Scene
{
protected:
  const Game *game;
public:
Scene(Game *_game):game(_game){}
  virtual ~Scene(){}
  
  virtual void render(float deltaTime) = 0;
  virtual void update(float deltaTime) = 0;
  virtual void reshape(int width, int height) = 0;
  virtual void dispose()=0;
};

#endif
