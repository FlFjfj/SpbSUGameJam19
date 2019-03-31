#include <memory>
#include "resourseManager.h"

std::unique_ptr<fjfj::Mesh> ResourseManager::squareMesh;

std::unique_ptr <fjfj::Shader> ResourseManager::simpleShader;
std::unique_ptr <fjfj::Shader> ResourseManager::animatedShader;
std::unique_ptr <fjfj::Shader> ResourseManager::alphaShader;

std::unique_ptr <fjfj::Texture> ResourseManager::fontTexture;

std::unique_ptr <fjfj::Texture> ResourseManager::noiseTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::dialogeInterface;
std::unique_ptr <fjfj::Texture> ResourseManager::dialogeChoose;
std::unique_ptr <fjfj::Texture> ResourseManager::bubbleTexture;

std::unique_ptr <fjfj::Texture> ResourseManager::kachokTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::gopnikTexture;

std::unique_ptr <fjfj::Texture> ResourseManager::menuTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::startButtonTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::episodesTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::episode1BackgroundTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::gopnikBackgroundTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::gopnikSadTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::nightBackgroundTexture;
std::unique_ptr <fjfj::Texture> ResourseManager::trash1Texture;
std::unique_ptr <fjfj::Texture> ResourseManager::trash2Texture;
std::unique_ptr <fjfj::Texture> ResourseManager::trash3Texture;
std::unique_ptr <fjfj::Texture> ResourseManager::trash4Texture;

std::unique_ptr <fjfj::Texture> ResourseManager::ep2dialogBack;
std::unique_ptr <fjfj::Texture> ResourseManager::ep2gameplayBack;

std::unique_ptr <fjfj::Texture> ResourseManager::bad1;
std::unique_ptr <fjfj::Texture> ResourseManager::bad2;
std::unique_ptr <fjfj::Texture> ResourseManager::bad3;

std::unique_ptr <fjfj::Texture> ResourseManager::good1;
std::unique_ptr <fjfj::Texture> ResourseManager::good2;
std::unique_ptr <fjfj::Texture> ResourseManager::good3;

void ResourseManager::initResourses() {
  simpleShader = std::make_unique<fjfj::Shader>("assets/shader/simple.vert", "assets/shader/simple.frag");
  animatedShader = std::make_unique<fjfj::Shader>("assets/shader/animated.vert", "assets/shader/animated.frag");
  alphaShader = std::make_unique<fjfj::Shader>("assets/shader/alpha.vert", "assets/shader/alpha.frag");

  fontTexture = std::make_unique<fjfj::Texture>("assets/texture/font.png");

  noiseTexture     = std::make_unique<fjfj::Texture>("assets/texture/noise.png");
  dialogeInterface = std::make_unique<fjfj::Texture>("assets/texture/dialogueInterface.png");
  dialogeChoose    = std::make_unique<fjfj::Texture>("assets/texture/dialogueChoose.png");
  bubbleTexture = std::make_unique<fjfj::Texture>("assets/texture/bubble.png");

  gopnikTexture = std::make_unique<fjfj::Texture>("assets/texture/friends/gopnik.png");
  kachokTexture = std::make_unique<fjfj::Texture>("assets/texture/friends/kachok.png");

  menuTexture = std::make_unique<fjfj::Texture>("assets/texture/menuScene.png");
  startButtonTexture = std::make_unique<fjfj::Texture>("assets/texture/startButton.png");
  episodesTexture = std::make_unique<fjfj::Texture>("assets/texture/episodesScreen.png");

  episode1BackgroundTexture = std::make_unique<fjfj::Texture>("assets/texture/episode1/episode1Background.png");
  gopnikBackgroundTexture = std::make_unique<fjfj::Texture>("assets/texture/episode1/gopnikBackground.png");
  gopnikSadTexture = std::make_unique<fjfj::Texture>("assets/texture/friends/gopnikSad.png");
  nightBackgroundTexture = std::make_unique<fjfj::Texture>("assets/texture/episode1/nightBackground.png");
  trash1Texture = std::make_unique<fjfj::Texture>("assets/texture/episode1/trash1.png");
  trash2Texture = std::make_unique<fjfj::Texture>("assets/texture/episode1/trash2.png");
  trash3Texture = std::make_unique<fjfj::Texture>("assets/texture/episode1/trash3.png");
  trash4Texture = std::make_unique<fjfj::Texture>("assets/texture/episode1/trash4.png");

  ep2dialogBack   = std::make_unique<fjfj::Texture>("assets/texture/episode2/dialogBackground.png");
  ep2gameplayBack = std::make_unique<fjfj::Texture>("assets/texture/episode2/bricks.png");

  bad1 = std::make_unique<fjfj::Texture>("assets/texture/episode2/bad1.png");
  bad2 = std::make_unique<fjfj::Texture>("assets/texture/episode2/bad2.png");
  bad3 = std::make_unique<fjfj::Texture>("assets/texture/episode2/bad3.png");

  good1 = std::make_unique<fjfj::Texture>("assets/texture/episode2/good1.png");
  good2 = std::make_unique<fjfj::Texture>("assets/texture/episode2/good2.png");
  good3 = std::make_unique<fjfj::Texture>("assets/texture/episode2/good3.png");
}
