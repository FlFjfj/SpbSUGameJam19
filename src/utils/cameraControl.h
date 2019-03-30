#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ecs/systems/updater.h>

class CameraControl {
public:
  CameraControl(bool plain, bool enabled);
  
private:
  bool plain, enabled;

  double lastPosX, lastPosY;

  void update(GLFWwindow* window);
};