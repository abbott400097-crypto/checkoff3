#include "rle.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void round_trip(const uint8_t *input, size_t n) {
    uint8_t encoded[1024], restored[512];
    size_t size = rle_encode(input, n, encoded, sizeof encoded);
    assert(size != SIZE_MAX && size <= 2 * n);
    size_t decoded_size = rle_decode(encoded, size, restored, sizeof restored);
    assert(decoded_size == n);
    assert(n == 0 || memcmp(input, restored, n) == 0);
}

int main(void) {
    uint8_t input[512], output[1024], restored[512];
    assert(rle_encode(NULL, 0, NULL, 0) == 0);
    assert(rle_decode(NULL, 0, NULL, 0) == 0);

    memset(input, 7, sizeof input);
    assert(rle_encode(input, 255, output, sizeof output) == 2);
    assert(output[0] == 255 && output[1] == 7);
    assert(rle_encode(input, 256, output, sizeof output) == 4);
    assert(output[0] == 255 && output[2] == 1);
    assert(rle_encode(input, 300, output, sizeof output) == 4);
    assert(output[0] == 255 && output[2] == 45);
    round_trip(input, 300);

    const uint8_t binary_data[] = {0, 0, 255, 255, 255, 0};
    const uint8_t expected[] = {2, 0, 3, 255, 1, 0};
    assert(rle_encode(binary_data, sizeof binary_data, output, sizeof output)
           == sizeof expected);
    assert(memcmp(output, expected, sizeof expected) == 0);
    round_trip(binary_data, sizeof binary_data);

    assert(rle_encode(input, 1, output, 0) == SIZE_MAX);
    assert(rle_encode(input, 1, output, 1) == SIZE_MAX);
    assert(rle_encode(input, 1, output, 2) == 2);
    const uint8_t odd[] = {1, 7, 2};
    const uint8_t zero_count[] = {0, 7};
    const uint8_t two_sevens[] = {2, 7};
    assert(rle_decode(odd, sizeof odd, restored, sizeof restored) == SIZE_MAX);
    assert(rle_decode(zero_count, sizeof zero_count, restored, sizeof restored)
           == SIZE_MAX);
    assert(rle_decode(two_sevens, 2, restored, 1) == SIZE_MAX);
    assert(rle_decode(two_sevens, 2, restored, 2) == 2);

    /* Exercise mixed values and run lengths at every input length. */
    for (size_t n = 0; n <= sizeof input; ++n) {
        for (size_t i = 0; i < n; ++i) input[i] = (uint8_t)(i % 4);
        round_trip(input, n);
        for (size_t i = 0; i < n; ++i) input[i] = (uint8_t)((i / 17) % 4);
        round_trip(input, n);
    }
    puts("All RLE tests passed: round trips, binary values, count limits, capacity, invalid streams.");
    return 0;
}
