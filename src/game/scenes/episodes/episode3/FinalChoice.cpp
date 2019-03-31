#include "FinalChoice.h"

#include <utils/math.h>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>


FinalChoice::FinalChoice() : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT), font(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя?().,", ResourseManager::fontTexture.get()) {
  init();
}

void FinalChoice::init() {
  simple_proj_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");
}

void FinalChoice::enter() {
  timeElapsed = 0;
  textPart = 0;
}

void FinalChoice::update() {
  timeElapsed += GlobalContext::TICK_DELTA;

  progress += GlobalContext::TICK_DELTA / 2;
  if (progress > 1) {
    progress = 0;
    textPart++;

    if (textPart == 3) {
      GlobalContext::changeScene(GlobalContext::startMenu.get());
    }
  }
}

void FinalChoice::draw(float complete) {
  camera.update();

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::gopnikBackgroundTexture.get(), simple_model_location,
    glm::vec2{ 0, 0 }, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);

  batch.draw(*ResourseManager::doctor.get(), simple_model_location,
    glm::vec2{ -450, -140 }, 300, 500);

  batch.draw(*ResourseManager::bubbleTexture.get(), simple_model_location, { 0, 0 }, 300, 300);

  switch (textPart) {
  case 0:
  {
    if (GlobalContext::hasCash) {
      font.draw(&batch, &camera, L"были потрачены все", -120, 50, 15, 30);
      font.draw(&batch, &camera, L"накопления,но этого мало", -130, 0, 15, 30);
    } else {
      font.draw(&batch, &camera, L"собственных средств", -120, 50, 15, 30);
      font.draw(&batch, &camera, L"практически нет", -130, 0, 15, 30);
    }

    break;
  }
  case 1:
    if (GlobalContext::hasCash && (GlobalContext::broAvialable[0] || GlobalContext::broAvialable[1])) {
      font.draw(&batch, &camera, L"но ваш друг смог", -120, 50, 15, 30);
      font.draw(&batch, &camera, L"выручить,отдав остальное", -130, 0, 15, 30);
      break;
    }

    if (GlobalContext::broAvialable[0] || GlobalContext::broAvialable[1]) {
      font.draw(&batch, &camera, L"друг помог, но всё", -120, 50, 15, 30);
      font.draw(&batch, &camera, L"равно не хватило", -130, 0, 15, 30);
      break;
    }

    font.draw(&batch, &camera, L"никто не помог", -120, 50, 15, 30);
    font.draw(&batch, &camera, L"в минуту нужды", -130, 0, 15, 30);
    break;

  case 2:
    if (GlobalContext::hasCash && (GlobalContext::broAvialable[0] || GlobalContext::broAvialable[1])) {
      font.draw(&batch, &camera, L"совместные усилия", -120, 50, 15, 30);
      font.draw(&batch, &camera, L"спасли вам жизнь", -130, 0, 15, 30);
      break;
    } else {
      font.draw(&batch, &camera, L"наступила смерть", -120, 50, 15, 30);
      font.draw(&batch, &camera, L"это неизбежно...", -130, 0, 15, 30);
    }
  }
}
