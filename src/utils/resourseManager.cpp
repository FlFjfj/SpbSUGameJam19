#include "resourseManager.h"

std::unique_ptr<fjfj::Mesh> ResourseManager::squareMesh;

std::unique_ptr <fjfj::Shader> ResourseManager::simpleShader;

std::unique_ptr <fjfj::Texture> ResourseManager::wallTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::floorTexture;

void ResourseManager::initResourses() {
  GLfloat vert[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
  };

  squareMesh = std::make_unique<fjfj::Mesh>(fjfj::Mesh(vert, 6));

  simpleShader = std::make_unique<fjfj::Shader>("assets/shader/sample.vert", "assets/shader/sample.frag");

  wallTexture = std::make_unique<fjfj::Texture>("assets/texture/wall.png");
  floorTexture = std::make_unique<fjfj::Texture>("assets/texture/floor.png");
}
