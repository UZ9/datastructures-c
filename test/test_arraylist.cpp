#include <gtest/gtest.h>

extern "C" {
#include "arraylist.h"
}

TEST(ArrayList_Create_HasSizeZeroAfterCreation, Basic) {
  arraylist_t *list = arraylist_create(10);

  EXPECT_EQ(list->size, 0);
}

TEST(ArrayList_Size_HasSizeZeroAfterCreation, Basic) {
  arraylist_t *list = arraylist_create(10);

  EXPECT_EQ(arraylist_size(list), 0);
}

TEST(ArrayList_IsEmpty_ShouldBeTrueAfterInitialization, Basic) {
  arraylist_t *list = arraylist_create(10);

  EXPECT_TRUE(arraylist_is_empty(list));
}

// TEST: arraylist empty after adding 1 then removing
