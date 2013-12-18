#ifndef GAME_H_2013_11_19
#define GAME_H_2013_11_19

class Scene;
class Input;
class Audio;
class FileIO;
class Graphics;

class Game
{
public:
  Game(){}
  virtual ~Game(){}

  virtual const Input*  getInput()  const=0;
  virtual const FileIO* getFileIO() const=0;
  virtual const Audio*  getAudio()  const=0;
  virtual const Graphics* getGraphics() const=0;  
  virtual bool setScene(Scene *scene)=0; //1ループの中で何度も切り替えないように, 複数回切り替えたらfalseを返すようにする todo?
  virtual const Scene* getCurrentScene() const = 0;
  virtual Scene* getStartScene() = 0; //コンストラクタから一番始めに一回だけ呼び出される todo protectedにすべき?
  virtual void loop()=0;
};

#endif
