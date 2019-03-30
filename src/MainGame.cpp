#include "MainGame.h"

#include <utils/resourseManager.h>
#include <game/GlobalContext.h>
#include <iostream>

#include <game/scenes/menu/StartMenu.h>

MainGame::MainGame() {}

void MainGame::init(GLFWwindow* window) {
  glfwWindowHint(GLFW_SAMPLES, 4);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  ResourseManager::initResourses();
  auto error = glGetError();
  std::cout << "resource init error: " << error << std::endl;

  GlobalContext::startMenu = createStartMenu();
  GlobalContext::reset();



  changeScene(GlobalContext::startMenu.get());
}

void MainGame::update(float delta) {
  timeSinceTick += delta;

  while (timeSinceTick > GlobalContext::TICK_DELTA) {
    timeSinceTick -= GlobalContext::TICK_DELTA;
    currentScene->update();
  }

  float completion = timeSinceTick / GlobalContext::TICK_DELTA;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  currentScene->draw(completion);
}


void MainGame::changeScene(Scene* newScene) {
  currentScene = newScene;
  currentScene->enter();
}
