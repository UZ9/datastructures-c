#include <gtest/gtest.h>

extern "C" {
#include "hashmap.h"
}

struct DummyNode {
  int val;
};

static void make_items(void **arr, int count) {
  for (int i = 0; i < count; i++) {
    DummyNode *node = (DummyNode *)malloc(sizeof(DummyNode));

    node->val = i;

    arr[i] = node;
  }
}

static void clean_items(void **arr, int count) {
  for (int i = 0; i < count; i++) {
    // no heap allocatd items in dummy node, so just free
    free(arr[i]);
    arr[i] = NULL;
  }
}

static void print_item(void *item) { printf("%d ", ((DummyNode *)item)->val); }

static bool node_is_value(void *node, int value) {
  return ((DummyNode *)node)->val == value;
}

TEST(HashMap_Create_HasZeroAfterCreation, Basic) {
  hashmap_t *map = hashmap_create(8);

  EXPECT_EQ(map->size, 0);
  EXPECT_EQ(hashmap_size(map), 0);
  EXPECT_EQ(hashmap_load_factor(map), 0);

  hashmap_destroy(map);
}

TEST(HashMap_Create_HasCorrectCapacityAfterCreation, Basic) {
  hashmap_t *map = hashmap_create(8);

  EXPECT_EQ(map->capacity, 8);
  hashmap_destroy(map);
}

TEST(HashMap_Put_CanPutOneItemNoResize, Basic) {
  hashmap_t *map = hashmap_create(8);

  void *arr[1];

  make_items(arr, 1);

  char *key = (char *)"hello";

  hashmap_put(map, key, arr[0]);

  EXPECT_EQ(map->size, 1);

  void *val = hashmap_get(map, key);

  EXPECT_EQ(val, arr[0]);
  hashmap_destroy(map);
  clean_items(arr, 1);
}

TEST(HashMap_Put_CanPutThreeItemNoResize, Basic) {
  hashmap_t *map = hashmap_create(8);

  void *arr[3];

  make_items(arr, 3);

  char *key1 = (char *)"key1";
  char *key2 = (char *)"key2";
  char *key3 = (char *)"key3";

  hashmap_put(map, key1, arr[0]);
  hashmap_put(map, key2, arr[1]);
  hashmap_put(map, key3, arr[2]);

  EXPECT_EQ(map->size, 3);

  EXPECT_EQ(hashmap_get(map, key1), arr[0]);
  EXPECT_EQ(hashmap_get(map, key2), arr[1]);
  EXPECT_EQ(hashmap_get(map, key3), arr[2]);
  hashmap_destroy(map);
  clean_items(arr, 3);
}

TEST(HashMap_Put_CanPutFourItemResize, Basic) {
  hashmap_t *map = hashmap_create(4);

  void *arr[3];

  make_items(arr, 3);

  char *key1 = (char *)"key1";
  char *key2 = (char *)"key2";
  char *key3 = (char *)"key3";

  hashmap_put(map, key1, arr[0]);
  hashmap_put(map, key2, arr[1]);
  hashmap_put(map, key3, arr[2]);

  EXPECT_EQ(map->size, 3);
  EXPECT_EQ(map->capacity, 8); // should have resized

  EXPECT_EQ(hashmap_get(map, key3), arr[2]);
  EXPECT_EQ(hashmap_get(map, key1), arr[0]);
  EXPECT_EQ(hashmap_get(map, key2), arr[1]);
  hashmap_destroy(map);
  clean_items(arr, 3);
}
