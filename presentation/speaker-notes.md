# Reference speaker notes

AI-assisted rehearsal draft; review and adapt in your own words.

Questions are on slides 2 and 5. Slide 7 compares repeated values with repeated sequences.

## Slide 1: Same pixels. Fewer bytes.

中文：开场介绍 RLE：保留所有像素，尝试减少存储。RLE 逐字母读。开头的问句用于引入，不需要等待回答。

English:

Hi everyone. Today I’m going to explain run-length encoding, or R-L-E.

Can we keep every pixel in a picture while storing less data? RLE describes repeated values using counts. I’ll show how we encode a row of pixels, recover the original data, and test the method on different patterns.

Source: Original teaching examples. All size comparisons use the explicitly stated count/value format.

## Slide 2: How would you describe this row?

中文：说明 32 个像素和一像素一字节后，问观众如何简短描述。停 5–10 秒，不翻页、不先说八个 A。等回答后再翻页。

English:

Here we have thirty-two pixels. The letters represent different colors.

In this example, each pixel uses one byte, so the original row takes thirty-two bytes.

How would you describe this row without listing every pixel, one by one?

[Pause for 5–10 seconds. Let the audience answer before advancing.]

Let’s look at one way to describe it.

Source: Original 32-pixel example. The encoded answer is only on the next slide.

## Slide 3: A row becomes four runs

中文：揭晓八个 A、八个 B、八个 C、八个 D。run 是连续相同的一段。本例 count 和颜色编号各占一字节，四对就是八字节，比 32 少 75%。只比较像素数据。

English:

We can say eight As, then eight Bs, eight Cs, and eight Ds. Each consecutive group of equal values is called a run.

We store each run as a count and a color index. In our example format, each takes one byte. That makes two bytes per pair, so four pairs take eight bytes.

We started with thirty-two bytes and saved twenty-four, or seventy-five percent.

These numbers count only pixel data. The image dimensions and the color palette are known separately.

Source: Original example verified by the companion C program: 32 raw bytes, four pairs, eight encoded bytes.

## Slide 4: Decoding restores every pixel

中文：解码就是把每对展开。八和 A 表示写八个 A。无损要求长度、每个数值和顺序完全一致；程序用长度和逐字节比较验证。

English:

Decoding expands each pair back into pixels. When the decoder reads eight and A, it writes A eight times. Then it does the same for B, C, and D.

We recover all thirty-two pixels in exactly the original order. This is what lossless means: we can reconstruct the original data exactly.

The C program checks both the decoded length and every decoded byte against the original input.

Source: The companion demo checks restored_size == n and memcmp(data, restored, n) == 0.

## Slide 5: Will this row get smaller?

中文：第二次互动。仍是 32 个像素，但颜色交替。问更小、一样大还是更大。停 5–10 秒，不先说每段一个或 64 字节。

English:

Now let’s change the pattern. We still have thirty-two pixels, but the colors alternate between A and B.

We will use the same format: one byte for the count and one byte for the color index.

Will the encoded result be smaller, the same size, or bigger? Why?

[Pause for 5–10 seconds. Let the audience answer before advancing.]

Let’s count the pairs and check.

Source: Original alternating-color example. The answer is revealed on the following slide.

## Slide 6: Compression can make data bigger

中文：每段只有一个像素，要写 32 对，每对两个字节，所以 64 字节。仍然无损，但不省空间。讲完衔接下一页：这个交替输入仍然有 AB 重复的规律。

English:

The result is bigger. Every run contains just one pixel, so we store one A, then one B, then one A again.

That gives thirty-two pairs. Each pair takes two bytes, so the result is sixty-four bytes, twice the original size.

We can still decode every pixel correctly. Lossless means exact recovery, but it does not guarantee a smaller result. Here, the extra count bytes make the data larger.

Source: Companion C experiment: alternating input has 32 raw bytes and 64 encoded bytes, with exact reconstruction.

## Slide 7: ABAB still has a pattern

中文：只讲简单比较。AAAA 是单个值连续重复，我们的 RLE 很适合；ABAB 是整个 AB 片段重复。LZ77 可引用前面出现过的字节串，能利用这种规律。不要把 AB 重复几次当成 LZ77 的实际编码，也不声称算过压缩大小。此页无需提问，直接解释约 30–40 秒。

English:

But ABAB still has a pattern: the sequence AB repeats.

Our RLE counts consecutive copies of one value, so it works well for AAAA. Other methods, such as L-Z seventy-seven, can use repeated sequences by referring back to earlier data.

That means a pattern can be useful for compression even when our RLE handles it poorly. The exact size depends on the encoding format. My demo only implements RLE.

Source: RFC 1951, section 3.2: repeated strings may be represented by a backward distance and length. https://www.rfc-editor.org/rfc/rfc1951.html . This slide is a conceptual comparison, not an implementation or size benchmark of LZ77.

## Slide 8: Same size. Different patterns.

中文：三张图均为 12×12=144 像素。按行连续读取，允许跨行继续同一段。两色带 2 段，爱心含背景共 19 段，频繁变色 144 段；对应 4、38、288 字节。不是 PNG 文件大小。

English:

Back to RLE, these images all have twelve by twelve pixels. Each starts with one hundred and forty-four bytes.

We read left to right, then continue on the next row. Our format lets a run continue across a row boundary.

The left image has two runs, so it takes four bytes. The heart has nineteen runs, including its background, so it takes thirty-eight bytes.

On the right, every next pixel changes color. That gives one hundred and forty-four pairs, or two hundred and eighty-eight bytes.

The dimensions are the same, but the patterns change the result. These are sizes in our example format, not PNG file sizes.

Source: Companion C program counts 2, 19, and 144 encoded pairs for the three 144-byte patterns.

## Slide 9: RLE works best with long runs

中文：收尾强调连续重复长度决定效果，并连接到 C 数组扫描、相邻比较和计数。一个无符号次数字节最多 255，更长的段要拆开。最后感谢并开放观众提问。

English:

RLE works best when equal values stay together in long runs. Our examples show that it can save space or make data larger, while still preserving every value.

The connection to C is an array problem. The encoder scans an array, counts equal neighbors, and writes count-value pairs into another array.

Our stored count uses one unsigned byte, so each pair can represent up to two hundred and fifty-five copies. Longer runs need more pairs.

My main takeaway is to look at the pattern and measure the result.

Thank you. What questions do you have?

Source: Companion implementation in src/rle.c and the 300-copy split experiment in src/demo.c.
