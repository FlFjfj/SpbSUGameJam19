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
  static void mouseButtonCallbackHelper(GLFWwindow*, int button, int action, int mods);
  void onMouseButton(int button, int action, int mods);

  float color;
  void* prevContext;
};

std::unique_ptr<Scene> createTestScene();