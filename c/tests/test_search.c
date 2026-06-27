#include "algo/search.h"
#include "utils/compare.h"
#include <assert.h>
#include <stdio.h>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    printf("[ RUNNING ] %s...\n", #test_func);                                                     \
    test_func();                                                                                   \
    printf("[ PASSED  ] %s\n\n", #test_func);                                                      \
  } while (0)

void test_linear_search(void) {
  int arr[] = {10, 21, 30, 42, 50, 67};
  size_t size = sizeof(arr) / sizeof(arr[0]);
  int *begin = arr;
  int *end = arr + size;

  // general elements
  assert(linear_search(begin, end, 30) == &arr[2]);
  assert(linear_search(begin, end, 10) == &arr[0]);
  assert(linear_search(begin, end, 50) == &arr[4]);

  // missing element
  assert(linear_search(begin, end, 404) == NULL);

  // empty array boundary
  assert(linear_search(begin, begin, 30) == NULL);
}

void test_binary_search(void) {
  // pre-sorted array
  int arr[] = {2, 4, 6, 8, 10, 12, 14, 16};
  size_t size = sizeof(arr) / sizeof(arr[0]);
  int *begin = arr;
  int *end = arr + size;

  // middle, boundaries, and general elements
  assert(binary_search(begin, end, 8, compare_ascending) == &arr[3]);
  assert(binary_search(begin, end, 2, compare_ascending) == &arr[0]);
  assert(binary_search(begin, end, 16, compare_ascending) == &arr[7]);

  // opposite comparator (non-middle element)
  assert(binary_search(begin, end, 6, compare_descending) == NULL); // not 10

  // missing elements (below, middle, above)
  assert(binary_search(begin, end, 1, compare_ascending) == NULL);
  assert(binary_search(begin, end, 9, compare_ascending) == NULL);
  assert(binary_search(begin, end, 99, compare_ascending) == NULL);

  // empty array boundary
  assert(binary_search(begin, begin, 8, compare_ascending) == NULL);
}

int main(void) {
  printf("Testing search...\n\n");

  RUN_TEST(test_linear_search);
  RUN_TEST(test_binary_search);

  printf("All tests passed for search\n");
  return 0;
}
