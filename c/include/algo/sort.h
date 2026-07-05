#pragma once

#include "utils/compare.h"

// O(N^2)
void bubble_sort(int *begin, int *end, compare_fn compare);
void selection_sort(int *begin, int *end, compare_fn compare);
void insertion_sort(int *begin, int *end, compare_fn compare);

// O(N log N)
void merge_sort(int *begin, int *end, compare_fn compare);
void quick_sort(int *begin, int *end, compare_fn compare);
