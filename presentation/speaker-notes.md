# Reference speaker notes

AI-assisted rehearsal draft; review and adapt in your own words.

## Slide 1

中文：开场只提出问题：保留每一个像素，能不能少存数据？RLE 通过记录连续重复的次数实现。
English: Can we keep every pixel in a picture and still store less data? Today I will explain run-length encoding, or R-L-E. It describes a repeated value with a count. We will encode a row, restore it, and see why the same method can sometimes make data larger.
Source: original RLE teaching example. The teaching format uses one byte for each color index and one byte for each run count.

## Slide 2

中文：先问观众：不用逐个列出像素，你会怎么描述这行颜色？等待回答，再解释四个 run。A、B、C、D 是颜色编号的显示标签。每个原始像素用 1 byte，count 也用 1 byte。每对 2 bytes，4 对共 8 bytes。节省 (32−8)/32=75%。尺寸和调色板另行已知。
English: How would you describe this row without listing every pixel? Take a moment. I would say eight of color A, then eight of B, eight of C, and eight of D. Each uninterrupted group is a run. We store each run as a count and a color index. In this teaching format, each number takes one byte. Thirty-two original pixels take thirty-two bytes. Four pairs take eight bytes. We save twenty-four out of thirty-two bytes, or seventy-five percent. These numbers count only pixel data. The dimensions and palette are known separately.
Source: original teaching example, verified by the companion C encoder and decoder.

## Slide 3

中文：看到 (8,A)，就在结果里写八个 A。其余依次展开，得到和原来完全相同的 32 个像素。lossless 是无损，要求值和顺序完全一致，而不是肉眼看着差不多。
English: Decoding reverses that description. The decoder reads eight and color A, and writes A eight times. Then it does the same for B, C, and D. We get every original value back in the original order. This is lossless compression. We changed how we describe the pixels, but kept enough information to reconstruct them exactly. A simple check is to compare the decoded array with the original array, byte by byte. The companion C example performs that check.
Source: original teaching example with verified exact encode/decode round trip.

## Slide 4

中文：先让观众猜交替颜色还能不能省空间。每个 run 只有一个像素，仍然需要次数+颜色两个字节。所以 32 个像素变成 32 对，共 64 bytes。无损只保证完整还原，不保证每个输入都变小。
English: What if every neighboring pixel is different? Here the colors alternate. Every run has length one. Instead of four pairs, we now need thirty-two pairs. Every pair still takes two bytes, so the encoded data takes sixty-four bytes. That is twice the original size. We can still decode it perfectly. Lossless describes whether we can recover the original information. It does not promise a smaller result for every input. In our format, each run has to pay for an extra count byte. Long runs save enough repetition to cover that cost. Short runs may not.
Source: original alternating-color example, verified 32 raw bytes and 64 encoded bytes.

## Slide 5

中文：三张图都是 144 个像素，原始大小完全相同。按从左到右、从上到下的顺序读，不在每行强制截断。左边前 72 格颜色相同、后 72 格颜色相同，只有两段，所以 4 bytes。爱心 19 段，38 bytes。右边每格变色，144 段，288 bytes。不是计算 PNG 文件大小。
English: These pictures all contain twelve times twelve pixels. With one byte per color index, each starts at one hundred and forty-four bytes. We read left to right, then continue on the next row. Our format allows a run to continue across a row boundary. The two color bands contain only two runs, so their encoded pixel data takes four bytes. The heart has nineteen runs and takes thirty-eight bytes. On the right, every next pixel changes color. That gives one hundred and forty-four runs and two hundred and eighty-eight bytes. The picture dimensions stayed the same. The pattern changed the result. These are sizes in our teaching format, not sizes of PNG files.
Source: patterns from companion presentation; runs independently counted as 2, 19, 144; each pair occupies 2 bytes.

## Slide 6

中文：收尾：RLE 对连续重复的内容有效，顺序和重复长度决定效果。连接 C：遍历 uint8_t 数组，比较相邻值，计数，然后写次数和颜色。count 是一字节无符号数，最多255，更长需要拆段。
English: The central idea is simple: replace consecutive copies with a count and a value. In the first example, that changed thirty-two bytes into eight. With alternating colors, it changed thirty-two into sixty-four. Both examples decoded correctly. The connection to C is an array problem. We scan byte values, count equal neighbors, and write the resulting pairs into another array. Because our count uses one unsigned byte, one pair can describe up to two hundred and fifty-five copies. We split longer runs into more pairs. The practical takeaway is to look at the data and measure the result. R-L-E works best when repeated values stay together for long stretches.
Q&A: A run is a consecutive stretch of equal values. Lossless means exact reconstruction. Metadata is excluded from our size comparison. This format uses count/value pairs, while real RLE file formats may add literal modes or other rules.
