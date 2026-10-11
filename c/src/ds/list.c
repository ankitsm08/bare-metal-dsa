#include "ds/list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Helpers
static inline ListNode *make_node(int val) {
  ListNode *node = malloc(sizeof(ListNode));
  if (!node) {
    fprintf(stderr, "Fatal: Out of memory allocating List node.\n");
    exit(EXIT_FAILURE);
  }

  node->val = val;
  node->next = node->prev = NULL;
  return node;
}

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

int list_front(const List *list) {
  assert(list != NULL);

  if (!list->head) {
    fprintf(stderr, "Index Error: List is empty.\n");
    exit(EXIT_FAILURE);
  }

  return list->head->val;
}
int list_back(const List *list) {
  assert(list != NULL);

  if (!list->tail) {
    fprintf(stderr, "Index Error: List is empty.\n");
    exit(EXIT_FAILURE);
  }

  return list->tail->val;
}

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

// Modifiers

void list_push_front(List *list, int val) {
  assert(list != NULL);
  ListNode *head = list->head;
  ListNode *new_head = make_node(val);

  if (head) {
    new_head->next = head;
    head->prev = new_head;
    list->head = head->prev = new_head;
  } else {
    list->head = list->tail = new_head;
  }
}

void list_push_back(List *list, int val) {
  assert(list != NULL);
  ListNode *tail = list->tail;
  ListNode *new_tail = make_node(val);

  if (tail) {
    new_tail->prev = tail;
    tail->next = new_tail;
    list->tail = tail->next = new_tail;
  } else {
    list->head = list->tail = new_tail;
  }
}

void list_pop_front(List *list) {
  assert(list != NULL);
  ListNode *head = list->head;
  assert(head != NULL);

  if (head->next) {
    list->head = head->next;
    head->next->prev = NULL;
  } else {
    list->head = list->tail = NULL;
  }
  free(head);
}

void list_pop_back(List *list) {
  assert(list != NULL);
  ListNode *tail = list->tail;
  assert(tail != NULL);

  if (tail->prev) {
    list->tail = tail->prev;
    tail->prev->next = NULL;
  } else {
    list->head = list->tail = NULL;
  }
  free(tail);
}
