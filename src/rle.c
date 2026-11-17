#include "rle.h"

#include <string.h>

size_t rle_encode(const uint8_t *src, size_t n,
                  uint8_t *dst, size_t capacity) {
    size_t out = 0;

    for (size_t i = 0; i < n;) {
        size_t count = 1;

        /* Grow the current run while its value stays the same.
         * A count byte cannot represent more than 255 copies. */
        while (count < 255 && count < n - i && src[i + count] == src[i]) {
            ++count;
        }

        /* Check space before writing the count and the value. */
        if (capacity - out < 2) return SIZE_MAX;
        dst[out++] = (uint8_t)count;
        dst[out++] = src[i];

        /* Skip all the source bytes represented by this pair. */
        i += count;
    }

    return out;
}

size_t rle_decode(const uint8_t *src, size_t n,
                  uint8_t *dst, size_t capacity) {
    size_t out = 0;
    if (n % 2 != 0) return SIZE_MAX;

    for (size_t i = 0; i < n; i += 2) {
        size_t count = src[i];
        uint8_t value = src[i + 1];

        if (count == 0 || count > capacity - out) return SIZE_MAX;

        /* Write 'count' copies of this one-byte value. */
        memset(dst + out, value, count);
        out += count;
    }

    return out;
}

