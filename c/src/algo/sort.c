#include "algo/sort.h"
#include "utils/compare.h"
#include <stdio.h>
#include <stdlib.h>

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

// merge_sort helper
void merge(int *begin, int *mid, int *end, compare_fn compare) {
  int *tmp = malloc(sizeof(int) * (end - begin));

  if (!tmp) {
    fprintf(stderr, "Fatal: Out of memory allocating merge buffer.\n");
    exit(EXIT_FAILURE);
  }

  int *i = begin, *j = mid, *k = tmp;
  while (i < mid && j < end)
    *k++ = compare(*i, *j) > 0 ? *j++ : *i++;
  while (i < mid)
    *k++ = *i++;
  while (j < end)
    *k++ = *j++;

  k = tmp;
  while (begin < end)
    *begin++ = *k++;

  free(tmp);
}

// O(N log N) time and O(N) space
void merge_sort(int *begin, int *end, compare_fn compare) {
  if (begin + 1 < end) {
    int *const mid = begin + ((end - begin) >> 1);

    merge_sort(begin, mid, compare);
    merge_sort(mid, end, compare);

    merge(begin, mid, end, compare);
  }
}
