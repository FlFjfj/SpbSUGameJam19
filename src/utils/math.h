#pragma once
#include <cmath>

namespace fjfj {
  float lerp(float start, float end, float percent);
  float clamp(float val, float minimum, float maximum);
  float sign(float x);
}