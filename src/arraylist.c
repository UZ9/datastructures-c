#include "arraylist.h"
#include <stdlib.h>

struct arraylist_t *arraylist_create(uint32_t initial_capacity) {
  struct arraylist_t *list =
      (struct arraylist_t *)malloc(sizeof(struct arraylist_t));

  list->data = (void **)calloc(initial_capacity, sizeof(void *));
  list->size = 0;

  list->capacity = initial_capacity;

  return list;
}

void arraylist_add(struct arraylist_t *list, void *item) {
  // check if at capacity
  if (list->size + 1 == list->capacity) {
    // resize
    uint32_t new_capacity = list->capacity * 2;

    list->capacity = new_capacity;

    list->data = realloc(list->data, new_capacity * sizeof(void *));
  }

  list->data[list->size++] = item;
}

void arraylist_add_at_index(struct arraylist_t *list, uint32_t index,
                            void *item) {}

void *arraylist_get(struct arraylist_t *list, uint32_t index) {}

void arraylist_set(struct arraylist_t *list, uint32_t index, void *new_value) {}

void *arraylist_remove(struct arraylist_t *list, uint32_t index) {}

uint32_t arraylist_size(struct arraylist_t *list) { return list->size; }

int arraylist_contains(struct arraylist_t *list, void *item) {}

int arraylist_index_of(struct arraylist_t *list, void *item) {}

int arraylist_is_empty(struct arraylist_t *list) { return list->size == 0; }
