# RLE: Same Pixels, Fewer Bytes

**Student / presenter:** Bingxi Li ([abbott400097-crypto](https://github.com/abbott400097-crypto))  
**Course:** COMP211, Fall 2026, Checkoff 3  
**Topic:** Data Representation → Data Compression → Run-Length Encoding

This project explores one question: **when does describing repetition save space?**
It includes a small C encoder and decoder, reproducible experiments, tests, and
an interactive pixel demonstration. The project uses an explicit teaching
format so that every size comparison can be checked.

Preparation status: Bingxi Li has personally run the program. The AI assistant
also ran the recorded experiments and automated tests.
The [shared RLE code-learning conversation](https://chatgpt.com/share/6afbcff5-f2d4-83ea-89dd-146df174e947)
is attached and was checked without signing in. It covers a later follow-up,
not the entire earlier preparation. The student-created final slides and video
remain to be added.

## The idea

A **run** is a consecutive stretch of the same value. RLE stores its length and
its value, preserving the order of the runs.

```text
Original:  A A A B B A A
Encoded:  (3,A) (2,B) (2,A)
Decoded:   A A A B B A A
```

The two A runs must stay separate. A frequency table such as `A:5, B:2` cannot
tell us where the A values appeared. RLE records ordered runs rather than total
frequencies.

## Connection to COMP211

The input and output are arrays of `uint8_t` values. On the tested platform,
each element is one byte. The encoder uses array indexing, a loop, and a counter.
It checks the output buffer's capacity before writing. The decoder reconstructs
the original array, and the experiment compares the restored bytes with the
original bytes.

```c
uint8_t original[] = {7, 7, 7, 7, 7, 2, 2, 2};
uint8_t encoded[]  = {5, 7, 3, 2};  /* (5,7), then (3,2) */
```

This is a concrete application of data representation and C arrays. A hash
table is not needed for the sequential scan. It could hold additional position
information, but a value-to-total-count table alone cannot reconstruct the input.
The demo uses a small count array to prove that two inputs have identical
frequencies; it does not implement or benchmark a hash table.

## Run the experiments

Requirements: a C11 compiler (`cc`, GCC, or Clang) and Make. No external library
or package installation is needed when those tools are already available.

```sh
make run
make test
```

Without Make:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Werror -O2 -Isrc src/rle.c src/demo.c -o rle_demo
./rle_demo
```

The exact captured experiment output is in [results.txt](results.txt).

## What the experiments show

| Input | Raw bytes | Encoded pairs | Encoded bytes | Exact reconstruction |
|---|---:|---:|---:|---|
| Four runs of eight pixels | 32 | 4 | 8 | Yes |
| Alternating colors | 32 | 32 | 64 | Yes |
| Eight 0s followed by eight 1s | 16 | 2 | 4 | Yes |
| Alternating 0 and 1, sixteen values | 16 | 16 | 32 | Yes |
| Three hundred copies of 7 | 300 | 2 | 4 | Yes |
| 12 × 12 image: two color bands | 144 | 2 | 4 | Yes |
| 12 × 12 image: pixel heart | 144 | 19 | 38 | Yes |
| 12 × 12 image: frequent changes | 144 | 144 | 288 | Yes |

### 1. Lossless does not mean smaller for every input

The four-run example saves 24 of 32 bytes, or 75%. Alternating colors require
one pair per pixel, doubling the payload. Both inputs decode exactly.

### 2. Order matters even when frequencies are identical

`0000000011111111` and `0101010101010101` contain the same numbers of 0 and 1.
Their encoded sizes are 4 and 32 bytes. The difference is how the equal values
are grouped. A histogram cannot distinguish them; ordered run pairs can.

### 3. The chosen representation has a boundary

An unsigned one-byte count can represent at most 255. A logical run of 300
copies of 7 becomes `(255,7) (45,7)`. It remains one logical repeated stretch,
but needs two encoded pairs. The decoder repeats both pairs in sequence.

### 4. A simple rule predicts the result

Let `n` be the number of raw bytes and `p` the number of encoded pairs, including
any split required by the 255 limit. The payload occupies `2p` bytes.

- It shrinks when `2p < n`.
- It stays the same size when `2p = n`.
- It expands when `2p > n`.

For nonempty inputs, this means the average number of input bytes represented
by each encoded pair must exceed two for this particular format to save space.
The threshold comes from our two-byte pair format; it is not a universal rule
for every real-world RLE variant.

## The format and its limits

Each pair contains a numeric unsigned count byte followed by a value byte.
The count must be in `1..255`. Counts are binary values, not decimal text
strings. An odd-length encoded stream or a zero count is invalid.

All examples compare **pixel-data payloads only**. Image dimensions, the palette,
and file headers are known separately and are not included. Images are read
left to right and then top to bottom. This teaching format allows a run to
continue across a row boundary.

This is not an encoder for PNG, BMP, TIFF, or DICOM files. Actual RLE formats may
use different packet layouts, literal modes, row rules, and metadata. A production
format might keep an uncompressed block when RLE would expand it; this demo does
not implement such a fallback.

The functions use caller-provided output buffers. `SIZE_MAX` signals invalid
input or insufficient capacity. Source and destination must not overlap. On
error, the destination may contain partial output and should not be used as a
valid encoded or decoded result. The library does not allocate memory.

## Files

- [src/rle.c](src/rle.c): the encoder and decoder.
- [src/demo.c](src/demo.c): four reproducible experiments.
- [tests/test_rle.c](tests/test_rle.c): round trips, zero/255 values, count limits,
  capacity checks, and malformed streams.
- [CODE-WALKTHROUGH.zh.md](CODE-WALKTHROUGH.zh.md): a Chinese guide to the actual C code.
- [demo/index.html](demo/index.html): the offline interactive visualization.
  Download and open it in a browser; GitHub's file view displays the HTML source.
- [presentation/](presentation/): reference slide draft and delivery notes.
- [REFLECTION.md](REFLECTION.md): the AI exploration reflection draft.
- [AI-CONVERSATION.md](AI-CONVERSATION.md): the conversation share link, its
  coverage, and actual excerpts from the earlier discussion.
- [REFERENCES.md](REFERENCES.md): course instructions and technical references.

## Attribution

Bingxi Li is the student and intended presenter. OpenAI Codex assisted with
explanations, code, test execution, documentation, and presentation drafts.
Student ownership of this repository does not mean its contents were produced
without AI assistance. The course requires student-created final slides; the
reference deck must not be represented as independently student-created work.

