#pragma once
#include <memory>

#include <game/Scene.h>

class StartMenu : public Scene {
public: 
  void init() override;
  void enter() override;
  void update() override;
  void draw(float complete) override;

private:
  float timing;
};

std::unique_ptr<Scene> createStartMenu();
