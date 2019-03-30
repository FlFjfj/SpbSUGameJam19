#include "Episodes.h"

#include <game/GlobalContext.h>
#include <utils/resourseManager.h>
#include <utils/math.h>

EpisodesScene::EpisodesScene() : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT) {
  init();
}

void EpisodesScene::init() {
  simple_proj_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");

  animated_proj_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ProjTrans");
  animated_model_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ModelTrans");
  animated_time_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_Time");
  animated_frameTime_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_FrameTime");
  animated_frameCount_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_FrameCount");
}

void EpisodesScene::enter() {
  state = EXIT;
  progress = 0;
}

void EpisodesScene::update() {
  elapsedTime += GlobalContext::TICK_DELTA;

  switch (state) {
  case EXIT:
  {
    progress += 1 / 20.0f;
    if (progress >= 1.0f) {
      progress = 0;
      currentScreen++;
      this->state = MOVE;
    }

    break;
  }

  case MOVE:
  {
    progress += 1 / 40.0f;
    if (progress >= 1.0f) {
      progress = 0;
      state = ENTER;
    }

    break;
  }

  case ENTER:
  {
    progress += 1 / 20.0f;
    if (progress >= 1.0f) {
      GlobalContext::changeScene(GlobalContext::eposides[currentScreen - 1].get());
    }

    break;
  }
  }
}

void EpisodesScene::draw(float delta) {
  float x, y, width, height;

  if (state == MOVE) {
    float progress = this->progress + delta / 40.0f;
    x = fjfj::lerp(screenData[currentScreen - 1][0], screenData[currentScreen][0], progress);
    y = fjfj::lerp(screenData[currentScreen - 1][1], screenData[currentScreen][1], progress);
    width = fjfj::lerp(screenData[currentScreen - 1][2], screenData[currentScreen][2], progress);
    height = fjfj::lerp(screenData[currentScreen - 1][3], screenData[currentScreen][3], progress);
  } else {
    x = screenData[currentScreen][0];
    y = screenData[currentScreen][1];
    width = screenData[currentScreen][2];
    height = screenData[currentScreen][3];
  }

  if (state == EXIT) {
    float progress = this->progress + delta / 20.0f;
    camera.width = fjfj::lerp((float)GlobalContext::SCREEN_WIDTH / 2, (float)GlobalContext::SCREEN_WIDTH, progress);
    camera.height = fjfj::lerp((float)GlobalContext::SCREEN_HEIGHT / 2, (float)GlobalContext::SCREEN_HEIGHT, progress);
  }

  if (state == ENTER) {
    float progress = this->progress + delta / 20.0f;
    camera.width = fjfj::lerp((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_WIDTH / 2, progress);
    camera.height = fjfj::lerp((float)GlobalContext::SCREEN_HEIGHT, (float)GlobalContext::SCREEN_HEIGHT / 2, progress);
  }

  camera.update();

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  float scalex = GlobalContext::SCREEN_WIDTH / width;
  float scaley = GlobalContext::SCREEN_HEIGHT / height;
  batch.draw(*ResourseManager::episodesTexture.get(), simple_model_location,
    glm::vec2{x * scalex, y * scaley}, scalex * screenSize, scaley * screenSize);

  ResourseManager::animatedShader->Use();
  glUniformMatrix4fv(animated_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  glUniform1f(animated_time_location, elapsedTime + delta * GlobalContext::TICK_DELTA);
  glUniform1f(animated_frameTime_location, noiseSpeed);
  glUniform1i(animated_frameCount_location, noiseFrames);
  for (int i = 0; i < 3; i++) {
    batch.draw(*ResourseManager::noiseTexture.get(), animated_model_location, glm::vec2{(x - screenData[i][0]) * scalex, (y - screenData[i][1]) * scaley}, screenData[i][4] * scalex, screenData[i][5] * scaley);
  }

}

std::unique_ptr<Scene> createEpisodesScene() {
  return std::make_unique<EpisodesScene>();
}
