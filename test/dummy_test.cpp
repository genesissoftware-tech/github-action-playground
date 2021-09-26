#include "dummy.hpp"
#include "gtest/gtest.h"

namespace {

TEST(DummyTest, zero) {
  EXPECT_EQ(0, return_0());
}

}
