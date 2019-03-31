#pragma once

#include <GL/glew.h>
#include <memory>
#include <game/GlobalContext.h>
#include <iostream>
#include <OrthographicCamera.h>
#include <SpriteBatch.h>

class Episode2 : public Scene {
public:
  Episode2();

  void init() override;
  void enter() override;
  void update() override;
  void draw(float complete) override;

private:
  fjfj::OrthographicCamera camera;
  fjfj::SpriteBatch batch;

  GLint simple_model_location = -2;
  GLint simple_proj_location = -2;

  float timeElapsed;

};

std::unique_ptr<Scene> createEpisode2();
