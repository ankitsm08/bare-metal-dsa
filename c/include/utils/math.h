#pragma once

#include <assert.h>

inline static int math_min(int a, int b) { return (a < b) ? a : b; }
inline static int math_max(int a, int b) { return (a > b) ? a : b; }

inline static int math_clamp(int val, int lower_bound, int upper_bound) {
  assert(lower_bound <= upper_bound);

  if (val >= upper_bound)
    return upper_bound;
  if (val <= lower_bound)
    return lower_bound;

  return val;
}
