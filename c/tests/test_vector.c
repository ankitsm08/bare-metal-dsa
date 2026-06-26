#include "ds/vector.h"
#include <assert.h>
#include <stdio.h>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    printf("[ RUNNING ] %s...\n", #test_func);                                                     \
    test_func();                                                                                   \
    printf("[ PASSED  ] %s\n\n", #test_func);                                                      \
  } while (0)

void test_lifecycle(void) {
  Vector *vec = vector_create(0);

  assert(vec != NULL);
  assert(vector_size(vec) == 0);
  // starting capacity
  assert(vector_capacity(vec) == 4);
  assert(vector_empty(vec) == true);

  vector_destroy(vec);
  // safe NULL cleanup
  vector_destroy(NULL);
}

void test_push_pop_growth(void) {
  Vector *vec = vector_create(0);

  assert(vector_size(vec) == 0);
  assert(vector_capacity(vec) == 4);

  vector_push_back(vec, 65);
  vector_push_back(vec, 110);
  vector_push_back(vec, 107);
  assert(vector_size(vec) == 3);
  assert(vector_capacity(vec) == 4);

  vector_push_back(vec, 4);
  assert(vector_size(vec) == 4);
  assert(vector_capacity(vec) == 4);

  vector_push_back(vec, 5);
  assert(vector_size(vec) == 5);
  assert(vector_capacity(vec) == 8);

  for (int i = 0; i < 100; i++) {
    vector_push_back(vec, i);
  }

  assert(vector_size(vec) == 105);
  assert(vector_capacity(vec) == 128);

  for (int i = 0; i < 100; i++) {
    vector_pop_back(vec);
  }

  assert(vector_size(vec) == 5);
  // explicitly verify no shrinkage
  assert(vector_capacity(vec) == 128);

  for (int i = 0; i < 5; i++) {
    vector_pop_back(vec);
  }

  assert(vector_size(vec) == 0);
  assert(vector_capacity(vec) == 128);

  vector_destroy(vec);
}

void test_element_access(void) {
  Vector *vec = vector_create(0);

  vector_push_back(vec, 1); // index 0
  assert(vector_get(vec, 0) == 1);
  vector_push_back(vec, 2); // index 1
  vector_push_back(vec, 1); // index 2
  vector_push_back(vec, 3); // index 3
  assert(vector_get(vec, 3) == 3);

  vector_set(vec, 3, 5);
  assert(vector_get(vec, 3) == 5);

  assert(vector_front(vec) == 1);
  assert(vector_back(vec) == 5);

  vector_pop_back(vec); // remove index 3
  assert(vector_back(vec) == 1);

  int *data = vector_data(vec);
  assert(data[0] == 1);
  assert(data[1] == 2);
  assert(data[vector_size(vec) - 1] == 1);

  vector_destroy(vec);
}

void test_insert_and_erase(void) {
  Vector *vec = vector_create(0);

  vector_push_back(vec, 42);
  vector_insert(vec, 0, 24);
  assert(vector_get(vec, 0) == 24);
  assert(vector_get(vec, 1) == 42);
  assert(vector_size(vec) == 2);
  assert(vector_capacity(vec) == 4);

  vector_insert(vec, 1, 1);
  assert(vector_get(vec, 1) == 1);
  vector_erase(vec, 1);
  assert(vector_get(vec, 1) == 42);

  vector_destroy(vec);
}

void test_reserve_and_shrink(void) {
  Vector *vec = vector_create(0);

  vector_reserve(vec, 100);
  assert(vector_capacity(vec) == 100);
  vector_shrink_to_fit(vec);
  assert(vector_capacity(vec) == 0);

  vector_push_back(vec, 1);
  assert(vector_size(vec) == 1);
  assert(vector_capacity(vec) == 4);

  for (int i = 0; i < 98; i++) {
    vector_push_back(vec, i);
  }

  assert(vector_capacity(vec) == 128);
  vector_shrink_to_fit(vec);
  assert(vector_capacity(vec) == 99);

  vector_push_back(vec, 123);
  assert(vector_capacity(vec) == 198);
  vector_shrink_to_fit(vec);
  assert(vector_capacity(vec) == 100);

  vector_destroy(vec);
}

void test_resize_down_loop(void) {
  Vector *vec = vector_create(0);

  assert(vector_size(vec) == 0);
  assert(vector_capacity(vec) == 4);

  vector_resize(vec, 25);
  assert(vector_size(vec) == 25);
  assert(vector_capacity(vec) == 25);

  vector_push_back(vec, 2147483647);
  assert(vector_size(vec) == 26);
  assert(vector_capacity(vec) == 50);

  vector_resize_with_value(vec, 26, -1);
  assert(vector_back(vec) == 2147483647);
  vector_pop_back(vec);
  assert(vector_back(vec) == 0);
  assert(vector_capacity(vec) == 50);
  assert(vector_size(vec) == 25);

  vector_resize_with_value(vec, 30, -1);
  assert(vector_back(vec) == -1);
  assert(vector_capacity(vec) == 50);
  assert(vector_size(vec) == 30);

  vector_destroy(vec);
}

void test_swap_and_clear(void) {
  Vector *vec1 = vector_create(0);
  Vector *vec2 = vector_create(0);

  vector_push_back(vec1, 1);
  vector_push_back(vec1, 2);
  vector_push_back(vec1, 3);
  vector_push_back(vec2, 1);
  vector_push_back(vec2, 2);
  vector_push_back(vec2, 3);
  vector_push_back(vec2, 4);
  vector_push_back(vec2, 5);
  vector_push_back(vec2, 6);
  assert(vector_size(vec1) == 3);
  assert(vector_size(vec2) == 6);
  assert(vector_capacity(vec1) == 4);
  assert(vector_capacity(vec2) == 8);

  vector_swap(vec1, vec2);
  assert(vector_size(vec1) == 6);
  assert(vector_size(vec2) == 3);
  assert(vector_capacity(vec1) == 8);
  assert(vector_capacity(vec2) == 4);

  assert(vector_get(vec1, 0) == 1);
  assert(vector_get(vec1, 4) == 5);
  assert(vector_get(vec2, 0) == 1);
  assert(vector_get(vec2, 2) == 3);

  vector_clear(vec1);
  vector_clear(vec2);
  assert(vector_size(vec1) == 0);
  assert(vector_capacity(vec1) == 8);
  assert(vector_size(vec2) == 0);
  assert(vector_capacity(vec2) == 4);

  vector_destroy(vec1);
  vector_destroy(vec2);
}

void test_iterators(void) {
  Vector *vec = vector_create(0);

  for (int i = 0; i < 42; i++) {
    vector_push_back(vec, i);
  }

  for (int *it = vector_begin(vec); it != vector_end(vec); ++it) {
    assert(++(*it) == vector_get(vec, it - vector_begin(vec)));
  }

  for (const int *it = vector_cbegin(vec); it != vector_cend(vec); it++) {
    assert(*it == vector_get(vec, it - vector_cbegin(vec)));
  }

  vector_destroy(vec);
}

int main(void) {
  printf("Testing vector...\n\n");

  RUN_TEST(test_lifecycle);
  RUN_TEST(test_push_pop_growth);
  RUN_TEST(test_element_access);
  RUN_TEST(test_insert_and_erase);
  RUN_TEST(test_reserve_and_shrink);
  RUN_TEST(test_resize_down_loop);
  RUN_TEST(test_swap_and_clear);
  RUN_TEST(test_iterators);

  printf("All tests passed for vector\n");
  return 0;
}
