#pragma once

#include <vector>
#include <memory>

#include <GLFW/glfw3.h>

#include "Scene.h"

struct GlobalContext {
  static void reset();
  static void changeScene(Scene* newScene);

  static GLFWwindow* window;
  static Scene* currentScene;
  static std::unique_ptr<Scene> testScene;

  static std::unique_ptr<Scene> startMenu;
  static std::unique_ptr<Scene> episodesScreen;
  static std::vector<std::unique_ptr<Scene>> eposides;
  static bool hasCash;
  static bool police;
  static bool bar;
  static bool goodCites;
  static bool badCites;
  static std::vector<bool> broAvialable;

  static const int SCREEN_WIDTH;
  static const int SCREEN_HEIGHT;
  static const int TICKS_PER_SECOND;
  static const float TICK_DELTA;
};