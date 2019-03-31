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

  GLint animated_model_location = -2;
  GLint animated_proj_location = -2;
  GLint animated_time_location = -2;
  GLint animated_frameTime_location = -2;
  GLint animated_frameCount_location = -2;

  float elapsedTime = 0;
  float human_speed = 0.15f;
  float human_frames = 6;

  int friendId;
  std::vector<int> graffity = { 0, 1, 2, 3, 4, 5 };
  bool isWashed[6] = { false, false, false, false, false, false };
  std::map<int, fjfj::Texture*> indexToTexture;
  int goodWashed = 0;
  int badWashed = 0;

  float moveProgress = 0;
  int moveDir = 0;

  
};
