#ifndef GLFW_SCENE_H_2013_12_18
#define GLFW_SCENE_H_2013_12_18

class GLFWScene:public Scene
{
protected:
  GLFWGame *glfwGame;
public:
  GLFWScene(GLFWGame *game)
    :Scene(game), glfwGame(game)
  {
  }
};
#endif
