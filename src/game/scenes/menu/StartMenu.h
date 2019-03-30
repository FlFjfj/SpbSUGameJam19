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

  GLint model_location;
  GLint proj_location;
};

std::unique_ptr<Scene> createStartMenu();
