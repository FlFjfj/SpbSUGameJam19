#include <memory>
#include "resourseManager.h"

std::unique_ptr<fjfj::Mesh> ResourseManager::squareMesh;

std::unique_ptr <fjfj::Shader> ResourseManager::simpleShader;

std::unique_ptr <fjfj::Texture> ResourseManager::menuTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::startButtonTexture;

void ResourseManager::initResourses() {
  simpleShader = std::make_unique<fjfj::Shader>("assets/shader/sample.vert", "assets/shader/sample.frag");


  menuTexture = std::make_unique<fjfj::Texture>("assets/texture/menuScene.png");
  startButtonTexture = std::make_unique<fjfj::Texture>("assets/texture/floor.png");
}
