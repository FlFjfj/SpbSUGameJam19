#pragma once
#include <GL/glew.h>

#include <memory>

#include <OrthographicCamera.h>
#include <SpriteBatch.h>

#include <game/Scene.h>

class EpisodesScene : public Scene {
public:
  EpisodesScene();

  void init() override;
  void enter() override;
  void update() override;
  void draw(float complete) override;

private:
  fjfj::OrthographicCamera camera;
  fjfj::SpriteBatch batch;

  GLint simple_model_location = -2;
  GLint simple_proj_location = -2;

  GLint animated_model_location = -2;
  GLint animated_proj_location = -2;
  GLint animated_time_location = -2;
  GLint animated_frameTime_location = -2;
  GLint animated_frameCount_location = -2;

  float elapsedTime = 0;
  const float noiseSpeed = 0.05f;
  const int noiseFrames = 6;

  int currentScreen = 0;
  float progress = 0;

  enum ScrrenState {
    EXIT, MOVE, ENTER
  } state;

  const float screenSize = 5500;
  const float screenData[16][6] = {
  {0, 0, 5500, 5500, 0, 0},
  { 1700, 2000, 1850, 1350, 1200, 900 },
  { 400, 2100, 1650, 1150, 850, 770 }
  };

};


std::unique_ptr<Scene> createEpisodesScene();
