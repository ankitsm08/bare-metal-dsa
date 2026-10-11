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

static void assert_bidirectional(const List *list) {
  if (list->head == NULL) {
    assert(list->tail == NULL);
    return;
  }

  // open ends
  assert(list->head->prev == NULL);
  assert(list->tail->next == NULL);

  // prev/next must agree with forward walk
  ListNode *prev = NULL;
  for (ListNode *node = list->head; node != NULL; node = node->next) {
    assert(node->prev == prev);
    if (prev != NULL)
      assert(prev->next == node);
    prev = node;
  }

  assert(prev == list->tail);
}

static void assert_contents(const List *list, const int *expected, size_t n) {
  assert(list_size(list) == n);

  for (size_t i = 0; i < n; i++)
    assert(list_get(list, i) == expected[i]);

  if (n > 0) {
    assert(list_front(list) == expected[0]);
    assert(list_back(list) == expected[n - 1]);
  }

  assert_bidirectional(list);
}

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

void test_push_pop_ends(void) {
  List *list = list_create();

  // empty -> one: head and tail = same node
  list_push_back(list, 10);
  assert(list_size(list) == 1);
  assert(list->head == list->tail);
  assert_bidirectional(list);

  // grow to three from both ends
  list_push_front(list, 5);
  list_push_back(list, 20);
  const int three[] = {5, 10, 20};
  assert_contents(list, three, 3);

  // shrink back down from both ends
  list_pop_front(list);
  list_pop_back(list);
  const int one[] = {10};
  assert_contents(list, one, 1);
  assert(list->head == list->tail);

  // last element removal leaves a fully empty, reusable list
  list_pop_front(list);
  assert(list_empty(list) == true);
  assert(list->head == NULL);
  assert(list->tail == NULL);

  list_push_back(list, 7);
  const int reused[] = {7};
  assert_contents(list, reused, 1);

  list_destroy(list);
}

void test_element_access(void) {
  List *list = list_create();

  for (int i = 0; i < 4; i++)
    list_push_back(list, i + 1);

  assert(list_get(list, 0) == 1);
  assert(list_get(list, 3) == 4);
  assert(list_front(list) == 1);
  assert(list_back(list) == 4);

  // set only the target, neighbours stay put
  list_set(list, 1, 99);
  assert(list_get(list, 1) == 99);
  assert(list_get(list, 0) == 1);
  assert(list_get(list, 2) == 3);
  assert_bidirectional(list);

  // negative and extreme values
  list_set(list, 0, INT_MIN);
  assert(list_get(list, 0) == INT_MIN);
  list_set(list, 0, INT_MAX);
  assert(list_get(list, 0) == INT_MAX);

  list_destroy(list);
}
int main(void) {
  printf("Testing list...\n\n");

  RUN_TEST(test_lifecycle);
  RUN_TEST(test_push_pop_ends);
  RUN_TEST(test_element_access);

  printf("All tests passed for list\n");
  return 0;
}
