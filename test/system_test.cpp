#include "gtest/gtest.h"

namespace {

TEST(SystemTest, ARMv7_32bit) {
  EXPECT_EQ(4, sizeof(void*));
}

}
