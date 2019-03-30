#include "StartMenu.h"

#include <game/GlobalContext.h>
#include <utils/resourseManager.h>

StartMenu::StartMenu() : camera(GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT) {
  init();
}

void StartMenu::init() {
  simple_proj_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");

  animated_proj_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ProjTrans");
  animated_model_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ModelTrans");
}

void StartMenu::enter() {

}

void StartMenu::update() {
  camera.update();
}

void StartMenu::draw(float delta) {
  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::menuTexture.get(), simple_model_location,
    glm::vec2{ 0, 0 }, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);
}

std::unique_ptr<Scene> createStartMenu() {
  return std::make_unique<StartMenu>();
}
