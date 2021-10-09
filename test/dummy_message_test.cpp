#include "dummy.hpp"
#include "gtest/gtest.h"

namespace {

const uint32_t buffer_length = 255;

TEST(DummyMessageEncodeTest, 12) {
    uint8_t buffer[buffer_length];
    uint32_t result = encode_dummy(12, buffer, buffer_length);
    EXPECT_NE(0, result);
}

}
