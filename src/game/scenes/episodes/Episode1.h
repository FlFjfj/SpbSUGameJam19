#pragma once

#include <GL/glew.h>

#include <memory>
#include <vector>

#include <OrthographicCamera.h>
#include <SpriteBatch.h>
#include <BitmapFont.h>
#include <game/Scene.h>
/*
 Player can
    help friend0 to collect scrap metal (HelpToCollect)
    refuse to help (RefuseToHelp)
    hand friend0 to cops and lose him

    if player helps he can
        CollectBar (and other stuff) and lose friend1 (CollectBar) but make more money
        Collect other stuff and keep friend1

 */

enum class Stages {
  Intro,
  SelectCase,
  HelpToCollect,
  RefuseToHelp,
  HandToCops,
  CollectBar,
  Ending
};

class Episode1 : public Scene {
public:
  Episode1();

  void init() override;
  void enter() override;
  void update() override;
  void draw(float complete) override;
  void onMouseButton(int button, int action, int mods) override;
  void onKey(int key, int scancode, int action, int mods) override;

  float getSelectorYCoord(float pos);

private:
  void changeStage(Stages stage1);

  void drawSelector();

  void drawGopnik(float alpha = 1);

  void drawSadGopnik();

  void drawDefaultBackround(float alpha = 1);

  void drawQuestBackround(float complete, float alpha = 1);

  void drawBubble(float alpha = 1);

  void drawQuestionText();

  void drawDialogInterface();

  void drawDialogText();

  void drawTrash();

  void drawArrest();

  float timeFromStart;
  int numPieces;
  bool barCollected;
  Stages stage;
  int selectorPos;
  float selectorMoveStart;
  int selectorState;
  int oldSelectPos;
  glm::vec2 center0;
  glm::vec2 center1;
  std::vector<glm::vec2> trashPositions;

  fjfj::OrthographicCamera camera;
  fjfj::SpriteBatch batch;
  fjfj::BitmapFont font;

  GLint alpha_model_location = -2;
  GLint alpha_proj_location = -2;
  GLint alpha_aplha_location = -2;

  static const int N_BUTTONS;
  static const float INTRO_STAGE_LENGTH;
  static const float GOPNIK_START_TIME;
  static const float GOPNIK_LENGTH;
  static const float BUBBLE_START_TIME;
  static const float BUBBLE_LENGTH;
  static const float SELECTOR_ANIMATION_LENGTH;
  static const float REFUSE_TO_HELP_LENGTH;
  static const float COLLECT_BAR_ANIMATION_LENGTH;
  static const float HAND_TO_COPS_ANIMATION_LENGTH;
  static const glm::vec2 SPEED;
};

std::unique_ptr<Scene> createEpisode1();
