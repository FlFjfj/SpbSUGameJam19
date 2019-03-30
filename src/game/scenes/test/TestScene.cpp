#include "TestScene.h"

#include <GLFW/glfw3.h>

#include <game/GlobalContext.h>

void TestScene::init() {

}

void TestScene::onMouseButton(int button, int action, int mods) {
  switch (button) {
  case GLFW_MOUSE_BUTTON_1:
    color = action == GLFW_PRESS ? 1.0f : 0.0f;
    break;
  case GLFW_MOUSE_BUTTON_2:
    color = action == GLFW_PRESS ? 0.5f : 0.0f;
    break;
  }
}

void TestScene::onKey(int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_0: color = 0.0f; break;
    case GLFW_KEY_1: color = 0.1f; break;
    case GLFW_KEY_2: color = 0.2f; break;
    case GLFW_KEY_3: color = 0.3f; break;
    case GLFW_KEY_4: color = 0.4f; break;
    case GLFW_KEY_5: color = 0.5f; break;
    case GLFW_KEY_6: color = 0.6f; break;
    case GLFW_KEY_7: color = 0.7f; break;
    case GLFW_KEY_8: color = 0.8f; break;
    case GLFW_KEY_9: color = 0.9f; break;
    }
  }
}

void TestScene::enter() {
}

void TestScene::update() {

}

void TestScene::draw(float) {
  glClearColor(color, color, color, 1.0f);
}

std::unique_ptr<Scene> createTestScene() {
  return std::make_unique<TestScene>();
}