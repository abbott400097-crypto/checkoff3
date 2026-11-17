#ifndef RLE_H
#define RLE_H

#include <stddef.h>
#include <stdint.h>

/* Teaching format: [count, value] pairs. A count is between 1 and 255.
 * Return the number of bytes written, or SIZE_MAX on invalid input/capacity.
 * For nonzero sizes, pointers must refer to sufficiently large buffers.
 * Source and destination buffers must not overlap.
 * The destination may contain partial output when an error is returned. */
size_t rle_encode(const uint8_t *src, size_t n, uint8_t *dst, size_t capacity);
size_t rle_decode(const uint8_t *src, size_t n, uint8_t *dst, size_t capacity);

#endif

