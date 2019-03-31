#include "Episode2.h"

#include <utils/math.h>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>

Episode2::Episode2() : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT) {
  init();
}

void Episode2::init() {
  simple_proj_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");
}

void Episode2::enter() {
  timeElapsed = 0;
}

void  Episode2::update() {
  timeElapsed += GlobalContext::TICK_DELTA / GlobalContext::TICKS_PER_SECOND;


}

void Episode2::draw(float complete) {
  camera.update();

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::ep2dialogBack.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);

  batch.draw(*ResourseManager::ep2ChooseFriend.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);
}

std::unique_ptr<Scene> createEpisode2() {
  return std::make_unique<Episode2>();
}