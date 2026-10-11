#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct ListNode {
  struct ListNode *next; // Pointer to the next element
  struct ListNode *prev; // Pointer to the previous element
  int val;               // Value of the node
} ListNode;

typedef struct {
  struct ListNode *head; // Pointer to the first element
  struct ListNode *tail; // Pointer to the last element
} List;

// Lifecycle
List *list_create(void);
void list_destroy(List *list);

// Element Access
int list_get(const List *list, size_t idx);
void list_set(List *list, size_t idx, int val);
int list_front(const List *list);
int list_back(const List *list);

// Size
bool list_empty(const List *list);
size_t list_size(const List *list);

// Modifiers
void list_push_front(List *list, int val);
void list_pop_front(List *list);
void list_push_back(List *list, int val);
void list_pop_back(List *list);
