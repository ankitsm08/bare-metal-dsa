#include "algo/sort.h"

static inline void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// O(N^2) don't use
void bubble_sort(int *begin, int *end, compare_fn compare) {
  for (int *i = end - 1; i >= begin; i--) {
    for (int *j = begin; j < i; j++) {
      if (compare(*j, *(j + 1)) > 0)
        swap(j, j + 1);
    }
  }
}

// O(N^2) minimal writes
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

// O(N^2) average but O(N) when nearly sorted
void insertion_sort(int *begin, int *end, compare_fn compare) {
  for (int *i = begin + 1; i < end; i++) {
    const int key = *i;
    int *j = i;

    while (--j >= begin && compare(*j, key) > 0)
      *(j + 1) = *j;

    *(j + 1) = key;
  }
}
