#include "StartMenu.h"
#include <GL/glew.h>

void StartMenu::init() {
}
void StartMenu::enter() {}
void StartMenu::update() {}
void StartMenu::draw(float delta) {
}

std::unique_ptr<Scene> createStartMenu() {
  return std::make_unique<StartMenu>();
}
