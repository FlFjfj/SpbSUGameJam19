#include <memory>
#include "resourseManager.h"

std::unique_ptr<fjfj::Mesh> ResourseManager::squareMesh;

std::unique_ptr <fjfj::Shader> ResourseManager::simpleShader;
std::unique_ptr <fjfj::Shader> ResourseManager::animatedShader;

std::unique_ptr <fjfj::Texture> ResourseManager::noiseTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::dialogeInterface;
std::unique_ptr <fjfj::Texture> ResourseManager::dialogeChoose;

std::unique_ptr <fjfj::Texture> ResourseManager::menuTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::startButtonTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::episodesTexture;

std::unique_ptr <fjfj::Texture> ResourseManager::ep2ChooseFriend;
std::unique_ptr <fjfj::Texture> ResourseManager::ep2dialogBack;

void ResourseManager::initResourses() {
  simpleShader = std::make_unique<fjfj::Shader>("assets/shader/simple.vert", "assets/shader/simple.frag");
  animatedShader = std::make_unique<fjfj::Shader>("assets/shader/animated.vert", "assets/shader/animated.frag");


  noiseTexture     = std::make_unique<fjfj::Texture>("assets/texture/noise.png");
  dialogeInterface = std::make_unique<fjfj::Texture>("assets/texture/dialogueInterface.png");
  dialogeChoose    = std::make_unique<fjfj::Texture>("assets/texture/dialogueChoose.png");

  menuTexture = std::make_unique<fjfj::Texture>("assets/texture/menuScene.png");
  startButtonTexture = std::make_unique<fjfj::Texture>("assets/texture/startButton.png");
  episodesTexture = std::make_unique<fjfj::Texture>("assets/texture/episodesScreen.png");

  ep2ChooseFriend = std::make_unique<fjfj::Texture>("assets/texture/episode2/chooseFriend.png");
  ep2dialogBack   = std::make_unique<fjfj::Texture>("assets/texture/episode2/dialogBackground.png");
}
