#include "algo/search.h"
#include "utils/compare.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    printf("[ RUNNING ] %s...\n", #test_func);                                                     \
    test_func();                                                                                   \
    printf("[ PASSED  ] %s\n\n", #test_func);                                                      \
  } while (0)

#define sz 11
const int sorted[sz] = {INT_MIN + 42, -42, -5, -3, 1, 2, 3, 4, 5, 6, INT_MAX - 42};

void test_linear_search(void) {
  // first element boundary
  assert(linear_search(sorted, sorted + sz, INT_MIN + 42) == &sorted[0]);

  // general elements
  assert(linear_search(sorted, sorted + sz, -42) == &sorted[1]);
  assert(linear_search(sorted, sorted + sz, 1) == &sorted[4]);
  assert(linear_search(sorted, sorted + sz, INT_MAX - 42) == &sorted[10]);

  // missing element (positive and negative)
  assert(linear_search(sorted, sorted + sz, 404) == NULL);
  assert(linear_search(sorted, sorted + sz, -9999) == NULL);

  // single-element range
  int x = 42;
  assert(linear_search(&x, &x + 1, 42) == &x);
  assert(linear_search(&x, &x + 1, 99) == NULL);

  // empty array boundary
  assert(linear_search(sorted, sorted, 1) == NULL);
}

void test_binary_search(void) {
  // first element boundary
  assert(binary_search(sorted, sorted + sz, INT_MIN + 42, compare_ascending) == &sorted[0]);

  // every element in the array
  for (size_t i = 0; i < sz; i++)
    assert(binary_search(sorted, sorted + sz, sorted[i], compare_ascending) == &sorted[i]);

  // opposite comparator (non-middle element)
  assert(binary_search(sorted, sorted + sz, 6, compare_descending) == NULL);

  // missing elements (below, middle, above)
  assert(binary_search(sorted, sorted + sz, INT_MIN, compare_ascending) == NULL);
  assert(binary_search(sorted, sorted + sz, 42, compare_ascending) == NULL);
  assert(binary_search(sorted, sorted + sz, INT_MAX, compare_ascending) == NULL);

  // even-length array
  int even[] = {0, 2, 4, 6, 8, 10};
  assert(binary_search(even, even + 6, 0, compare_ascending) == &even[0]);
  assert(binary_search(even, even + 6, 6, compare_ascending) == &even[3]);
  assert(binary_search(even, even + 6, 10, compare_ascending) == &even[5]);
  assert(binary_search(even, even + 6, 7, compare_ascending) == NULL);

  // 1-element and 2-element arrays
  int one[] = {99};
  assert(binary_search(one, one + 1, 99, compare_ascending) == &one[0]);
  assert(binary_search(one, one + 1, 1, compare_ascending) == NULL);
  int two[] = {10, 20};
  assert(binary_search(two, two + 2, 10, compare_ascending) == &two[0]);
  assert(binary_search(two, two + 2, 20, compare_ascending) == &two[1]);
  assert(binary_search(two, two + 2, 15, compare_ascending) == NULL);

  // duplicates: returns some pointer to a matching element
  int dups[] = {1, 2, 2, 2, 3};
  int *res = binary_search(dups, dups + 5, 2, compare_ascending);
  assert(res && *res == 2);

  // empty array boundary
  assert(binary_search(sorted, sorted, 1, compare_ascending) == NULL);
}

void test_lower_bound(void) {
  // present elements
  assert(lower_bound(sorted, sorted + sz, -42, compare_ascending) == &sorted[1]);
  assert(lower_bound(sorted, sorted + sz, 1, compare_ascending) == &sorted[4]);
  assert(lower_bound(sorted, sorted + sz, INT_MAX - 42, compare_ascending) == &sorted[10]);

  // same as binary_search for present, unique elements
  assert(lower_bound(sorted, sorted + sz, 3, compare_ascending)
         == binary_search(sorted, sorted + sz, 3, compare_ascending));

  // missing: between elements
  assert(lower_bound(sorted, sorted + sz, 0, compare_ascending) == &sorted[4]);  // 1
  assert(lower_bound(sorted, sorted + sz, -4, compare_ascending) == &sorted[3]); // -3

  // missing: below all / above all
  assert(lower_bound(sorted, sorted + sz, INT_MIN, compare_ascending) == &sorted[0]);
  assert(lower_bound(sorted, sorted + sz, INT_MAX, compare_ascending) == sorted + sz);

  // empty
  assert(lower_bound(sorted, sorted, 1, compare_ascending) == sorted);

  // duplicates: first occurrence of target
  int dups[] = {1, 2, 2, 2, 3, 4, 5};
  assert(lower_bound(dups, dups + 7, 2, compare_ascending) == &dups[1]);
  assert(upper_bound(dups, dups + 7, 2, compare_ascending) == &dups[4]);

  // lower_bound vs upper_bound on duplicates
  int all_same[] = {7, 7, 7, 7};
  assert(lower_bound(all_same, all_same + 4, 7, compare_ascending) == &all_same[0]);
  assert(upper_bound(all_same, all_same + 4, 7, compare_ascending) == &all_same[4]);

  // descending comparator
  int desc[] = {10, 8, 6, 4, 2};
  assert(lower_bound(desc, desc + 5, 6, compare_descending)
         == &desc[2]); // 6: first not less than 6
  assert(lower_bound(desc, desc + 5, 5, compare_descending)
         == &desc[3]); // 4: first not less than 5
}

void test_upper_bound(void) {
  // present elements
  assert(upper_bound(sorted, sorted + sz, -42, compare_ascending) == &sorted[2]); // -5
  assert(upper_bound(sorted, sorted + sz, 1, compare_ascending) == &sorted[5]);   // 2
  assert(upper_bound(sorted, sorted + sz, 6, compare_ascending) == &sorted[10]);  // INT_MAX-42
  assert(upper_bound(sorted, sorted + sz, INT_MAX - 42, compare_ascending) == sorted + sz);

  // missing: between elements
  assert(upper_bound(sorted, sorted + sz, 0, compare_ascending) == &sorted[4]);  // 1
  assert(upper_bound(sorted, sorted + sz, -4, compare_ascending) == &sorted[3]); // -3

  // missing: below all / above all
  assert(upper_bound(sorted, sorted + sz, INT_MIN, compare_ascending) == &sorted[0]);
  assert(upper_bound(sorted, sorted + sz, INT_MAX, compare_ascending) == sorted + sz);

  // empty
  assert(upper_bound(sorted, sorted, 1, compare_ascending) == sorted);

  // descending comparator
  int desc[] = {10, 8, 6, 4, 2};
  assert(upper_bound(desc, desc + 5, 5, compare_descending) == &desc[3]); // 4: first greater than 5
  assert(upper_bound(desc, desc + 5, 6, compare_descending) == &desc[3]); // 4: first greater than 6
}

int main(void) {
  printf("Testing search...\n\n");

  RUN_TEST(test_linear_search);
  RUN_TEST(test_binary_search);
  RUN_TEST(test_lower_bound);
  RUN_TEST(test_upper_bound);

  printf("All tests passed for search\n");
  return 0;
}
