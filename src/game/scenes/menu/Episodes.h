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
};

std::unique_ptr<Scene> createEpisodesScene();
