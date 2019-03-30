#pragma once

#include <Shader.h>
#include <Texture.h>
#include <Mesh.h>

class ResourseManager {
public:
  static void initResourses();

  static std::unique_ptr<fjfj::Mesh> squareMesh;

  static std::unique_ptr <fjfj::Shader> simpleShader;

  static std::unique_ptr <fjfj::Texture> wallTexture;
  static std::unique_ptr <fjfj::Texture> floorTexture;
};