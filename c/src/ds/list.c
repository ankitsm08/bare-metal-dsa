#include "ds/list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static inline ListNode *get_node(const List *list, size_t idx) {
  assert(list != NULL);

  ListNode *node = list->head;
  size_t i = 0;

  while (node && i < idx) {
    node = node->next;
    i++;
  }

  if (node == NULL) {
    fprintf(stderr, "Index Error: Index %zu out-of-bounds for list.\n", idx);
    exit(EXIT_FAILURE);
  }

  return node;
}

// Lifecycle
List *list_create(void) {
  List *list = malloc(sizeof(List));
  if (!list) {
    fprintf(stderr, "Fatal: Out of memory allocating List struct.\n");
    exit(EXIT_FAILURE);
  }

  list->head = list->tail = NULL;
  return list;
}

void list_destroy(List *list) {
  if (!list)
    return;

  ListNode *node = list->head;

  while (node != NULL) {
    ListNode *next = node->next;
    free(node);
    node = next;
  }

  free(list);
}

// Element Access
int list_get(const List *list, size_t idx) { return get_node(list, idx)->val; }
void list_set(List *list, size_t idx, int val) { get_node(list, idx)->val = val; }

// Size
bool list_empty(const List *list) {
  assert(list != NULL);
  return list->head == NULL;
}

size_t list_size(const List *list) {
  assert(list != NULL);
  size_t sz = 0;

  ListNode *node = list->head;
  while (node != NULL) {
    sz++;
    node = node->next;
  }

  return sz;
}
