#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_LOAD_FACTOR 0.65

// A simple quadratic-probing hashmap in C--nothing fancy.

#include <stdint.h>

struct hashmap_entry_t {
  char *key;
  void *value;
};

struct hashmap_t {
  uint32_t size;
  uint32_t capacity;
  struct hashmap_entry_t *entries;
};

// initial_size must be power of 2
struct hashmap_t *hashmap_create(uint32_t initial_capacity);

void hashmap_put(struct hashmap_t *map, char *key, void *value);

void *hashmap_get(struct hashmap_t *map, char *key);

uint32_t hashmap_size(struct hashmap_t *map);

double hashmap_load_factor(struct hashmap_t *map);

void hashmap_destroy(struct hashmap_t *map);

#endif // HASHMAP_H
