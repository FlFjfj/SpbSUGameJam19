#include "GlobalContext.h"

std::unique_ptr<Scene> GlobalContext::startMenu = {};
std::unique_ptr<Scene> GlobalContext::episodesScreen = {};
std::vector<std::unique_ptr<Scene>> GlobalContext::eposides = {};

const int GlobalContext::SCREEN_WIDTH = 1280;
const int GlobalContext::SCREEN_HEIGHT = 720;
const int GlobalContext::TICKS_PER_SECOND = 20;
const float GlobalContext::TICK_DELTA = 1.0f / GlobalContext::TICKS_PER_SECOND;

void GlobalContext::reset() {

}