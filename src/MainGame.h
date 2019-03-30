#pragma once

#include <Engine.h>
#include <game/Scene.h>
#include <memory>

#include <game/GlobalContext.h>

class MainGame : public fjfj::GameBody {
private:
  float timeSinceTick = 0;

  static void onMouseCallback(GLFWwindow*, int button, int action, int mods);
  static void onKeyCallback(GLFWwindow*, int key, int scancode, int action, int mods);

public:
  MainGame();

  void init(GLFWwindow*) override;
  void update(float) override;
  void changeScene(Scene* newScene);

};
