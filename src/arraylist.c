#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>

#define LOG_ERROR(msg, ...) fprintf(stderr, msg "\n", ##__VA_ARGS__)

struct arraylist_t *arraylist_create(uint32_t initial_capacity) {
  struct arraylist_t *list =
      (struct arraylist_t *)calloc(1, sizeof(struct arraylist_t));

  list->data = (void **)calloc(initial_capacity, sizeof(void *));
  list->size = 0;

  if (initial_capacity == 0) {
    LOG_ERROR("arrayli_create: cannot have initial capacity 0, must be > 0");
    free(list->data);
    free(list);
    return NULL;
  }

  list->capacity = initial_capacity;

  return list;
}

void arraylist_add(struct arraylist_t *list, void *item) {
  if (list == NULL) {
    LOG_ERROR("arraylist_add: null list provided");
    return;
  }

  arraylist_add_at_index(list, list->size, item);
}

void arraylist_add_at_index(struct arraylist_t *list, uint32_t index,
                            void *item) {
  if (list == NULL) {
    LOG_ERROR("arraylist_add_at_index: null list provided");
    return;
  }

  if (index > list->size) {
    LOG_ERROR(
        "arraylist_add_at_index: index %d out of bounds for list of size %d",
        index, list->size);
    return;
  }

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
    for (int i = list->size; i > index; i--) {
      list->data[i] = list->data[i - 1];
    }

    list->data[index] = item;

    list->size++;
  }
}

void *arraylist_get(struct arraylist_t *list, uint32_t index) {
  if (list == NULL) {
    LOG_ERROR("arraylist_get: null list provided");
    return NULL;
  }

  if (index >= list->size) {
    LOG_ERROR("arraylist_get: index %d out of bounds for list of size %d",
              index, list->size);
    return NULL;
  }

  return list->data[index];
}

void *arraylist_set(struct arraylist_t *list, uint32_t index, void *new_value) {
  if (list == NULL) {
    LOG_ERROR("arraylist_set: null list provided");
    return NULL;
  }

  if (index >= list->size) {
    LOG_ERROR("arraylist_get: index %d out of bounds for list of size %d",
              index, list->size);
    return NULL;
  }

  void *temp = list->data[index];

  list->data[index] = new_value;

  return temp;
}

void *arraylist_remove(struct arraylist_t *list, uint32_t index) {
  if (list == NULL) {
    LOG_ERROR("arraylist_remove: null list provided");
    return NULL;
  }
  // TODO: edge cases

  void *removed = list->data[index];

  for (int i = index + 1; i < list->size; i++) {
    list->data[i - 1] = list->data[i];
  }

  list->data[list->size - 1] = NULL;

  list->size--;

  return removed;
}

uint32_t arraylist_size(struct arraylist_t *list) {
  if (list == NULL) {
    LOG_ERROR("arraylist_size: null list provided");
    return -1;
  }

  return list->size;
}

int arraylist_contains(struct arraylist_t *list, void *item) {
  if (list == NULL) {
    LOG_ERROR("arraylist_contains: null list provided");
    return -1;
  }

  return arraylist_index_of(list, item) != -1;
}

int arraylist_index_of(struct arraylist_t *list, void *item) {
  if (list == NULL) {
    LOG_ERROR("arraylist_index_of: null list provided");
    return -1;
  }

  // assuming strict comparison
  for (int i = 0; i < list->size; i++) {
    if (list->data[i] == item) {
      return i;
    }
  }

  return -1;
}

int arraylist_is_empty(struct arraylist_t *list) {

  if (list == NULL) {
    LOG_ERROR("arraylist_is_empty: null list provided");
    return -1;
  }

  return list->size == 0;
}

void arraylist_destroy(struct arraylist_t *list) {
  if (list == NULL) {
    LOG_ERROR("arraylist_destroy: null list provided");
    return;
  }

  // due to the void* potentially containing other pointers, we do NOT handle
  // cleaning it up here.
  free(list->data);
  free(list);
}
