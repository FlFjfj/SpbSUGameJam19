#pragma once

#include <Shader.h>
#include <Texture.h>
#include <Mesh.h>

class ResourseManager {
public:
  static void initResourses();

  static std::unique_ptr<fjfj::Mesh> squareMesh;

  static std::unique_ptr <fjfj::Shader> simpleShader;
  static std::unique_ptr <fjfj::Shader> animatedShader;
  static std::unique_ptr <fjfj::Shader> alphaShader;
  static std::unique_ptr <fjfj::Shader> postShader;

  static std::unique_ptr <fjfj::Texture> fontTexture;

  static std::unique_ptr <fjfj::Texture> noiseTexture;
  static std::unique_ptr <fjfj::Texture> dialogeInterface;
  static std::unique_ptr <fjfj::Texture> dialogeChoose;
  static std::unique_ptr <fjfj::Texture> bubbleTexture;

  static std::unique_ptr <fjfj::Texture> kachokTexture;
  static std::unique_ptr <fjfj::Texture> gopnikTexture;

  static std::unique_ptr <fjfj::Texture> menuTexture;
  static std::unique_ptr <fjfj::Texture> startButtonTexture;
  static std::unique_ptr <fjfj::Texture> episodesTexture;

  static std::unique_ptr <fjfj::Texture> episode1BackgroundTexture;
  static std::unique_ptr <fjfj::Texture> episode1FriendTexture;
  static std::unique_ptr <fjfj::Texture> episode1LightTexture;
  static std::unique_ptr <fjfj::Texture> arrestTexture;
  static std::unique_ptr <fjfj::Texture> gopnikBackgroundTexture;
  static std::unique_ptr <fjfj::Texture> gopnikSadTexture;
  static std::unique_ptr <fjfj::Texture> nightBackgroundTexture;
  static std::unique_ptr <fjfj::Texture> trash1Texture;
  static std::unique_ptr <fjfj::Texture> trash2Texture;
  static std::unique_ptr <fjfj::Texture> trash3Texture;
  static std::unique_ptr <fjfj::Texture> trash4Texture;

  static std::unique_ptr <fjfj::Texture> ep2dialogBack;
  static std::unique_ptr <fjfj::Texture> ep2gameplayBack;
  static std::unique_ptr <fjfj::Texture> ep2human;

  static std::unique_ptr <fjfj::Texture> doctor;

  static std::unique_ptr <fjfj::Texture> bad1;
  static std::unique_ptr <fjfj::Texture> bad2;
  static std::unique_ptr <fjfj::Texture> bad3;

  static std::unique_ptr <fjfj::Texture> good1;
  static std::unique_ptr <fjfj::Texture> good2;
  static std::unique_ptr <fjfj::Texture> good3;

};
