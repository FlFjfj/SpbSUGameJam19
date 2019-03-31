#include "MainGame.h"

#include <utils/resourseManager.h>
#include <game/GlobalContext.h>
#include <iostream>

#include <game/scenes/menu/StartMenu.h>
#include <game/scenes/menu/Episodes.h>
#include <game/scenes/test/TestScene.h>

#include <game/scenes/episodes/Episode1.h>
#include <game/scenes/episodes/episode2/Episode2.h>

void MainGame::onMouseCallback(GLFWwindow *, int button, int action, int mods) {
  GlobalContext::currentScene->onMouseButton(button, action, mods);
}

void MainGame::onKeyCallback(GLFWwindow *, int key, int scancode, int action, int mods) {
  GlobalContext::currentScene->onKey(key, scancode, action, mods);
}

MainGame::MainGame() {}

void MainGame::init(GLFWwindow* window) {
  glfwWindowHint(GLFW_SAMPLES, 4);
  glEnable(GL_MULTISAMPLE);
  //glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  ResourseManager::initResourses();
  auto error = glGetError();
  std::cout << "resource init error: " << error << std::endl;

  GlobalContext::window = window;
  GlobalContext::startMenu = createStartMenu();
  GlobalContext::episodesScreen = createEpisodesScene();
  GlobalContext::testScene = createTestScene();
  GlobalContext::eposides.emplace_back(createEpisode1());
  GlobalContext::eposides.emplace_back(createEpisode2());

  GlobalContext::reset();
  //GlobalContext::changeScene(GlobalContext::startMenu.get());
  GlobalContext::changeScene(GlobalContext::eposides[0].get());


  glfwSetMouseButtonCallback(window, MainGame::onMouseCallback);
  glfwSetKeyCallback(window, MainGame::onKeyCallback);

  batch = new fjfj::SpriteBatch();
  camera = new fjfj::OrthographicCamera(GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);
  camera->update();
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glGenTextures(1, &fbtex.texture);
  glBindTexture(GL_TEXTURE_2D, fbtex.texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbtex.texture, 0);

  post_model_location = glGetUniformLocation(ResourseManager::postShader.get()->Program, "u_ModelTrans");
  post_proj_location = glGetUniformLocation(ResourseManager::postShader.get()->Program, "u_ProjTrans");
}

void MainGame::update(float delta) {
  timeSinceTick += delta;

  while (timeSinceTick > GlobalContext::TICK_DELTA) {
    timeSinceTick -= GlobalContext::TICK_DELTA;
    GlobalContext::currentScene->update();
  }

  float completion = timeSinceTick / GlobalContext::TICK_DELTA;

  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glClear(GL_COLOR_BUFFER_BIT);
  GlobalContext::currentScene->draw(completion);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ResourseManager::postShader->Use();
  glUniformMatrix4fv(post_proj_location, 1, GL_FALSE, glm::value_ptr(camera->proj));
  batch->draw(fbtex, post_model_location, { 0, 0 }, GlobalContext::SCREEN_WIDTH, GlobalContext::SCREEN_HEIGHT);
}



