#include <pb_encode.h>
#include <pb_decode.h>

#include "dummy.hpp"
#include "dummy.pb.h"

std::int32_t return_0() {
    return 0;
}

std::uint32_t encode_dummy(uint32_t value, uint8_t* buffer, uint32_t buffer_length) {
    DummyMessage message = DummyMessage_init_zero;
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_length);

    message.value = value;

    pb_encode(&stream, DummyMessage_fields, &message);
    
    return stream.bytes_written;
}

std::uint32_t dencode_dummy(uint8_t* buffer, uint32_t buffer_length) {
    DummyMessage message = DummyMessage_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(buffer, buffer_length);

    pb_decode(&stream, DummyMessage_fields, &message);

    return message.value;
}
