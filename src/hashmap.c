#include "hashmap.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// basic, unsecure hash algorithm, would not use in production
// as it's susceptible to collision attacks
// hash function from https://benhoyt.com/writings/hash-table-in-c/
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

#define LOG_ERROR(msg, ...) fprintf(stderr, msg "\n", ##__VA_ARGS__)

static uint64_t hash_key(const char *key) {
  uint64_t hash = FNV_OFFSET;
  for (const char *p = key; *p; p++) {
    hash ^= (uint64_t)(unsigned char)(*p);
    hash *= FNV_PRIME;
  }
  return hash;
}

struct hashmap_t *hashmap_create(uint32_t initial_capacity) {
  struct hashmap_t *map =
      (struct hashmap_t *)calloc(1, sizeof(struct hashmap_t));

  map->size = 0;
  map->capacity = initial_capacity;
  map->entries = (struct hashmap_entry_t *)calloc(
      initial_capacity, sizeof(struct hashmap_entry_t));

  return map;
}

// add only hashmap; using this for constant lookup table
void hashmap_put(struct hashmap_t *map, char *key, void *value) {
  if ((map->size + 1) / (double)map->capacity > HASHMAP_LOAD_FACTOR) {
    // resize: there's not much sense in reallocing as we have to rehash each
    // key
    uint64_t new_capacity = map->capacity * 2;

    char *test1 = (char *)"test1";
    char *test2 = (char *)"test2";

    struct hashmap_entry_t *new_entries =
        calloc(new_capacity, sizeof(struct hashmap_entry_t));

    if (new_entries == NULL) {
      LOG_ERROR("hashmap_put: failed to resize hashmap");
      return;
    }

    // search through all previous keys, and rehash
    for (uint32_t i = 0; i < map->capacity; i++) {
      struct hashmap_entry_t *entry = &map->entries[i];

      if (entry->key != NULL) {
        uint32_t initial_index = hash_key(entry->key) & (new_capacity - 1);

        uint32_t index = initial_index;

        uint32_t probe_count = 1;

        while (new_entries[index].key != NULL) {
          // quadratic probing: 0, 1, 2, 4, 9, etc.
          // i = i_0 + probe_count^2
          index =
              initial_index + (probe_count * probe_count) & (new_capacity - 1);
          probe_count++;
        }

        new_entries[index].key = entry->key;
        new_entries[index].value = entry->value;
      }
    }

    // free previous entry array
    free(map->entries);

    map->capacity = new_capacity;
    map->entries = new_entries;
  }

  // bitmask trick: if capacity guaranteed power of 2,
  // we can just AND the other bits away
  // e.g. 64 = 1000000, we care about those zeroes
  // 64 - 1 = 63 = 0111111, use this as bitmask
  uint32_t initial_index = hash_key(key) & (map->capacity - 1);

  uint32_t index = initial_index;

  uint32_t probe_count = 1;

  while (map->entries[index].key != NULL) {
    // quadratic probing: 0, 1, 2, 4, 9, etc.
    // i = i_0 + probe_count^2
    index = initial_index + (probe_count * probe_count) & (map->capacity - 1);
    probe_count++;
  }

  // place new element
  map->entries[index].key = key;
  map->entries[index].value = value;

  map->size++;
}

void *hashmap_get(struct hashmap_t *map, char *key) {

  uint32_t initial_index = hash_key(key) & (map->capacity - 1);

  uint32_t index = initial_index;

  uint32_t probe_count = 1;

  // TODO: infinite loop here unless there's an exit condiiton on high load
  // factors
  while (map->entries[index].key != NULL &&
         strcmp(map->entries[index].key, key) != 0) {
    // keys are not equal, but we can keep going
    index = initial_index + (probe_count * probe_count) & (map->capacity - 1);
    probe_count++;
  }

  if (map->entries[index].key == NULL) {
    // didn't find key
    return NULL;
  } else {
    return map->entries[index].value;
  }
}

uint32_t hashmap_size(struct hashmap_t *map) { return map->size; }

double hashmap_load_factor(struct hashmap_t *map) {
  return map->size / (double)map->capacity;
}

void hashmap_destroy(struct hashmap_t *map) {
  // user is responsible for freeing items themselves
  free(map->entries);
  free(map);
}
