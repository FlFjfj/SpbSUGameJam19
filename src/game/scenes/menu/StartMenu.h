#pragma once
#include <GL/glew.h>

#include <memory>

#include <OrthographicCamera.h>
#include <SpriteBatch.h>

#include <game/Scene.h>

class StartMenu : public Scene {
public: 
  StartMenu();

  void init() override;
  void enter() override;
  void update() override;
  void draw(float complete) override;

private:
  fjfj::OrthographicCamera camera;
  fjfj::SpriteBatch batch;

  GLint simple_model_location;
  GLint simple_proj_location;

  GLint animated_model_location;
  GLint animated_proj_location;
  GLint animated_frameData_location;

};

std::unique_ptr<Scene> createStartMenu();
