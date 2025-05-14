#include <gtest/gtest.h>

extern "C" {
#include "arraylist.h"
}

TEST(HelloTest, Basic) {
  EXPECT_STRNE("hello", "world");

  EXPECT_EQ(sum(1, 3), 4);

  EXPECT_EQ(7 * 6, 42);
}
