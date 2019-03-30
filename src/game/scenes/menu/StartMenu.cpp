#include "StartMenu.h"

#include <utils/math.h>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>

StartMenu::StartMenu() : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT) {
  init();
}

void StartMenu::init() {
  simple_proj_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");

  animated_proj_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ProjTrans");
  animated_model_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ModelTrans");
  animated_time_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_Time");
  animated_frameTime_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_FrameTime");
  animated_frameCount_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_FrameCount");
}

void StartMenu::enter() {

}

void StartMenu::update() {
  elapsedTime += GlobalContext::TICK_DELTA;

  switch (state) {
  case WAIT:
  {
    auto state = glfwGetKey(GlobalContext::window, GLFW_KEY_SPACE);
    if (state == GLFW_PRESS) {
      progress = 0;
      this->state = ANIMATE;
    }

    break;
  }

  case ANIMATE:
  {
    progress += 1 / 20.0f;
    if (progress >= 1.0f) {
      state = FINAL;
      progress = 0;
      progress = 0;
      camera.width = (float)GlobalContext::SCREEN_WIDTH;
      camera.height = (float)GlobalContext::SCREEN_HEIGHT;
      camera.position = { 0, 0 };
    }

    break;
  }

  case FINAL:
  {
    progress += 1 / 10.0f;
    if (progress >= 1.0f) {
      GlobalContext::changeScene(GlobalContext::episodesScreen.get());
    }

    break;
  }
  }
}

void StartMenu::draw(float delta) {
  if (state == ANIMATE) {
    camera.width = fjfj::lerp((float)GlobalContext::SCREEN_WIDTH, 690, progress + delta / 20.0f);
    camera.height = fjfj::lerp((float)GlobalContext::SCREEN_HEIGHT, 375, progress + delta / 20.0f);
    camera.position = glm::vec2{ 10, 23 } *(progress + delta / 20.0f);
  }

  camera.update();

  if (state != FINAL) {
    ResourseManager::simpleShader->Use();
    glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    batch.draw(*ResourseManager::menuTexture.get(), simple_model_location,
      glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);
  }

  ResourseManager::animatedShader->Use();
  glUniformMatrix4fv(animated_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  glUniform1f(animated_time_location, elapsedTime + delta * GlobalContext::TICK_DELTA);
  glUniform1f(animated_frameTime_location, noiseSpeed);
  glUniform1i(animated_frameCount_location, noiseFrames);

  switch (state) {
  case StartMenu::WAIT:
  case StartMenu::ANIMATE:
    batch.draw(*ResourseManager::noiseTexture.get(), animated_model_location,
      glm::vec2{ 10, 23 }, 690, 375);
    break;
  case StartMenu::FINAL:
    batch.draw(*ResourseManager::noiseTexture.get(), animated_model_location,
      glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);
    break;
  default:
    break;
  }

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));

  switch (state) {
  case StartMenu::WAIT:
    batch.draw(*ResourseManager::startButtonTexture.get(), simple_model_location,
      glm::vec2{ 10, 23 }, 680, 200);
    break;
  case StartMenu::ANIMATE:
    batch.draw(*ResourseManager::startButtonTexture.get(), simple_model_location,
      glm::vec2{ 10, 23 }, fjfj::lerp(680, 0, progress + delta / 20.0f), fjfj::lerp(200, 0, progress + delta / 20.0f));
    break;
  default:
    break;
  }


}

std::unique_ptr<Scene> createStartMenu() {
  return std::make_unique<StartMenu>();
}
