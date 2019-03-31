// Created by hedonistant on 30.03.19.
//

#include "Episode1.h"
#include <memory>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>
#include <iostream>
#include <utils/math.h>
#include <random>

const int Episode1::N_BUTTONS = 3;
const float Episode1::INTRO_STAGE_LENGTH = 2;
const float Episode1::GOPNIK_START_TIME = 0;
const float Episode1::GOPNIK_LENGTH = 2;
const float Episode1::BUBBLE_START_TIME = 0;
const float Episode1::BUBBLE_LENGTH = 2;
const float Episode1::SELECTOR_ANIMATION_LENGTH = 0.2;
const float Episode1::REFUSE_TO_HELP_LENGTH = 1;
const float Episode1::COLLECT_BAR_ANIMATION_LENGTH = 5;
const float Episode1::HAND_TO_COPS_ANIMATION_LENGTH = 4;
const glm::vec2 Episode1::SPEED = { 400, 0 };

enum asd {
  WAIT,
  MOVE
};

Episode1::Episode1() : camera(GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT), font(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя?().,", ResourseManager::fontTexture.get()) {
  init();
}

void Episode1::init() {
  alpha_proj_location = glGetUniformLocation(ResourseManager::alphaShader->Program, "u_ProjTrans");
  alpha_model_location = glGetUniformLocation(ResourseManager::alphaShader->Program, "u_ModelTrans");
  alpha_aplha_location = glGetUniformLocation(ResourseManager::alphaShader->Program, "u_alpha");
}

void Episode1::enter() {
  numPieces = 0;
  timeFromStart = 0;
  barCollected = false;
  selectorPos = 0;
  selectorState = WAIT;
  stage = Stages::Intro;
  center0 = { 0, 0 };
  center1 = { 0, 0 };


  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> disx(-GlobalContext::SCREEN_WIDTH * 1.4f, GlobalContext::SCREEN_WIDTH * 1.4);
  std::uniform_int_distribution<> disy(-GlobalContext::SCREEN_HEIGHT / 2, -GlobalContext::SCREEN_HEIGHT / 2 + 200);

  for (int i = 0; i < 11; ++i) {
    float x = disx(gen);
    float y = disy(gen);
    trashPositions.emplace_back(x, y);
  }
}

void Episode1::update() {
  timeFromStart += GlobalContext::TICK_DELTA;
  switch (stage) {
  case Stages::Intro:
  {
    if (timeFromStart > INTRO_STAGE_LENGTH) {
      changeStage(Stages::SelectCase);
    }

    break;
  }

  case Stages::SelectCase:
  {
    if (selectorState == MOVE && timeFromStart - selectorMoveStart > SELECTOR_ANIMATION_LENGTH) {
      selectorState = WAIT;
    }

    break;
  }

  case Stages::HelpToCollect:
  {
    if (numPieces >= 10) {
      GlobalContext::cash += (numPieces - 1) * 2 + barCollected ? 100 : 0;
      changeStage(Stages::Ending);
    }

    center0 = center1;

    if (glfwGetKey(GlobalContext::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      center1 = center0 - GlobalContext::TICK_DELTA * SPEED;
    }

    if (glfwGetKey(GlobalContext::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      center1 = center0 + GlobalContext::TICK_DELTA * SPEED;
    }

    if (fabs(center1[0]) > 1280) {
      center1[0] = 1280 * fjfj::sign(center1[0]);
    }

    break;
  }

  case Stages::RefuseToHelp:
  {
    if (timeFromStart > REFUSE_TO_HELP_LENGTH) {
      changeStage(Stages::Ending);
    }

    break;
  }

  case Stages::HandToCops:
  {
    if (timeFromStart > HAND_TO_COPS_ANIMATION_LENGTH) {
      GlobalContext::broAvialable[0] = 0;
      changeStage(Stages::Ending);
    }

    break;
  }

  case Stages::CollectBar:
  {
    if (timeFromStart > COLLECT_BAR_ANIMATION_LENGTH) {
      GlobalContext::broAvialable[1] = 0;
      stage = Stages::HelpToCollect;
    }

    break;
  }

  case Stages::Ending:
  {
    if (numPieces >= 10) {
      GlobalContext::cash += (numPieces - 1) * 2 + barCollected ? 100 : 0;
    }

    GlobalContext::changeScene(GlobalContext::episodesScreen.get());

    break;
  }
  }
}

void Episode1::draw(float complete) {
  auto center = center0 + complete * (center1 - center0);
  camera.position = -center;
  camera.update();

  switch (stage) {
  case Stages::Intro:
  {
    ResourseManager::alphaShader->Use();
    glUniformMatrix4fv(alpha_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    auto gopnikProgress = (timeFromStart - GOPNIK_START_TIME) / GOPNIK_LENGTH;
    auto bubbleProgress = (timeFromStart - BUBBLE_START_TIME) / BUBBLE_LENGTH;
    drawDefaultBackround();
    drawGopnik(gopnikProgress);
    drawDialogInterface();
    drawBubble(bubbleProgress);
    if (bubbleProgress > 1) {
      drawQuestionText();
    }

    break;
  }
  case Stages::SelectCase:
  {
    ResourseManager::alphaShader->Use();
    glUniformMatrix4fv(alpha_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    glUniform1f(alpha_aplha_location, 1);
    drawDefaultBackround();
    drawGopnik();
    drawBubble();
    drawDialogInterface();
    drawQuestionText();
    drawDialogText();
    break;
  }
  case Stages::RefuseToHelp:
  {
    ResourseManager::alphaShader->Use();
    glUniformMatrix4fv(alpha_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    glUniform1f(alpha_aplha_location, 1);
    drawDefaultBackround();
    drawSadGopnik();
    drawDialogInterface();
    break;
  }
  case Stages::HelpToCollect:
  {
    ResourseManager::alphaShader->Use();
    glUniformMatrix4fv(alpha_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    drawQuestBackround(complete, 1);
    glUniform1f(alpha_aplha_location, 1);
    drawTrash();
  }
  case Stages::CollectBar:
  {
    ResourseManager::alphaShader->Use();
    glUniformMatrix4fv(alpha_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    glUniform1f(alpha_aplha_location, 1);
    drawQuestBackround(complete, timeFromStart / COLLECT_BAR_ANIMATION_LENGTH);
    glUniform1f(alpha_aplha_location, 1);
    drawTrash();
    break;
  }
  case Stages::HandToCops:
  {
    ResourseManager::alphaShader->Use();
    glUniformMatrix4fv(alpha_proj_location, 1, GL_FALSE, glm::value_ptr(camera.proj));
    glUniform1f(alpha_aplha_location, 1);
    drawArrest();
    break;
  }
  }
}

void Episode1::onMouseButton(int button, int action, int mods) {
  if (stage == Stages::HelpToCollect && button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
    double x, y;
    glfwGetCursorPos(GlobalContext::window, &x, &y);
    x -= center1.x + GlobalContext::SCREEN_WIDTH / 2;
    y = 360 - y;


    for (int i = 0; i < trashPositions.size(); i++) {
      auto& pos = trashPositions[i];
      if (glm::length(pos - glm::vec2{ x, y }) < 50) {
        pos = { -9001, -9001 };
        ++numPieces;
      }
    }

    if (glm::length(glm::vec2{ 1850 - x, -200 - y }) < 100) {
      barCollected = true;
      changeStage(Stages::CollectBar);
    }
  }
}

void Episode1::onKey(int key, int scancode, int action, int mods) {
  switch (stage) {
  case Stages::SelectCase:
  {
    switch (key) {
    case GLFW_KEY_UP:
    {
      if (action == GLFW_PRESS && selectorState == WAIT) {
        if (selectorPos - 1 >= 0) {
          selectorState = MOVE;
          oldSelectPos = selectorPos;
          --selectorPos;
          selectorMoveStart = timeFromStart;
        }
      }

      break;
    }

    case GLFW_KEY_DOWN:
    {
      if (action == GLFW_PRESS && selectorState == WAIT) {
        if (selectorPos + 1 < N_BUTTONS) {
          selectorState = MOVE;
          oldSelectPos = selectorPos;
          ++selectorPos;
          selectorMoveStart = timeFromStart;
        }
      }

      break;
    }

    case GLFW_KEY_ENTER:
    {
      if (action == GLFW_RELEASE && selectorState == WAIT) {
        switch (selectorPos) {
        case 0: changeStage(Stages::RefuseToHelp); break;
        case 1: changeStage(Stages::HelpToCollect); break;
        case 2: changeStage(Stages::HandToCops); break;
        }
      }

      break;
    }
    }

    break;
  }
  }
}

float Episode1::getSelectorYCoord(float pos) {
  return -GlobalContext::SCREEN_HEIGHT / 2 + 30 + 42 * (N_BUTTONS - pos);
}

void Episode1::changeStage(Stages stage1) {
  stage = stage1;
  timeFromStart = 0;
}

std::unique_ptr<Scene> createEpisode1() {
  return std::make_unique<Episode1>();
}

void Episode1::drawSelector() {
  float selectorYcoord = 0;
  switch (selectorState) {
  case WAIT:
  {
    selectorYcoord = getSelectorYCoord(1 + selectorPos);
    break;
  }

  case MOVE:
  {
    selectorYcoord = getSelectorYCoord(1 + oldSelectPos + fjfj::sign(selectorPos - oldSelectPos) * (timeFromStart - selectorMoveStart) / SELECTOR_ANIMATION_LENGTH);
    break;
  }
  }
  glUniform1f(alpha_aplha_location, 1);
  batch.draw(*ResourseManager::dialogeChoose.get(), alpha_model_location,
    glm::vec2{ 0, selectorYcoord }, GlobalContext::SCREEN_WIDTH, 35);
}

void Episode1::drawGopnik(float alpha) {
  glUniform1f(alpha_aplha_location, alpha);
  batch.draw(*ResourseManager::gopnikTexture.get(), alpha_model_location, glm::vec2{ 0, 0 }, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);
}

void Episode1::drawSadGopnik() {
  glUniform1f(alpha_aplha_location, 1);
  batch.draw(*ResourseManager::gopnikSadTexture.get(), alpha_model_location, glm::vec2{ 0, 0 }, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);
}

void Episode1::drawDefaultBackround(float alpha) {
  glUniform1f(alpha_aplha_location, alpha);
  batch.draw(*ResourseManager::gopnikBackgroundTexture.get(), alpha_model_location, glm::vec2{ 0, 0 }, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);
}

void Episode1::drawQuestBackround(float complete, float alpha) {
  auto center = center0 + complete * (center1 - center0);
  batch.draw(*ResourseManager::nightBackgroundTexture.get(), alpha_model_location, -center * 2.0f / 3.0f, GlobalContext::SCREEN_WIDTH * 2, GlobalContext::SCREEN_HEIGHT);

  if (stage != Stages::CollectBar) {
    glUniform1f(alpha_aplha_location, 1);
    batch.draw(*ResourseManager::episode1BackgroundTexture.get(), alpha_model_location, { 0, 0 }, GlobalContext::SCREEN_WIDTH * 3, GlobalContext::SCREEN_HEIGHT);
  } else {
    glUniform1f(alpha_aplha_location, 1 - alpha);
    batch.draw(*ResourseManager::episode1LightTexture.get(), alpha_model_location, { 0, 0 }, GlobalContext::SCREEN_WIDTH * 3, GlobalContext::SCREEN_HEIGHT);
    glUniform1f(alpha_aplha_location, alpha);
    batch.draw(*ResourseManager::episode1FriendTexture.get(), alpha_model_location, { 0, 0 }, GlobalContext::SCREEN_WIDTH * 3, GlobalContext::SCREEN_HEIGHT);
  }


}

void Episode1::drawBubble(float alpha) {
  glUniform1f(alpha_aplha_location, alpha);
  batch.draw(*ResourseManager::bubbleTexture.get(), alpha_model_location, glm::vec2{ 0.3, 0 }, GlobalContext::SCREEN_WIDTH / 3, GlobalContext::SCREEN_HEIGHT / 3);
}

void Episode1::drawQuestionText() {
  float textX = -100;
  float textY = 50;

  font.draw(&batch, &camera, L"помоги собрать", textX + 0, textY + 0, 20, 30);
  font.draw(&batch, &camera, L"металлолом", textX + 0, textY - 35, 20, 30);
}

void Episode1::drawDialogInterface() {
  glUniform1f(alpha_aplha_location, 1);
  batch.draw(*ResourseManager::dialogeInterface.get(), alpha_model_location,
    glm::vec2{ 0, 0 }, (float)GlobalContext::SCREEN_WIDTH, (float)GlobalContext::SCREEN_HEIGHT);

  drawSelector();
}

void Episode1::drawDialogText() {
  auto y1 = getSelectorYCoord(1);
  auto y2 = getSelectorYCoord(2);
  auto y3 = getSelectorYCoord(3);
  float x = -600;

  font.draw(&batch, &camera, L"не помогать", x + 0, y1 + 0, 20, 30);
  font.draw(&batch, &camera, L"помогать", x + 0, y2 + 0, 20, 30);
  font.draw(&batch, &camera, L"сдать копам", x + 0, y3 + 0, 20, 30);
}

void Episode1::drawTrash() {

  for (int i = 0; i < trashPositions.size(); i++) {
    fjfj::Texture* tex;
    switch (i % 3) {
    case 0: tex = ResourseManager::trash1Texture.get(); break;
    case 1: tex = ResourseManager::trash2Texture.get(); break;
    case 2: tex = ResourseManager::trash3Texture.get(); break;
    }

    batch.draw(*tex, alpha_model_location, trashPositions[i], 80, 80);
  }

  if (!barCollected) {
    batch.draw(*ResourseManager::trash4Texture.get(), alpha_model_location, { 1850, -200 }, 200, 300);
  }
}

void Episode1::drawArrest() {
  float percent = timeFromStart / HAND_TO_COPS_ANIMATION_LENGTH;
  batch.draw(*ResourseManager::arrestTexture.get(), alpha_model_location, { 0, 0 }, GlobalContext::SCREEN_WIDTH * (1 + 0.1 * percent), GlobalContext::SCREEN_HEIGHT * (1 + 0.1 * percent));
}

