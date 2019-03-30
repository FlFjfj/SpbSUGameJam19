#include "cameraControl.h"

#include <iostream>

CameraControl::CameraControl(bool plain, bool enabled) : 
  plain(plain), 
  enabled(enabled) {}

void CameraControl::update(GLFWwindow* window) {
  if (enabled) {
    //auto& cam = ecs.graphics.camera;
    //
    ////glm::vec3 front = plain ? glm::normalize(glm::vec3{ cam.Front.x, 0, cam.Front.z }) : cam.Front;
    ////glm::vec3 right = plain ? glm::normalize(glm::vec3{ cam.Right.x, 0, cam.Right.z }) : cam.Right;
    ////
    ////if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    ////  cam.Position = cam.Position + (0.01f * front);
    ////}
    ////
    ////if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    ////  cam.Position = cam.Position - (0.01f * front);
    ////}
    ////
    ////if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    ////  cam.Position = cam.Position + (0.01f * right);
    ////}
    ////
    ////if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    ////  cam.Position = cam.Position - (0.01f * right);
    ////}
    //
    //double nx, ny;
    //glfwGetCursorPos(window, &nx, &ny);
    //double dx = lastPosX - nx, dy = lastPosY - ny;
    //lastPosX = nx;
    //lastPosY = ny;
    //
    //cam.Front = glm::rotate(
    //  glm::rotate(
    //    glm::mat4(1.0),
    //    (float)dx / 800.0f, glm::vec3{ 0, 1.0, 0.0 })
    //  , (float)dy / 800.0f, cam.Right)
    //  * glm::vec4{ cam.Front.x, cam.Front.y, cam.Front.z, 1.0 };
  }
}
