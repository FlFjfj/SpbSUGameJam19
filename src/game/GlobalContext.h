#pragma once

#include <vector>
#include <memory>

#include <GLFW/glfw3.h>

#include "Scene.h"

struct GlobalContext {
  static void reset();

  static GLFWwindow* window;
  static Scene* currentScene;
  static std::unique_ptr<Scene> testScene;

  static std::unique_ptr<Scene> startMenu;
  static std::unique_ptr<Scene> episodesScreen;
  static std::vector<std::unique_ptr<Scene>> eposides;
  static int nEpisodes;
  static int nBro;
  static int cash;
  static int health;
  static std::vector<bool> episodeAvialable;
  static std::vector<bool> broAvialable;

  static const int SCREEN_WIDTH;
  static const int SCREEN_HEIGHT;
  static const int TICKS_PER_SECOND;
  static const float TICK_DELTA;
};