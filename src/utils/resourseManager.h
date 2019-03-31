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

  static std::unique_ptr <fjfj::Texture> noiseTexture;
  static std::unique_ptr <fjfj::Texture> dialogeInterface;
  static std::unique_ptr <fjfj::Texture> dialogeChoose;


  static std::unique_ptr <fjfj::Texture> menuTexture;
  static std::unique_ptr <fjfj::Texture> startButtonTexture;
  static std::unique_ptr <fjfj::Texture> episodesTexture;

  static std::unique_ptr <fjfj::Texture> ep2ChooseFriend;
  static std::unique_ptr <fjfj::Texture> ep2dialogBack;

  //static std::unique_ptr <fjfj::Texture> ;


};