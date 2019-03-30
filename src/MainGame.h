#pragma once

#include <Engine.h>
#include <game/Scene.h>
#include <memory>

#include <game/GlobalContext.h>

class MainGame : public fjfj::GameBody {
private:
  Scene* currentScene;
  float timeSinceTick = 0;

public:
  MainGame();

  void init(GLFWwindow*) override;
  void update(float) override;
  void changeScene(Scene* newScene);

};
