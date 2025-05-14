#include <gtest/gtest.h>

extern "C" {
#include "arraylist.h"
}

struct DummyNode {
  int val;
};

void make_items(void **arr, int count) {
  for (int i = 0; i < count; i++) {
    DummyNode *node = (DummyNode *)malloc(sizeof(DummyNode));

    node->val = i;

    arr[i] = node;
  }
}

void print_item(void *item) { printf("%d ", ((DummyNode *)item)->val); }

bool node_is_value(void *node, int value) {
  return ((DummyNode *)node)->val == value;
}

TEST(ArrayList_Create_HasSizeZeroAfterCreation, Basic) {
  arraylist_t *list = arraylist_create(10);

  EXPECT_EQ(list->size, 0);
}

TEST(ArrayList_Create_HasCorrectCapacity, Basic) {
  arraylist_t *list = arraylist_create(10);

  EXPECT_EQ(list->capacity, 10);
}

///////////////////////////////////////////

TEST(ArrayList_Size_HasSizeZeroAfterCreation, Basic) {
  arraylist_t *list = arraylist_create(10);

  EXPECT_EQ(arraylist_size(list), 0);
}

///////////////////////////////////////////

TEST(ArrayList_IsEmpty_ShouldBeTrueAfterInitialization, Basic) {
  arraylist_t *list = arraylist_create(10);

  EXPECT_TRUE(arraylist_is_empty(list));
}

///////////////////////////////////////////

TEST(ArrayList_Add_NoResize, Basic) {
  arraylist_t *list = arraylist_create(5);

  void *arr[3];

  auto a = &arr;

  make_items(arr, 3);

  EXPECT_TRUE(node_is_value(arr[0], 0));
  EXPECT_TRUE(node_is_value(arr[1], 1));
  EXPECT_TRUE(node_is_value(arr[2], 2));

  arraylist_add(list, arr[0]);
  arraylist_add(list, arr[1]);
  arraylist_add(list, arr[2]);

  EXPECT_EQ(arraylist_size(list), 3);

  EXPECT_EQ(list->data[0], arr[0]);
  EXPECT_EQ(list->data[1], arr[1]);
  EXPECT_EQ(list->data[2], arr[2]);
}

TEST(ArrayList_Add_CanResize, Basic) {
  arraylist_t *list = arraylist_create(2);

  void *arr[3];

  auto a = &arr;

  make_items(arr, 3);

  EXPECT_TRUE(node_is_value(arr[0], 0));
  EXPECT_TRUE(node_is_value(arr[1], 1));
  EXPECT_TRUE(node_is_value(arr[2], 2));

  arraylist_add(list, arr[0]);
  arraylist_add(list, arr[1]);
  arraylist_add(list, arr[2]);

  EXPECT_EQ(arraylist_size(list), 3);

  EXPECT_EQ(list->data[0], arr[0]);
  EXPECT_EQ(list->data[1], arr[1]);
  EXPECT_EQ(list->data[2], arr[2]);
}

TEST(ArrayList_Add_InMiddle, Basic) {
  arraylist_t *list = arraylist_create(5);

  void *arr[4];

  auto a = &arr;

  make_items(arr, 4);

  EXPECT_TRUE(node_is_value(arr[0], 0));
  EXPECT_TRUE(node_is_value(arr[1], 1));
  EXPECT_TRUE(node_is_value(arr[2], 2));

  arraylist_add(list, arr[0]);
  arraylist_add(list, arr[1]);
  arraylist_add(list, arr[2]);

  EXPECT_EQ(arraylist_size(list), 3);

  EXPECT_EQ(list->data[0], arr[0]);
  EXPECT_EQ(list->data[1], arr[1]);
  EXPECT_EQ(list->data[2], arr[2]);

  arraylist_add_at_index(list, 1, arr[3]);
  EXPECT_EQ(list->data[1], arr[3]);

  EXPECT_EQ(list->data[2], arr[1]);

  EXPECT_EQ(list->data[3], arr[2]);
}

// TEST: arraylist empty after adding 1 then removing
