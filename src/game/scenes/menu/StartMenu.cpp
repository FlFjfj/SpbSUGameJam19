#include "StartMenu.h"

#include <game/GlobalContext.h>
#include <utils/resourseManager.h>

StartMenu::StartMenu() : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT) {
  init();
}

void StartMenu::init() {
  simple_proj_location         = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location        = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");

  animated_proj_location       = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ProjTrans");
  animated_model_location      = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ModelTrans");
  animated_time_location       = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_Time");
  animated_frameTime_location  = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_FrameTime");
  animated_frameCount_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_FrameCount");
}

void StartMenu::enter() {

}

void StartMenu::update() {
  elapsedTime += GlobalContext::TICK_DELTA;

  camera.update();
}

void StartMenu::draw(float delta) {
  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::menuTexture.get(), simple_model_location,
    glm::vec2{ 0, 0 }, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);

  ResourseManager::animatedShader->Use();
  glUniformMatrix4fv(animated_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  glUniform1f(animated_time_location, elapsedTime + delta * GlobalContext::TICK_DELTA);
  glUniform1f(animated_frameTime_location, noiseSpeed);
  glUniform1i(animated_frameCount_location, noiseFrames);
  batch.draw(*ResourseManager::noiseTexture.get(), animated_model_location,
    glm::vec2{ 10, 23 }, 690, 375);
}

std::unique_ptr<Scene> createStartMenu() {
  return std::make_unique<StartMenu>();
}
