#include "algo/sort.h"

static inline void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// O(N^2)

// don't use
void bubble_sort(int *begin, int *end, compare_fn compare) {
  for (int *i = end - 1; i >= begin; i--) {
    for (int *j = begin; j < i; j++) {
      if (compare(*j, *(j + 1)) > 0)
        swap(j, j + 1);
    }
  }
}

// minimal writes
void selection_sort(int *begin, int *end, compare_fn compare) {
  for (int *i = begin; i < end - 1; i++) {
    int *selected = i;

    for (int *j = i + 1; j < end; j++) {
      if (compare(*selected, *j) > 0)
        selected = j;
    }

    if (selected != i)
      swap(selected, i);
  }
}
