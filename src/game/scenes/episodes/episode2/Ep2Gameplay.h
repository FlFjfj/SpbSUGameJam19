#pragma once

#include <GL/glew.h>
#include <memory>
#include <game/GlobalContext.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include <OrthographicCamera.h>
#include <SpriteBatch.h>
#include <BitmapFont.h>


class Episode2Gameplay : public Scene {
public:
  Episode2Gameplay(int choosen);

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

  int friendId;
  std::vector<int> graffity = { 0, 1, 2, 3, 4, 5 };
  std::map<int, fjfj::Texture*> indexToTexture;

  float moveProgress = 0;
  int moveDir = 0;

  float progress = 0;
  int choosenVariant = 0;
  bool moveDown = true;

  enum DialogeState {
    WAIT, MOVE
  } state = WAIT;;
};
