#pragma once

#include <stdbool.h>

typedef int (*compare_fn)(int, int);

inline static int compare_ascending(int a, int b) { return a - b; }
inline static int compare_descending(int a, int b) { return b - a; }

inline static bool compare_less(int a, int b) { return a < b; }
inline static bool compare_less_equal(int a, int b) { return a <= b; }

inline static bool compare_greater(int a, int b) { return a > b; }
inline static bool compare_greater_equal(int a, int b) { return a >= b; }

inline static bool compare_equal(int a, int b) { return a == b; }
inline static bool compare_not_equal(int a, int b) { return a != b; }
