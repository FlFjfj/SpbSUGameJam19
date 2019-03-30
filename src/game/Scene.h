#pragma once

class Scene {
public:
  virtual void init() = 0;
  virtual void enter() = 0;
  virtual void update() = 0;
  virtual void draw(float complete) = 0;

  virtual void onMouseButton(int buttion, int action, int mods);
  virtual void onKey(int key, int scancode, int action, int mods);

  virtual ~Scene() = default;
};