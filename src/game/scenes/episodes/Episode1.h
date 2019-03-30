#pragma once

#include <memory>
#include <game/GlobalContext.h>
#include <iostream>
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

private:
  float timeFromStart;
  int numPieces;
  bool barCollected;
  Stages stage;
  int buttonPos;
  void changeStage(Stages stage1);

  static const int N_BUTTONS;
  static const float INTRO_STAGE_LENGTH;
};

std::unique_ptr<Scene> createEpisode1();
