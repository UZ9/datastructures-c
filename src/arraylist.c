#include "arraylist.h"
#include <stdio.h>
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
  arraylist_add_at_index(list, list->size, item);
}

void arraylist_add_at_index(struct arraylist_t *list, uint32_t index,
                            void *item) {

  // check if at capacity
  if (list->size + 1 == list->capacity) {
    // resize
    uint32_t new_capacity = list->capacity * 2;

    list->capacity = new_capacity;

    list->data = realloc(list->data, new_capacity * sizeof(void *));
  }

  // add to back
  if (index == list->size) {
    list->data[list->size++] = item;
  } else {
    // shuffle everything over

    for (int i = list->size + 1; i > index; i--) {
      printf("%d\n", i);
      list->data[i] = list->data[i - 1];
    }

    list->data[index] = item;

    list->size++;
  }
}

void *arraylist_get(struct arraylist_t *list, uint32_t index) {
  if (index >= list->size || index < 0) {
    return NULL;
  }

  return list->data[index];
}

void *arraylist_set(struct arraylist_t *list, uint32_t index, void *new_value) {
  if (index >= list->size || index < 0) {
    return NULL;
  }

  void* temp = list->data[index];

  list->data[index] = new_value;

  return temp;
}

void *arraylist_remove(struct arraylist_t *list, uint32_t index) {
  // TODO: edge cases

  void *removed = list->data[index];

  for (int i = index + 1; i <= list->size; i++) {
    list->data[i - 1] = list->data[i];
  }

  list->data[list->size - 1] = NULL;

  list->size--;

  return removed;
}

uint32_t arraylist_size(struct arraylist_t *list) { return list->size; }

int arraylist_contains(struct arraylist_t *list, void *item) {
  return arraylist_index_of(list, item) != -1;
}

int arraylist_index_of(struct arraylist_t *list, void *item) {

  // assuming strict comparison
  for (int i = 0; i < list->size; i++) {
    if (list->data[i] == item) {
      return i;
    }
  }

  return -1;
}

int arraylist_is_empty(struct arraylist_t *list) { return list->size == 0; }

void arraylist_destroy(struct arraylist_t *list) {
  // due to the void* potentially containing other pointers, we do NOT handle cleaning it up here.
  free(list->data);
  free(list);
}
