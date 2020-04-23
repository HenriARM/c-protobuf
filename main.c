#include <stdio.h>
#include <stdlib.h>
// nanopb
#include "protobuf/pb_encode.h"
#include "protobuf/pb_decode.h"

#define BUF_SIZE 128
// TODO add more variables
struct Message {
    int value;
};

// used for all structs
const pb_msgdesc_t STRUCT_FIELDS;

// returns buffer with encoded struct
void encode_struct(void *src_struct, unsigned char *buf, unsigned long buf_size) {
    // create a stream that will write to our buffer
    pb_ostream_t stream = pb_ostream_from_buffer(buf, buf_size);
    bool status = pb_encode(&stream, &STRUCT_FIELDS, &src_struct);
    if (!status) {
        printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        exit(1);
    }
}

// returns encoded struct, decoding buffer
void decode_struct(unsigned char *buf, void *dest_struct) {
    // create a stream that reads from the buffer
    pb_istream_t stream = pb_istream_from_buffer(buf, 0);
    bool status = pb_decode(&stream, &STRUCT_FIELDS, &dest_struct);
    if (!status) {
        printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
        exit(1);
    }
}

int main() {
    unsigned char buf[BUF_SIZE];
    struct Message en_message, de_message;
    en_message.value = 2;

    encode_struct(&en_message, buf, BUF_SIZE);
    decode_struct(buf, &de_message);
    printf("Your value was %d!\n", de_message.value);

    return 0;
}
