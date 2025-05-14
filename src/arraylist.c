#include "arraylist.h"
#include <stdlib.h>

struct arraylist_t *arraylist_create(uint32_t initial_size) {
  struct arraylist_t *list =
      (struct arraylist_t *)malloc(sizeof(struct arraylist_t));

  list->data = (void *)malloc(sizeof(void *) * initial_size);
  list->size = 0;

  return list;
}

void arraylist_add(struct arraylist_t *list, void *item) {}

void arraylist_add_at_index(struct arraylist_t *list, uint32_t index,
                            void *item) {}

void *arraylist_get(struct arraylist_t *list, uint32_t index) {}

void arraylist_set(struct arraylist_t *list, uint32_t index, void *new_value) {}

void *arraylist_remove(struct arraylist_t *list, uint32_t index) {}

uint32_t arraylist_size(struct arraylist_t *list) {}

int arraylist_contains(struct arraylist_t *list, void *item) {}

int arraylist_index_of(struct arraylist_t *list, void *item) {}

int arraylist_is_empty(struct arraylist_t *list) { return list->size == 0; }
