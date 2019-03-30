#pragma once

#include <memory>

#include <GLFW/glfw3.h>

#include <game/Scene.h>

class TestScene : public Scene {
  void init() override;
  void enter() override;
  void update() override;
  void draw(float complete) override;

private:
  void onMouseButton(int button, int action, int mods) override;
  void onKey(int key, int scancode, int action, int mods) override;

  float color;
  void* prevContext;
};

std::unique_ptr<Scene> createTestScene();