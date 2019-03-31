//
// Created by hedonistant on 30.03.19.
//

#include "Episode1.h"
#include <memory>
#include <game/GlobalContext.h>
#include <utils/resourseManager.h>
#include <iostream>

const int Episode1::N_BUTTONS = 3;
const float Episode1::INTRO_STAGE_LENGTH = 10;
const float Episode1::GOPNIK_START_TIME = 0;
const float Episode1::GOPNIK_LENGTH = 3;
const float Episode1::BUBBLE_START_TIME = 2;
const float Episode1::BUBBLE_LENGTH = 1;

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
  buttonPos = 0;
  stage = Stages::Intro;
}

void Episode1::update() {
  timeFromStart += GlobalContext::TICK_DELTA;
  switch (stage) {
  case Stages::Intro: {
    if (timeFromStart > INTRO_STAGE_LENGTH) {
      //changeStage(Stages::SelectCase);
    }

    break;
  }

  case Stages::SelectCase: {
    break;
  }

  case Stages::HelpToCollect: {
    if (numPieces >= 10) {
      GlobalContext::cash += (numPieces - 1) * 2 + barCollected ? 100 : 0;
      stage = Stages::Ending;
    }

    break;
  }

  case Stages::RefuseToHelp: {
    //some visual content
    if (timeFromStart > 5) {
      stage = Stages::Ending;
    }

    break;
  }

  case Stages::HandToCops: {
    //some visual content

    GlobalContext::broAvialable[0] = 0;
    stage = Stages::Ending;

    break;
  }

  case Stages::CollectBar: {
    if (timeFromStart > 5) {
      GlobalContext::broAvialable[1] = 0;
      stage = Stages::HelpToCollect;
    }

    break;
  }

  case Stages::Ending: {

    if (numPieces >= 10) {
      GlobalContext::cash += (numPieces - 1) * 2 + barCollected ? 100 : 0;
      stage = Stages::Ending;
    }

    break;
  }
  }
}

void Episode1::draw(float complete) {
  camera.update();
  switch (stage) {
  case Stages::Intro: {
    ResourseManager::alphaShader->Use();
    glUniformMatrix4fv(alpha_model_location, 1, GL_FALSE, glm::value_ptr(camera.proj));

    glUniform1f(alpha_aplha_location, 1);
    batch.draw(*ResourseManager::gopnikBackgroundTexture.get(), alpha_proj_location, glm::vec2{0, 0}, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);

    auto gopnikProgress = (timeFromStart - GOPNIK_START_TIME) / GOPNIK_LENGTH;
    glUniform1f(alpha_aplha_location, gopnikProgress);
    batch.draw(*ResourseManager::gopnikTexture.get(), alpha_proj_location, glm::vec2{0, 0}, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);
    
    auto bubbleProgress = (timeFromStart - BUBBLE_START_TIME) / BUBBLE_LENGTH;
    glUniform1f(alpha_aplha_location, bubbleProgress);
    batch.draw(*ResourseManager::bubbleTexture.get(), alpha_proj_location, glm::vec2{0.3, 0}, GlobalContext::SCREEN_WIDTH/3, GlobalContext::SCREEN_HEIGHT/3);

    font.draw(&batch, &camera, L"слыш)ты", 0, 0, 50, 50);
    //std::cout << "gopnik progress=" << gopnikProgress << s;td::endl;
    std::cout << "bubble progress=" << bubbleProgress << std::endl;
    break;
  }
  }
}

void Episode1::onMouseButton(int button, int action, int mods) {
  if (stage == Stages::HelpToCollect) {

  }
}

void Episode1::onKey(int key, int scancode, int action, int mods) {
  switch (stage) {
  case Stages::SelectCase: {
    switch (key) {
    case GLFW_KEY_UP: {
      if (action == GLFW_PRESS) {
        buttonPos = (buttonPos + N_BUTTONS - 1) % N_BUTTONS;
      }

      break;
    }

    case GLFW_KEY_DOWN: {
      if (action == GLFW_PRESS) {
        buttonPos += 1;
        buttonPos = buttonPos > 2 ? 0 : buttonPos;
      }

      break;
    }

    case GLFW_KEY_ENTER: {
      if (action == GLFW_RELEASE) {
        switch (buttonPos) {
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

void Episode1::changeStage(Stages stage1) {
  stage = stage1;
  timeFromStart = 0;
}

std::unique_ptr<Scene> createEpisode1() {
  return std::make_unique<Episode1>();
}