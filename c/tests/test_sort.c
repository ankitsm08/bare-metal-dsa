#include "algo/sort.h"
#include "utils/compare.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    printf("[ RUNNING ] %s...\n", #test_func);                                                     \
    test_func();                                                                                   \
    printf("[ PASSED  ] %s\n\n", #test_func);                                                      \
  } while (0)

void test_bubble_sort(void) {
  int sorted_ascending[6] = {1, 2, 3, 4, 5, 6};
  int sorted_descending[6] = {6, 5, 4, 3, 2, 1};

  int arr1[6] = {3, 4, 2, 6, 5, 1};
  bubble_sort(arr1, arr1 + 6, compare_ascending);

  for (size_t i = 0; i < 6; i++) {
    assert(arr1[i] == sorted_ascending[i]);
  }

  int arr2[6] = {3, 4, 2, 6, 5, 1};
  bubble_sort(arr2, arr2 + 6, compare_descending);

  for (size_t i = 0; i < 6; i++) {
    assert(arr2[i] == sorted_descending[i]);
  }
}

int main(void) {
  printf("Testing sort...\n\n");

  RUN_TEST(test_bubble_sort);

  printf("All tests passed for sort\n");
  return 0;
}
