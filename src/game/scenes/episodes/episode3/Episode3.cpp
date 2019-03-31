#include "Episode3.h"

#include <utils/math.h>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>


#include "FinalChoice.h"

Episode3::Episode3() : camera((float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT), font(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя?().,", ResourseManager::fontTexture.get()) {
  init();
}

void Episode3::init() {
  simple_proj_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ProjTrans");
  simple_model_location = glGetUniformLocation(ResourseManager::simpleShader->Program, "u_ModelTrans");
}

void Episode3::enter() {
  timeElapsed = 0;
  
  if (GlobalContext::bar)
    available_indexes.push_back(2);
  if (GlobalContext::police)
    available_indexes.push_back(1);
  if (GlobalContext::badCites || GlobalContext::goodCites)
    available_indexes.push_back(0);
  if (available_indexes.empty()) {
    GlobalContext::changeScene(new FinalChoice());
  }

  choosenVariant = 0;
  selectorPos = available_indexes[choosenVariant];
  oldSelectorPos = selectorPos;

  drawBar = false;
  drawCite = false;
  drawBuy = false;
  drawOutofCash = false;
}

void Episode3::update() {
  timeElapsed += GlobalContext::TICK_DELTA / GlobalContext::TICKS_PER_SECOND;

  switch (state) {
  case WAIT:
  {
    auto state = glfwGetKey(GlobalContext::window, GLFW_KEY_DOWN);
    if (state == GLFW_PRESS && choosenVariant + 1 < available_indexes.size()) {
      progress = 0;
      choosenVariant++;
      oldSelectorPos = selectorPos;
      selectorPos = available_indexes[choosenVariant];
      this->state = MOVE;
      break;
    }

    state = glfwGetKey(GlobalContext::window, GLFW_KEY_UP);
    if (state == GLFW_PRESS && choosenVariant > 0) {
      progress = 0;
      choosenVariant--;
      oldSelectorPos = selectorPos;
      selectorPos = available_indexes[choosenVariant];
      this->state = MOVE;
      break;
    }

    state = glfwGetKey(GlobalContext::window, GLFW_KEY_ENTER);
    if (state == GLFW_PRESS) {
      switch (selectorPos) {
      case 2:
      {
        if (GlobalContext::hasCash) {
          drawBar = true;
        } else {
          drawOutofCash = true;
        }

        progress = 0;
        this->state = FINALIZE;
        break;
      }
      case 1:
      {
        if (GlobalContext::hasCash) {
          drawBuy = true;
        } else {
          drawOutofCash = true;
        }

        progress = 0;
        this->state = FINALIZE;
        break;
      }
      case 0:
      {
        if (GlobalContext::hasCash) {
          drawCite = true;
        } else {
          drawOutofCash = true;
        }

        progress = 0;
        this->state = FINALIZE;
        break;
      }
      }
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

  case FINALIZE:
  {
    progress += 1 / 80.0f;
    if (progress >= 1.0f) {
      state = WAIT;
      progress = 0;
      GlobalContext::changeScene(new FinalChoice());
    }

    break;
  }

  }
}

void Episode3::draw(float complete) {
  camera.update();

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::ep2dialogBack.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);

  if ((drawCite && GlobalContext::badCites) || drawBuy) {
    batch.draw(*ResourseManager::gopnikTexture.get(), simple_model_location,
      glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);
  }


  if ((drawCite && GlobalContext::goodCites) || drawBar) {
    batch.draw(*ResourseManager::kachokTexture.get(), simple_model_location,
      glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);
  }

  if (drawBar || drawBuy || drawCite || drawOutofCash) {
    batch.draw(
      *ResourseManager::bubbleTexture.get(), simple_model_location, { 0, 0 }, 300, 300
    );

    if (drawOutofCash) {
      font.draw(&batch, &camera, L"денег на это", -120, 50, 15, 30);
      font.draw(&batch, &camera, L"совсем не осталось", -130, 0, 15, 30);
    }

    if (drawBar) {
      font.draw(&batch, &camera, L"дружба как турник:", -120, 50, 15, 30);
      font.draw(&batch, &camera, L"спилишь не запилишь", -130, 0, 15, 30);
    }

    if (drawBuy) {
      font.draw(&batch, &camera, L"ты освободил меня,", -120, 70, 15, 30);
      font.draw(&batch, &camera, L"но наша дружба", -120, 45, 15, 30);
      font.draw(&batch, &camera, L"умерла в камере", -120, 15, 15, 30);
    }
    
    if (drawCite) {
      font.draw(&batch, &camera, L"дружбу заново", -120, 35, 15, 30);
      font.draw(&batch, &camera, L"не напишешь", -120, 0, 15, 30);
    }
  }

  ResourseManager::simpleShader->Use();
  glUniformMatrix4fv(simple_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
  batch.draw(*ResourseManager::dialogeInterface.get(), simple_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);

  if (state == MOVE) {
    float y = fjfj::lerp(getSelectorYCoord(selectorPos), getSelectorYCoord(oldSelectorPos), 1.0 - (progress + complete / 5.0f));
    batch.draw(*ResourseManager::dialogeChoose.get(), simple_model_location,
      glm::vec2{ 0, y }, GlobalContext::SCREEN_WIDTH, 35);
  } else {
    batch.draw(*ResourseManager::dialogeChoose.get(), simple_model_location,
      glm::vec2{ 0, getSelectorYCoord(selectorPos)}, GlobalContext::SCREEN_WIDTH, 35);
  }

  font.draw(&batch, &camera, L"стоит попытаться вернуть друзей",      -GlobalContext::SCREEN_WIDTH / 2 + 30, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * 3, 20, 30);
  if(GlobalContext::bar)
    font.draw(&batch, &camera, L"поставить новый турник во дворе",      -GlobalContext::SCREEN_WIDTH / 2 + 30, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * 2, 20, 30);
  if(GlobalContext::police)
    font.draw(&batch, &camera, L"заплатить за друга залог",     -GlobalContext::SCREEN_WIDTH / 2 + 30, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * 1, 20, 30);
  if(GlobalContext::badCites || GlobalContext::goodCites)
    font.draw(&batch, &camera, L"расписать стены их любимыми цитатами", -GlobalContext::SCREEN_WIDTH / 2 + 30, -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * 0, 20, 30);
}

float Episode3::getSelectorYCoord(float pos) {
  return -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * pos;
}


std::unique_ptr<Scene> createEpisode3() {
  return std::make_unique<Episode3>();
}