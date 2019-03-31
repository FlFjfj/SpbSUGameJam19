#include "Episode2.h"

#include <utils/math.h>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>

#include "Ep2Gameplay.h"

Episode2::Episode2() : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT), font(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя?().,", ResourseManager::fontTexture.get()) {
  init();
}

void Episode2::init() {
  simple_proj_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");
}

void Episode2::enter() {
  timeElapsed = 0;
}

void Episode2::update() {
  timeElapsed += GlobalContext::TICK_DELTA / GlobalContext::TICKS_PER_SECOND;

  switch (state) {
  case WAIT:
  {
    auto state = glfwGetKey(GlobalContext::window, GLFW_KEY_DOWN);
    if (state == GLFW_PRESS && choosenVariant != 2) {
      progress = 0;
      moveDown = true;
      choosenVariant++;
      this->state = MOVE;
      break;
    }

    state = glfwGetKey(GlobalContext::window, GLFW_KEY_UP);
    if (state == GLFW_PRESS && choosenVariant != 0) {
      progress = 0;
      moveDown = false;
      choosenVariant--;
      this->state = MOVE;
      break;
    }

    state = glfwGetKey(GlobalContext::window, GLFW_KEY_ENTER);
    if (state == GLFW_PRESS) {
      GlobalContext::changeScene(new Episode2Gameplay(choosenVariant));
      break;
    }

    break;
  }

  case MOVE:
  {
    progress += 1 / 5.0f;
    if (progress >= 1.0f) {
      state = WAIT;
      progress = 0;
    }

    break;
  }
  }
}

void Episode2::draw(float complete) {
  camera.update();

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::ep2dialogBack.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);

  batch.draw(*ResourseManager::gopnikTexture.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);
  batch.draw(*ResourseManager::kachokTexture.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);

  batch.draw(*ResourseManager::dialogeInterface.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);

  if (state == MOVE) {
    float diff = fjfj::lerp(0, moveDown ? 1 : -1 , 1.0 - (progress + complete / 5.0f));
    batch.draw(*ResourseManager::dialogeChoose.get(), simple_model_location,
      glm::vec2{ 0, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * (3 - choosenVariant + diff) }, GlobalContext::SCREEN_WIDTH, 35);
  } else {
    batch.draw(*ResourseManager::dialogeChoose.get(), simple_model_location,
      glm::vec2{ 0, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * (3 - choosenVariant) }, GlobalContext::SCREEN_WIDTH, 35);
  }

  font.draw(&batch, &camera, L"просить помочь друга слева",      -GlobalContext::SCREEN_WIDTH / 2 + 30, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * 3, 20, 30);
  font.draw(&batch, &camera, L"просить помочь друга справа",     -GlobalContext::SCREEN_WIDTH / 2 + 30, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * 2, 20, 30);
  font.draw(&batch, &camera, L"шо тот... шо этот... пойду один", -GlobalContext::SCREEN_WIDTH / 2 + 30, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * 1, 20, 30);
}

std::unique_ptr<Scene> createEpisode2() {
  return std::make_unique<Episode2>();
}