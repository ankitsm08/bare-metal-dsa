#include "__TYPE__/__NAME__.h"
#include <stdio.h>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    printf("[ RUNNING ] %s...\n", #test_func);                                                     \
    test_func();                                                                                   \
    printf("[ PASSED  ] %s\n\n", #test_func);                                                      \
  } while (0)

int main(void) {
  printf("Testing __NAME__...\n\n");

  printf("All tests passed for __NAME__\n");
  return 0;
}
