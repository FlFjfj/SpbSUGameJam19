#include "Ep2Gameplay.h"

#include <random>
#include <ctime>

#include <utils/math.h>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>

Episode2Gameplay::Episode2Gameplay(int choosen) : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT), font(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя?().,", ResourseManager::fontTexture.get()) {
  init();

  switch (choosen - 1) {
  case 0:
  {
    if (GlobalContext::hasCash) {
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

  animated_proj_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ProjTrans");
  animated_model_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_ModelTrans");
  animated_time_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_Time");
  animated_frameTime_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_FrameTime");
  animated_frameCount_location = glGetUniformLocation(ResourseManager::animatedShader->Program, "u_FrameCount");

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
  elapsedTime = 0;
}

void  Episode2Gameplay::update() {
  moveDir = 0;
  //auto state = glfwGetKey(GlobalContext::window, GLFW_KEY_LEFT);
  //if (state == GLFW_PRESS) {
  //  moveProgress -= GlobalContext::TICK_DELTA / 4;
  //  moveDir -= 1;
  //}

  auto state = glfwGetKey(GlobalContext::window, GLFW_KEY_RIGHT);
  if (state == GLFW_PRESS) {
    moveProgress += GlobalContext::TICK_DELTA / 8;
    moveDir += 1;
  }

  state = glfwGetKey(GlobalContext::window, GLFW_KEY_SPACE);
  if (state == GLFW_PRESS) {
    int index = int(moveProgress * 6);
    isWashed[index % 6] = true;
    (graffity[index % 6] >= 3 ? goodWashed : badWashed)++;
  }

  if (moveProgress < 0)
    moveProgress = 0;
  if (moveProgress > 1) {
    if (goodWashed >= 2) {
      GlobalContext::broAvialable[1] = false;
      GlobalContext::goodCites = true;
    }

    if (badWashed >= 2) {
      GlobalContext::broAvialable[0] = false;
      GlobalContext::badCites = true;
    }

    if (badWashed + goodWashed >= 3)
      GlobalContext::hasCash = true;

    GlobalContext::changeScene(GlobalContext::episodesScreen.get());
  }

  if (moveDir != 0) {
    elapsedTime += GlobalContext::TICK_DELTA;
  }
}

void Episode2Gameplay::draw(float delta) {
  camera.position.x = fjfj::lerp(-GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_WIDTH, fjfj::clamp(moveProgress + moveDir * delta * GlobalContext::TICK_DELTA / 8, 0, 1));
  camera.update();

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::ep2gameplayBack.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH * 3, (float)GlobalContext::SCREEN_HEIGHT);

  for (int i = 0; i < graffity.size(); i++) {
    if (!isWashed[i])
      batch.draw(*indexToTexture[graffity[i]], simple_model_location,
        glm::vec2{ 350 + i * ((GlobalContext::SCREEN_WIDTH * 3 - 30) / graffity.size()) - GlobalContext::SCREEN_WIDTH * 3.0 / 2.0, 150 },
        (float)GlobalContext::SCREEN_WIDTH / 2, (float)GlobalContext::SCREEN_HEIGHT / 3);
  }

  ResourseManager::animatedShader->Use();
  glUniformMatrix4fv(animated_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  glUniform1f(animated_time_location, elapsedTime + (moveDir == 0 ? 0 : delta * GlobalContext::TICK_DELTA));
  glUniform1f(animated_frameTime_location, human_speed);
  glUniform1i(animated_frameCount_location, human_frames);
  batch.draw(*ResourseManager::ep2human.get(), animated_model_location,
    { fjfj::lerp(-GlobalContext::SCREEN_WIDTH * 3 / 2 + 400, GlobalContext::SCREEN_WIDTH * 3 / 2, fjfj::clamp(moveProgress + moveDir * delta * GlobalContext::TICK_DELTA / 8, 0, 1)), -250 },
    200, 360);

  switch (friendId) {
  case 0:
  {
    ResourseManager::simpleShader->Use();
    glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    batch.draw(*ResourseManager::gopnikTexture.get(), simple_model_location,
      glm::vec2{
        fjfj::lerp(-GlobalContext::SCREEN_WIDTH * 3 / 2 + (float)GlobalContext::SCREEN_WIDTH / 4,
        GlobalContext::SCREEN_WIDTH * 3 / 2 + (float)GlobalContext::SCREEN_WIDTH / 4 - 1280,
        fjfj::clamp(moveProgress + moveDir * delta * GlobalContext::TICK_DELTA / 8, 0, 1)),
        -250 },
        (float)GlobalContext::SCREEN_WIDTH / 2, (float)GlobalContext::SCREEN_HEIGHT / 2);

    int index = int(moveProgress * 6);
    if (!isWashed[index % 6]) {
      batch.draw(*ResourseManager::bubbleTexture.get(), simple_model_location,
        glm::vec2{
          fjfj::lerp(-GlobalContext::SCREEN_WIDTH * 3 / 2 + 370,
          GlobalContext::SCREEN_WIDTH * 3 / 2 - 1280 + 370,
          fjfj::clamp(moveProgress + moveDir * delta * GlobalContext::TICK_DELTA / 8, 0, 1)),
          -150 },
          300, 200);

      font.draw(&batch, &camera, graffity[index % 6] >= 3 ? L"так себе" : L"глубоко",
        fjfj::lerp(-GlobalContext::SCREEN_WIDTH * 3 / 2 + 250,
          GlobalContext::SCREEN_WIDTH * 3 / 2 - 1280 + 250,
          fjfj::clamp(moveProgress + moveDir * delta * GlobalContext::TICK_DELTA / 8, 0, 1)),
        -150, 30, 35);

    }
    break;
  }

  case 1:
  {
    ResourseManager::simpleShader->Use();
    glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    batch.draw(*ResourseManager::kachokTexture.get(), simple_model_location,
      glm::vec2{
        fjfj::lerp(-GlobalContext::SCREEN_WIDTH * 3 / 2 + 1280 - (float)GlobalContext::SCREEN_WIDTH / 3,
        GlobalContext::SCREEN_WIDTH * 3 / 2 - (float)GlobalContext::SCREEN_WIDTH / 3,
        fjfj::clamp(moveProgress + moveDir * delta * GlobalContext::TICK_DELTA / 8, 0, 1)),
        -250 },
        (float)GlobalContext::SCREEN_WIDTH / 3, (float)GlobalContext::SCREEN_HEIGHT / 3);

    int index = int(moveProgress * 6);
    if (!isWashed[index % 6]) {
      batch.draw(*ResourseManager::bubbleTexture.get(), simple_model_location,
        glm::vec2{
          fjfj::lerp(-GlobalContext::SCREEN_WIDTH * 3 / 2 + 1280 - 150,
          GlobalContext::SCREEN_WIDTH * 3 / 2 - 150,
          fjfj::clamp(moveProgress + moveDir * delta * GlobalContext::TICK_DELTA / 8, 0, 1)),
          -150 },
          300, 300);

      font.draw(&batch, &camera, graffity[index % 6] >= 3 ? L"пойдёт" : L"стираем",
        fjfj::lerp(-GlobalContext::SCREEN_WIDTH * 3 / 2 + 1280 - 250,
          GlobalContext::SCREEN_WIDTH * 3 / 2 - 250,
          fjfj::clamp(moveProgress + moveDir * delta * GlobalContext::TICK_DELTA / 8, 0, 1)),
        -150, 30, 35);
    }


    break;
  }
  }

}
