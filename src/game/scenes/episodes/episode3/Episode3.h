#pragma once

#include <GL/glew.h>
#include <memory>
#include <game/GlobalContext.h>
#include <iostream>

#include <OrthographicCamera.h>
#include <SpriteBatch.h>
#include <BitmapFont.h>


class Episode3 : public Scene {
public:
  Episode3();

  void init() override;
  void enter() override;
  void update() override;
  void draw(float complete) override;

  float getSelectorYCoord(float pos);

private:
  fjfj::OrthographicCamera camera;
  fjfj::SpriteBatch batch;
  fjfj::BitmapFont font;

  GLint simple_model_location = -2;
  GLint simple_proj_location = -2;

  float timeElapsed = 0;

  float progress = 0;
  int choosenVariant = 1;
  int selectorPos = 1;
  int oldSelectorPos = 1;
  std::vector<int> available_indexes;

  bool drawBuy;
  bool drawBar;
  bool drawCite;
  bool drawOutofCash;

  enum DialogeState {
    WAIT, MOVE, FINALIZE
  } state = WAIT;;
};

std::unique_ptr<Scene> createEpisode3();
