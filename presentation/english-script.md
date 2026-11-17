# Complete English Presentation Script

AI-assisted rehearsal draft. Read only the spoken text; bracketed directions are stage cues.

Nine slides; approximately 637 spoken words. At 120–130 words per minute, plus two 5–10 second audience pauses, plan for about 5.1–5.6 minutes. Rehearse once with a timer.

## Slide 1: Same pixels. Fewer bytes.

Hi everyone. Today I’m going to explain run-length encoding, or R-L-E.

Can we keep every pixel in a picture while storing less data? RLE describes repeated values using counts. I’ll show how we encode a row of pixels, recover the original data, and test the method on different patterns.

## Slide 2: How would you describe this row?

Here we have thirty-two pixels. The letters represent different colors.

In this example, each pixel uses one byte, so the original row takes thirty-two bytes.

How would you describe this row without listing every pixel, one by one?

[Pause for 5–10 seconds. Let the audience answer before advancing.]

Let’s look at one way to describe it.

## Slide 3: A row becomes four runs

We can say eight As, then eight Bs, eight Cs, and eight Ds. Each consecutive group of equal values is called a run.

We store each run as a count and a color index. In our example format, each takes one byte. That makes two bytes per pair, so four pairs take eight bytes.

We started with thirty-two bytes and saved twenty-four, or seventy-five percent.

These numbers count only pixel data. The image dimensions and the color palette are known separately.

## Slide 4: Decoding restores every pixel

Decoding expands each pair back into pixels. When the decoder reads eight and A, it writes A eight times. Then it does the same for B, C, and D.

We recover all thirty-two pixels in exactly the original order. This is what lossless means: we can reconstruct the original data exactly.

The C program checks both the decoded length and every decoded byte against the original input.

## Slide 5: Will this row get smaller?

Now let’s change the pattern. We still have thirty-two pixels, but the colors alternate between A and B.

We will use the same format: one byte for the count and one byte for the color index.

Will the encoded result be smaller, the same size, or bigger? Why?

[Pause for 5–10 seconds. Let the audience answer before advancing.]

Let’s count the pairs and check.

## Slide 6: Compression can make data bigger

The result is bigger. Every run contains just one pixel, so we store one A, then one B, then one A again.

That gives thirty-two pairs. Each pair takes two bytes, so the result is sixty-four bytes, twice the original size.

We can still decode every pixel correctly. Lossless means exact recovery, but it does not guarantee a smaller result. Here, the extra count bytes make the data larger.

## Slide 7: ABAB still has a pattern

But ABAB still has a pattern: the sequence AB repeats.

Our RLE counts consecutive copies of one value, so it works well for AAAA. Other methods, such as L-Z seventy-seven, can use repeated sequences by referring back to earlier data.

That means a pattern can be useful for compression even when our RLE handles it poorly. The exact size depends on the encoding format. My demo only implements RLE.

## Slide 8: Same size. Different patterns.

Back to RLE, these images all have twelve by twelve pixels. Each starts with one hundred and forty-four bytes.

We read left to right, then continue on the next row. Our format lets a run continue across a row boundary.

The left image has two runs, so it takes four bytes. The heart has nineteen runs, including its background, so it takes thirty-eight bytes.

On the right, every next pixel changes color. That gives one hundred and forty-four pairs, or two hundred and eighty-eight bytes.

The dimensions are the same, but the patterns change the result. These are sizes in our example format, not PNG file sizes.

## Slide 9: RLE works best with long runs

RLE works best when equal values stay together in long runs. Our examples show that it can save space or make data larger, while still preserving every value.

The connection to C is an array problem. The encoder scans an array, counts equal neighbors, and writes count-value pairs into another array.

Our stored count uses one unsigned byte, so each pair can represent up to two hundred and fifty-five copies. Longer runs need more pairs.

My main takeaway is to look at the pattern and measure the result.

Thank you. What questions do you have?
