#include "rle.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void report(const char *name, const uint8_t *data, size_t n) {
    uint8_t encoded[1024], restored[512];
    size_t size = rle_encode(data, n, encoded, sizeof encoded);
    assert(size != SIZE_MAX);
    size_t restored_size = rle_decode(encoded, size, restored, sizeof restored);
    int equal = restored_size == n && memcmp(data, restored, n) == 0;
    assert(equal);

    printf("%-23s raw=%3zu bytes  pairs=%3zu  encoded=%3zu bytes  exact=%s\n",
           name, n, size / 2, size, equal ? "yes" : "NO");
    if (size <= 8) {
        printf("  pairs:");
        for (size_t i = 0; i < size; i += 2) {
            printf(" (%u,%u)", (unsigned)encoded[i], (unsigned)encoded[i + 1]);
        }
        putchar('\n');
    }
}

static void histogram(const uint8_t *data, size_t n, size_t counts[256]) {
    memset(counts, 0, 256 * sizeof counts[0]);
    for (size_t i = 0; i < n; ++i) ++counts[data[i]];
}

int main(void) {
    uint8_t four_runs[32], alternating[32];
    for (size_t i = 0; i < 32; ++i) {
        four_runs[i] = (uint8_t)(i / 8);
        alternating[i] = (uint8_t)(i % 2);
    }

    puts("Experiment 1: compression can shrink or expand data");
    report("Four long runs", four_runs, sizeof four_runs);
    report("Alternating colors", alternating, sizeof alternating);

    puts("\nExperiment 2: same frequencies, different order");
    uint8_t grouped[16], mixed[16];
    for (size_t i = 0; i < 16; ++i) {
        grouped[i] = (uint8_t)(i / 8);
        mixed[i] = (uint8_t)(i % 2);
    }
    size_t grouped_counts[256], mixed_counts[256];
    histogram(grouped, sizeof grouped, grouped_counts);
    histogram(mixed, sizeof mixed, mixed_counts);
    assert(memcmp(grouped_counts, mixed_counts, sizeof grouped_counts) == 0);
    printf("Both contain value 0: %zu times; value 1: %zu times.\n",
           grouped_counts[0], grouped_counts[1]);
    report("0000000011111111", grouped, sizeof grouped);
    report("0101010101010101", mixed, sizeof mixed);
    puts("Total counts cannot distinguish these inputs. RLE preserves their order.");

    puts("\nExperiment 3: one count byte has a limit");
    uint8_t long_run[300];
    memset(long_run, 7, sizeof long_run);
    report("300 copies of 7", long_run, sizeof long_run);
    puts("One logical run splits into pairs (255,7) and (45,7).");

    puts("\nExperiment 4: the three presentation images");
    uint8_t bands[144], heart[144], changing[144];
    const char heart_rows[] =
        "000000000000"
        "000220022000"
        "002222222200"
        "022222222220"
        "022222222220"
        "002222222200"
        "000222222000"
        "000022220000"
        "000002200000"
        "000000000000"
        "000000000000"
        "000000000000";
    for (size_t i = 0; i < 144; ++i) {
        bands[i] = i < 72 ? 1 : 3;
        heart[i] = (uint8_t)(heart_rows[i] - '0');
        changing[i] = (uint8_t)((i % 12 + i / 12) % 4);
    }
    report("Two color bands", bands, sizeof bands);
    report("Pixel heart", heart, sizeof heart);
    report("Frequent color changes", changing, sizeof changing);
    return 0;
}

