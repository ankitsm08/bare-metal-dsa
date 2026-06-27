#include "utils/compare.h"
#include "utils/math.h"
#include <assert.h>
#include <stdio.h>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    printf("[ RUNNING ] %s...\n", #test_func);                                                     \
    test_func();                                                                                   \
    printf("[ PASSED  ] %s\n\n", #test_func);                                                      \
  } while (0)

void test_comparators(void) {
  assert(compare_ascending(10, 20) < 0);
  assert(compare_ascending(20, 10) > 0);
  assert(compare_ascending(10, 10) == 0);

  assert(compare_descending(10, 20) > 0);
  assert(compare_descending(20, 10) < 0);
  assert(compare_descending(10, 10) == 0);
}

void test_math_utilities(void) {
  assert(math_min(10, 20) == 10);
  assert(math_max(10, 20) == 20);

  assert(math_clamp(5, 0, 10) == 5);   // in bounds -> unchanged
  assert(math_clamp(-5, 0, 10) == 0);  // below bounds -> min
  assert(math_clamp(15, 0, 10) == 10); // above bounds -> max
}

int main(void) {
  printf("Testing utils...\n\n");

  RUN_TEST(test_comparators);
  RUN_TEST(test_math_utilities);

  printf("All utility tests passed!\n");
  return 0;
}
