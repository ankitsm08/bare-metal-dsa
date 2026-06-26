#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *data;       // Array of integers
  size_t capacity; // Allocated memory slots
  size_t size;     // Current number of stored elements
} Vector;

// Lifecycle
Vector *vector_create(size_t init_cap);
void vector_destroy(Vector *vec);

// Element Access
int vector_get(const Vector *vec, size_t idx);
void vector_set(Vector *vec, size_t idx, int val);
int vector_front(const Vector *vec);
int vector_back(const Vector *vec);
int *vector_data(Vector *vec);

// Iterators
int *vector_begin(Vector *vec);
const int *vector_cbegin(const Vector *vec);
int *vector_end(Vector *vec);
const int *vector_cend(const Vector *vec);

// Capacity
bool vector_empty(const Vector *vec);
size_t vector_size(const Vector *vec);
void vector_reserve(Vector *vec, size_t new_cap);
size_t vector_capacity(const Vector *vec);
void vector_shrink_to_fit(Vector *vec);

// Modifiers
void vector_clear(Vector *vec);
void vector_insert(Vector *vec, size_t idx, int val);
void vector_push_back(Vector *vec, int val);
void vector_pop_back(Vector *vec);
void vector_erase(Vector *vec, size_t pos);
void vector_resize(Vector *vec, size_t new_size);
void vector_resize_with_value(Vector *vec, size_t new_size, int val);
void vector_swap(Vector *vec1, Vector *vec2);
