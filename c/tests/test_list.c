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

void test_insert(void) {
  List *list = list_create();

  // insert into an empty list is a push
  list_insert(list, 0, 42);
  const int single[] = {42};
  assert_contents(list, single, 1);

  // insert at head
  list_insert(list, 0, 1);
  const int prepended[] = {1, 42};
  assert_contents(list, prepended, 2);

  // insert at tail (idx == size)
  list_insert(list, 2, 99);
  const int appended[] = {1, 42, 99};
  assert_contents(list, appended, 3);

  // insert in the middle, both neighbours relink correctly
  list_insert(list, 1, 7);
  const int middle[] = {1, 7, 42, 99};
  assert_contents(list, middle, 4);

  // walking back from the tail sees the same order
  ListNode *node = list->tail;
  assert(node->val == 99);
  node = node->prev;
  assert(node->val == 42);
  node = node->prev;
  assert(node->val == 7);
  assert(node->prev->val == 1);
  assert(node->prev->prev == NULL);

  list_destroy(list);
}

void test_erase(void) {
  List *list = list_create();

  for (int i = 1; i <= 5; i++)
    list_push_back(list, i);

  // erase head, tail pointer must be untouched
  list_erase(list, 0);
  const int no_head[] = {2, 3, 4, 5};
  assert_contents(list, no_head, 4);

  // erase tail, head pointer must be untouched
  list_erase(list, 3);
  const int no_tail[] = {2, 3, 4};
  assert_contents(list, no_tail, 3);

  // erase the only interior node
  list_erase(list, 1);
  const int gap[] = {2, 4};
  assert_contents(list, gap, 2);

  // erase down to a single node, then to empty
  list_erase(list, 0);
  const int single[] = {4};
  assert_contents(list, single, 1);
  assert(list->head == list->tail);

  list_erase(list, 0);
  assert(list_empty(list) == true);
  assert(list->head == NULL);
  assert(list->tail == NULL);

  // list stays usable after draining
  list_push_back(list, 100);
  const int reused[] = {100};
  assert_contents(list, reused, 1);

  list_destroy(list);
}

void test_clear_and_reuse(void) {
  List *list = list_create();

  for (int i = 0; i < 50; i++)
    list_push_back(list, i);

  assert(list_size(list) == 50);

  // clear frees every node but keeps List alive
  list_clear(list);
  assert(list_empty(list) == true);
  assert(list_size(list) == 0);
  assert(list->head == NULL);
  assert(list->tail == NULL);

  // clearing an already empty list is a no-op
  list_clear(list);
  assert(list_empty(list) == true);

  // both ends still work after a clear
  list_push_back(list, 1);
  list_push_front(list, 0);
  const int two[] = {0, 1};
  assert_contents(list, two, 2);

  list_destroy(list);
}

void test_swap(void) {
  List *a = list_create();
  List *b = list_create();

  for (int i = 1; i <= 3; i++)
    list_push_back(a, i);
  for (int i = 7; i <= 12; i++)
    list_push_back(b, i);

  list_swap(a, b);

  const int a_after[] = {7, 8, 9, 10, 11, 12};
  const int b_after[] = {1, 2, 3};
  assert_contents(a, a_after, 6);
  assert_contents(b, b_after, 3);

  // swap an empty list with a populated one
  List *empty = list_create();
  list_swap(a, empty);

  assert(list_empty(a) == true);
  assert(a->head == NULL && a->tail == NULL);
  const int moved[] = {7, 8, 9, 10, 11, 12};
  assert_contents(empty, moved, 6);

  // swapping a list with itself must be harmless
  list_swap(empty, empty);
  assert_contents(empty, moved, 6);

  list_destroy(a);
  list_destroy(b);
  list_destroy(empty);
}

void test_large_loop(void) {
  List *list = list_create();

  for (int i = 0; i < 200; i++)
    list_push_back(list, i);

  assert(list_size(list) == 200);
  assert(list_front(list) == 0);
  assert(list_back(list) == 199);
  assert_bidirectional(list);

  for (int i = 0; i < 50; i++)
    list_push_front(list, -1);
  // index 0 = last pushed value

  assert(list_size(list) == 250);
  assert(list_front(list) == -1);
  assert(list_get(list, 50) == 0);
  assert(list_back(list) == 199);

  // drain fully from the front
  while (!list_empty(list))
    list_pop_front(list);

  assert(list->head == NULL);
  assert(list->tail == NULL);

  list_destroy(list);
}

int main(void) {
  printf("Testing list...\n\n");

  RUN_TEST(test_lifecycle);
  RUN_TEST(test_push_pop_ends);
  RUN_TEST(test_element_access);
  RUN_TEST(test_insert);
  RUN_TEST(test_erase);
  RUN_TEST(test_clear_and_reuse);
  RUN_TEST(test_swap);
  RUN_TEST(test_large_loop);

  printf("All tests passed for list\n");
  return 0;
}
