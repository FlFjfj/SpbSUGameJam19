#pragma once

#include <Engine.h>
#include <ecs/ECS.h>

class MainGame : public fjfj::GameBody {
public:
  MainGame();

  void init(GLFWwindow*) override;
  void update(float) override;
  void render() override;

private:
  Ecs ecs;
};
