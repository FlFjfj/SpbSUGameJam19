#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ecs/ECS.h>
#include <ecs/systems/updater.h>

class CameraControl {
public:
  CameraControl(Ecs& ecs, bool plain, bool enabled);
  
private:
  bool plain, enabled;
  Ecs& ecs;
  UpdatingComponent updaterComp;
  double lastPosX, lastPosY;

  void update(GLFWwindow* window);
};