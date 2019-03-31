#include "Ep2Gameplay.h"

#include <random>
#include <ctime>

#include <utils/math.h>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>

Episode2Gameplay::Episode2Gameplay(int choosen) : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT), font(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя?().,", ResourseManager::fontTexture.get()) {
  init();

  switch (choosen) {
  case 0:
  {
    if (GlobalContext::cash > 100) {
      friendId = 0;
      break;
    }

    if (GlobalContext::broAvialable[0]) {
      if (unsigned(std::time(0)) % 2) {
        friendId = 0;
        break;
      }
    }

    friendId = -1;
    break;
  }

  case 1:
  {
    friendId = GlobalContext::broAvialable[1] ? 1 : -1;
    break;
  }

  case 2:
  {
    friendId = -1;
    break;
  }
  }
}

void Episode2Gameplay::init() {
  simple_proj_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");

  indexToTexture = {
    { 0, ResourseManager::bad1.get() },
  { 1, ResourseManager::bad2.get() },
  { 2, ResourseManager::bad3.get() },
  { 3, ResourseManager::good1.get() },
  { 4, ResourseManager::good2.get() },
  { 5, ResourseManager::good3.get() },
  };
}

void Episode2Gameplay::enter() {
  std::random_shuffle(graffity.begin(), graffity.end());
  timeElapsed = 0;
}

void  Episode2Gameplay::update() {
  timeElapsed += GlobalContext::TICK_DELTA / GlobalContext::TICKS_PER_SECOND;

  moveDir = 0;
  auto state = glfwGetKey(GlobalContext::window, GLFW_KEY_LEFT);
  if (state == GLFW_PRESS) {
    moveProgress -= GlobalContext::TICK_DELTA / 4;
    moveDir -= 1;
  }

  state = glfwGetKey(GlobalContext::window, GLFW_KEY_RIGHT);
  if (state == GLFW_PRESS) {
    moveProgress += GlobalContext::TICK_DELTA / 4;
    moveDir += 1;
  }

  if (moveProgress < 0)
    moveProgress = 0;
  if (moveProgress > 1)
    moveProgress = 1;
}

void Episode2Gameplay::draw(float complete) {
  camera.position.x = fjfj::lerp(-GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_WIDTH, fjfj::clamp(moveProgress + moveDir * complete * GlobalContext::TICK_DELTA / 4, 0, 1));
  camera.update();

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::ep2gameplayBack.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH * 3, (float)GlobalContext::SCREEN_HEIGHT);

  for (int i = 0; i < graffity.size(); i++) {
    batch.draw(*indexToTexture[graffity[i]], simple_model_location,
      glm::vec2{ 350 + i * ((GlobalContext::SCREEN_WIDTH * 3 - 30) / graffity.size()) - GlobalContext::SCREEN_WIDTH * 3.0 / 2.0, 150 }, 
      (float)GlobalContext::SCREEN_WIDTH / 2, (float)GlobalContext::SCREEN_HEIGHT / 3);
  }

}
