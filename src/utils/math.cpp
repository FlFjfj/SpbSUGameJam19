#include "math.h"

float fjfj::lerp(float start, float end, float percent) {
  return (start + percent * (end - start));
}

float fjfj::clamp(float val, float minimum, float maximum) {
  if (val < minimum)
    return minimum;
  if (val > maximum)
    return maximum;

  return val;
}

float fjfj::sign(float x) {
  return x > 0 ? 1 : -1;
}
