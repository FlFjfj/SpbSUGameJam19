#include <Engine.h>

#include "MainGame.h"

int main() {
  MainGame game;
  fjfj::Engine e(game);
  e.start(1280, 720, false);
}
