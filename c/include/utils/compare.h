#pragma once

#include <stdbool.h>

typedef int (*compare_fn)(int, int);

static inline int compare_ascending(int a, int b) { return (a > b) - (a < b); }
static inline int compare_descending(int a, int b) { return (a < b) - (a > b); }

static inline bool compare_less(int a, int b) { return a < b; }
static inline bool compare_less_equal(int a, int b) { return a <= b; }

static inline bool compare_greater(int a, int b) { return a > b; }
static inline bool compare_greater_equal(int a, int b) { return a >= b; }

static inline bool compare_equal(int a, int b) { return a == b; }
static inline bool compare_not_equal(int a, int b) { return a != b; }
