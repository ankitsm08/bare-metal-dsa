#include "algo/sort.h"
#include "utils/compare.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    printf("[ RUNNING ] %s...\n", #test_func);                                                     \
    test_func();                                                                                   \
    printf("[ PASSED  ] %s\n\n", #test_func);                                                      \
  } while (0)

#define sz 11
const int sorted_ascending[sz] = {INT_MIN, -42, -5, -3, 1, 2, 3, 4, 5, 6, +INT_MAX};
const int sorted_descending[sz] = {INT_MAX, 6, 5, 4, 3, 2, 1, -3, -5, -42, INT_MIN};
#define UNSORTED_ARRAY {1, -5, INT_MIN, -3, 6, 4, -42, 3, INT_MAX, 2, 5}

void test_sort(void sort(int *, int *, compare_fn)) {
  int arr1[sz] = UNSORTED_ARRAY;
  sort(arr1, arr1 + sz, compare_ascending);

  for (size_t i = 0; i < sz; i++) {
    assert(arr1[i] == sorted_ascending[i]);
  }

  int arr2[sz] = UNSORTED_ARRAY;
  sort(arr2, arr2 + sz, compare_descending);

  for (size_t i = 0; i < sz; i++) {
    assert(arr2[i] == sorted_descending[i]);
  }
}

void test_bubble_sort(void) { test_sort(bubble_sort); }
void test_selection_sort(void) { test_sort(selection_sort); }
void test_insertion_sort(void) { test_sort(insertion_sort); }
void test_merge_sort(void) { test_sort(merge_sort); }

int main(void) {
  printf("Testing sort...\n\n");

  RUN_TEST(test_bubble_sort);
  RUN_TEST(test_selection_sort);
  RUN_TEST(test_insertion_sort);
  RUN_TEST(test_merge_sort);

  printf("All tests passed for sort\n");
  return 0;
}
