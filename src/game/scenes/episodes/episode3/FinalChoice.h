#pragma once

#include <GL/glew.h>
#include <memory>
#include <game/GlobalContext.h>
#include <iostream>

#include <OrthographicCamera.h>
#include <SpriteBatch.h>
#include <BitmapFont.h>


class FinalChoice : public Scene {
public:
  FinalChoice();

  void init() override;
  void enter() override;
  void update() override;
  void draw(float complete) override;

private:
  fjfj::OrthographicCamera camera;
  fjfj::SpriteBatch batch;
  fjfj::BitmapFont font;

  GLint simple_model_location = -2;
  GLint simple_proj_location = -2;

  float timeElapsed = 0;

  float progress = 0;
  int textPart = 0;

  enum DialogeState {
    WAIT, MOVE,
  } state = WAIT;;
};
