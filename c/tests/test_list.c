#include "ds/list.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    printf("[ RUNNING ] %s...\n", #test_func);                                                     \
    test_func();                                                                                   \
    printf("[ PASSED  ] %s\n\n", #test_func);                                                      \
  } while (0)

void test_lifecycle(void) {
  List *list = list_create();

  assert(list != NULL);
  // initial empty list check
  assert(list_empty(list) == true);
  assert(list_size(list) == 0);
  assert(list->head == NULL);
  assert(list->tail == NULL);

  list_destroy(list);
  // safe NULL cleanup
  list_destroy(NULL);
}

int main(void) {
  printf("Testing list...\n\n");

  RUN_TEST(test_lifecycle);

  printf("All tests passed for list\n");
  return 0;
}
