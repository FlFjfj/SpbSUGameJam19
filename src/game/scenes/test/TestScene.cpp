#include "TestScene.h"

#include <GLFW/glfw3.h>

#include <game/GlobalContext.h>

void TestScene::init() {

}

void TestScene::mouseButtonCallbackHelper(GLFWwindow*, int button, int action, int mods) {
  reinterpret_cast<TestScene*>(GlobalContext::currentContext)->onMouseButton(button, action, mods);
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

void TestScene::enter() {
  prevContext = GlobalContext::currentContext;
  GlobalContext::currentContext = this;

  glfwSetMouseButtonCallback(GlobalContext::window, TestScene::mouseButtonCallbackHelper);
}

void TestScene::update() {

}

void TestScene::draw(float) {
  glClearColor(color, color, color, 1.0f);
}

std::unique_ptr<Scene> createTestScene() {
  return std::make_unique<TestScene>();
}