#pragma once

#include <stddef.h>

// O(N) linear search
int *linear_search(const int *begin, const int *end, int target);

// O(log N) binary search on sorted ranges
int *binary_search(const int *begin, const int *end, int target, int (*compare)(int, int));
