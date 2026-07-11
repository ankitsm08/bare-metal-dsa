#pragma once

#include "utils/compare.h"
#include <stddef.h>

// O(N) linear search
int *linear_search(const int *begin, const int *end, int target);

// O(log N) binary search on sorted ranges
int *binary_search(const int *begin, const int *end, int target, compare_fn compare);
int *lower_bound(const int *begin, const int *end, int target, compare_fn compare);
int *upper_bound(const int *begin, const int *end, int target, compare_fn compare);
