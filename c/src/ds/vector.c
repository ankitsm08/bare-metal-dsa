#include "ds/vector.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 4

inline static size_t vector_next_capacity(size_t cap) {
  return cap < STARTING_CAPACITY ? STARTING_CAPACITY : cap * 2;
}

static void vector_reallocate(Vector *vec, size_t new_cap) {
  int *temp = realloc(vec->data, sizeof(int) * new_cap);
  if (!temp) {
    fprintf(stderr, "Fatal: Out of memory reallocating Vector buffer.\n");
    exit(EXIT_FAILURE);
  }

  vec->data = temp;
  vec->capacity = new_cap;
}

// Lifecycle
Vector *vector_create(size_t init_cap) {
  Vector *vec = malloc(sizeof(Vector));
  if (!vec) {
    fprintf(stderr, "Fatal: Out of memory allocating Vector struct.\n");
    exit(EXIT_FAILURE);
  }

  vec->size = 0;
  vec->capacity = init_cap == 0 ? STARTING_CAPACITY : init_cap;
  vec->data = malloc(sizeof(int) * vec->capacity);

  if (!vec->data) {
    free(vec);
    fprintf(stderr, "Fatal: Out of memory allocating Vector buffer.\n");
    exit(EXIT_FAILURE);
  }

  return vec;
}

void vector_destroy(Vector *vec) {
  if (vec) {
    free(vec->data);
    free(vec);
  }
}

// Element Access
int vector_get(const Vector *vec, size_t idx) {
  assert(vec != NULL);

  if (idx >= vec->size) {
    fprintf(stderr, "Index Error: Index %zu out-of-bounds.\n", idx);
    exit(EXIT_FAILURE);
  }

  return vec->data[idx];
}

void vector_set(Vector *vec, size_t idx, int val) {
  assert(vec != NULL);

  if (idx >= vec->size) {
    fprintf(stderr, "Index Error: Index %zu out-of-bounds.\n", idx);
    exit(EXIT_FAILURE);
  }

  vec->data[idx] = val;
}

int vector_front(const Vector *vec) {
  assert(vec != NULL);

  if (vec->size == 0) {
    fprintf(stderr, "Error: Cannot get first element of empty vector.\n");
    exit(EXIT_FAILURE);
  }

  return vec->data[0];
}

int vector_back(const Vector *vec) {
  assert(vec != NULL);

  if (vec->size == 0) {
    fprintf(stderr, "Error: Cannot get last element of empty vector.\n");
    exit(EXIT_FAILURE);
  }

  return vec->data[vec->size - 1];
}

int *vector_data(Vector *vec) {
  assert(vec != NULL);
  return vec->data;
}

// Iterators
int *vector_begin(Vector *vec) {
  assert(vec != NULL);
  return vec->data;
}

const int *vector_cbegin(const Vector *vec) {
  assert(vec != NULL);
  return vec->data;
}

int *vector_end(Vector *vec) {
  assert(vec != NULL);
  return vec->data + vec->size;
}

const int *vector_cend(const Vector *vec) {
  assert(vec != NULL);
  return vec->data + vec->size;
}

// Capacity
bool vector_empty(const Vector *vec) {
  assert(vec != NULL);
  return vec->size == 0;
}

size_t vector_size(const Vector *vec) {
  assert(vec != NULL);
  return vec->size;
}

void vector_reserve(Vector *vec, size_t new_cap) {
  assert(vec != NULL);

  if (vec->capacity >= new_cap)
    return;

  vector_reallocate(vec, new_cap);
}

size_t vector_capacity(const Vector *vec) {
  assert(vec != NULL);
  return vec->capacity;
}

void vector_shrink_to_fit(Vector *vec) {
  assert(vec != NULL);

  if (vec->size == 0) {
    free(vec->data);
    vec->data = NULL;
    vec->capacity = 0;
    return;
  }

  vector_reallocate(vec, vec->size);
}

// Modifiers
void vector_clear(Vector *vec) {
  assert(vec != NULL);
  vec->size = 0;
}

void vector_insert(Vector *vec, size_t idx, int val) {
  assert(vec != NULL);

  if (idx > vec->size) {
    fprintf(stderr, "Index Error: Cannot insert at out-of-bounds index %zu.\n", idx);
    exit(EXIT_FAILURE);
  }

  if (vec->size == vec->capacity)
    vector_reallocate(vec, vector_next_capacity(vec->capacity));

  // shift elements right to make room
  for (size_t i = vec->size; i > idx; i--) {
    vec->data[i] = vec->data[i - 1];
  }

  vec->data[idx] = val;
  vec->size++;
}

void vector_push_back(Vector *vec, int val) {
  assert(vec != NULL);

  if (vec->size == vec->capacity) {
    vector_reallocate(vec, vector_next_capacity(vec->capacity));
  }

  vec->data[vec->size++] = val;
}

void vector_pop_back(Vector *vec) {
  assert(vec != NULL);

  if (vec->size == 0) {
    fprintf(stderr, "Fatal: Cannot pop from an empty vector.\n");
    exit(EXIT_FAILURE);
  }

  vec->size--;
}

void vector_erase(Vector *vec, size_t idx) {
  assert(vec != NULL);

  if (vec->size <= idx) {
    fprintf(stderr, "Index Error: Index %zu out-of-bounds for vector.\n", idx);
    exit(EXIT_FAILURE);
  }

  // shift elements left to close the gap
  for (size_t i = idx; i < vec->size - 1; i++) {
    vec->data[i] = vec->data[i + 1];
  }

  vec->size--;
}

void vector_resize(Vector *vec, size_t new_size) { vector_resize_with_value(vec, new_size, 0); }

void vector_resize_with_value(Vector *vec, size_t new_size, int val) {
  assert(vec != NULL);

  if (vec->size < new_size) {
    if (vec->capacity < new_size)
      vector_reallocate(vec, new_size);

    // initialize new slots to val
    for (size_t i = vec->size; i < new_size; i++) {
      vec->data[i] = val;
    }
  }

  vec->size = new_size;
}

void vector_swap(Vector *vec1, Vector *vec2) {
  assert(vec1 != NULL && vec2 != NULL);

  int *temp_data = vec1->data;
  vec1->data = vec2->data;
  vec2->data = temp_data;

  size_t temp_size = vec1->size;
  vec1->size = vec2->size;
  vec2->size = temp_size;

  size_t temp_capacity = vec1->capacity;
  vec1->capacity = vec2->capacity;
  vec2->capacity = temp_capacity;
}
