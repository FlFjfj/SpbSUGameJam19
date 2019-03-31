#include "GlobalContext.h"

GLFWwindow* GlobalContext::window = nullptr;
Scene* GlobalContext::currentScene = nullptr;

std::unique_ptr<Scene> GlobalContext::startMenu = {};
std::unique_ptr<Scene> GlobalContext::testScene = {};
std::unique_ptr<Scene> GlobalContext::episodesScreen = {};
std::vector<std::unique_ptr<Scene>> GlobalContext::eposides = {};

const int GlobalContext::SCREEN_WIDTH = 1280;
const int GlobalContext::SCREEN_HEIGHT = 720;
const int GlobalContext::TICKS_PER_SECOND = 20;
const float GlobalContext::TICK_DELTA = 1.0f / GlobalContext::TICKS_PER_SECOND;

bool GlobalContext::hasCash;
bool GlobalContext::police;
bool GlobalContext::bar;
bool GlobalContext::goodCites;
bool GlobalContext::badCites;
std::vector<bool> GlobalContext::broAvialable = {};

void GlobalContext::reset() {
  hasCash = false;
  police = false;
  bar = false;
  goodCites = false;
  badCites = false;

  GlobalContext::broAvialable.resize(2);
  std::fill(GlobalContext::broAvialable.begin(), broAvialable.end(), true);
}

void GlobalContext::changeScene(Scene* newScene) {
  currentScene = newScene;
  currentScene->enter();
}