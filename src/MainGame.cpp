#include "MainGame.h"

#include <utils/resourseManager.h>

#include <iostream>

MainGame::MainGame() : ecs() {}

void MainGame::init(GLFWwindow* window) {
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  ResourseManager::initResourses();
  auto error = glGetError();
  std::cout << "resource init error: " << error << std::endl;

  ecs.init(window);
}

void MainGame::update(float delta) {
  ecs.update(delta);
}

void MainGame::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ecs.draw();
}
