//
// Created by hedonistant on 30.03.19.
//

#include "Episode1.h"
#include <memory>

const int Episode1::N_BUTTONS = 3;
const float Episode1::INTRO_STAGE_LENGTH = 3;

Episode1::Episode1() {
  init();
}

void Episode1::init() {
  stage = Stages::Intro;
}

void Episode1::enter() {
  numPieces = 0;
  timeFromStart = 0;
  barCollected = false;
  buttonPos = 0;
}

void  Episode1::update() {
  std::cout << buttonPos << std::endl;
  timeFromStart += GlobalContext::TICK_DELTA;
  switch (stage) {
  case Stages::Intro: {
    if (timeFromStart > INTRO_STAGE_LENGTH) {
      changeStage(Stages::SelectCase);
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
  switch (stage) {
  case Stages::Intro: {
    glClearColor(1, 0, 0, 1);
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
  std::cout << "Stage: " << (int)stage << std::endl;
}

std::unique_ptr<Scene> createEpisode1() {
  return std::make_unique<Episode1>();
}