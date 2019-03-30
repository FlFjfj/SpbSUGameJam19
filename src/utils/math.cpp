#include "math.h"

float fjfj::lerp(float start, float end, float percent) {
  return (start + percent * (end - start));
}