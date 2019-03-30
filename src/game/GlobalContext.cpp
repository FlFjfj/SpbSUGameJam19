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

int GlobalContext::nEpisodes = 6;
int GlobalContext::nBro=3;
int GlobalContext::health=100;
int GlobalContext::cash=100;

std::vector<bool> GlobalContext::episodeAvialable={};
std::vector<bool> GlobalContext::broAvialable={};

void GlobalContext::reset() {
    GlobalContext::nEpisodes = 6;
    GlobalContext::nBro=3;
    GlobalContext::health=100;
    GlobalContext::cash=100;
    GlobalContext::episodeAvialable.resize(GlobalContext::nEpisodes);
    std::fill(GlobalContext::episodeAvialable.begin(), GlobalContext::episodeAvialable.end(),0);
    std::fill(GlobalContext::episodeAvialable.begin(), GlobalContext::episodeAvialable.begin()+2,1);
    GlobalContext::broAvialable.resize(GlobalContext::nBro);
    std::fill(GlobalContext::broAvialable.begin(), broAvialable.end(), 1);
}

void GlobalContext::changeScene(Scene* newScene) {
  currentScene = newScene;
  currentScene->enter();
}