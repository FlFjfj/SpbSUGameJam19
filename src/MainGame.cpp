#include "MainGame.h"

#include <utils/resourseManager.h>
#include <game/GlobalContext.h>
#include <iostream>

#include <game/scenes/menu/StartMenu.h>
#include <game/scenes/test/TestScene.h>

void MainGame::onMouseCallback(GLFWwindow *, int button, int action, int mods) {
  GlobalContext::currentScene->onMouseButton(button, action, mods);
}

void MainGame::onKeyCallback(GLFWwindow *, int key, int scancode, int action, int mods) {
  GlobalContext::currentScene->onKey(key, scancode, action, mods);
}

MainGame::MainGame() {}

void MainGame::init(GLFWwindow* window) {
  glfwWindowHint(GLFW_SAMPLES, 4);
  glEnable(GL_MULTISAMPLE);
  //glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  ResourseManager::initResourses();
  auto error = glGetError();
  std::cout << "resource init error: " << error << std::endl;

  GlobalContext::window = window;
  GlobalContext::startMenu = createStartMenu();
  GlobalContext::testScene = createTestScene();
  GlobalContext::reset();
#ifdef TEST_SCENE
  GlobalContext::changeScene(GlobalContext::testScene.get());
#else
  GlobalContext::changeScene(GlobalContext::startMenu.get());
#endif

  glfwSetMouseButtonCallback(window, MainGame::onMouseCallback);
  glfwSetKeyCallback(window, MainGame::onKeyCallback);
}

void MainGame::update(float delta) {
  timeSinceTick += delta;

  while (timeSinceTick > GlobalContext::TICK_DELTA) {
    timeSinceTick -= GlobalContext::TICK_DELTA;
    GlobalContext::currentScene->update();
  }

  float completion = timeSinceTick / GlobalContext::TICK_DELTA;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  GlobalContext::currentScene->draw(completion);
}



