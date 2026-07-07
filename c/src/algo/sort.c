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

  k = tmp;
  while (begin < j)
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

// quick sort lomuto partition helper using middle-element
int *lomuto_partition(int *begin, int *end, compare_fn compare) {
  int *pivot_mid = begin + ((end - begin) >> 1);

  int pivot_val = *pivot_mid;
  swap(pivot_mid, end - 1);

  for (int *j = begin; j < end - 1; j++) {
    if (compare(*j, pivot_val) <= 0)
      swap(begin++, j);
  }

  swap(begin, end - 1);
  return begin;
}

// O(N log N) time and O(log N) call stack space
void quick_lomuto_sort(int *begin, int *end, compare_fn compare) {
  if (begin + 1 < end) {
    int *pivot = lomuto_partition(begin, end, compare);

    quick_lomuto_sort(begin, pivot, compare);
    quick_lomuto_sort(pivot + 1, end, compare);
  }
}
