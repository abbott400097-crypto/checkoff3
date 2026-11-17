# AI Exploration Reflection: Run-Length Encoding

**Student:** Bingxi Li  
**Course:** COMP211, Fall 2026  
**AI tools:** OpenAI Codex and ChatGPT  
**Status:** Draft for my review before submission.  
**Conversation permalink:** [RLE code-learning follow-up](https://chatgpt.com/share/6afbcff5-f2d4-83ea-89dd-146df174e947). This is a later follow-up; [AI-CONVERSATION.md](AI-CONVERSATION.md) distinguishes its contents from earlier discussion.

## How I approached the topic

I asked AI to help me find a topic that I could understand and explain clearly
within a short presentation. The conversation eventually focused on run-length
encoding, which is one of the listed Checkoff 3 topics. I wanted visual examples
because I found it difficult to follow explanations that did not show the
actual data or code being discussed.

My questions went beyond how to replace repeated values with a count. I wanted
to know whether the topic really connected to COMP211, whether arrays were a
natural representation, and why a hash table was not the obvious choice. I
also questioned whether the proposed presentation had enough substance.

## Representative prompts

These three prompts are visible in the shared follow-up. They grew out of
code-reading questions suggested during the earlier preparation; they are not
claimed as independently devised prompts. The Chinese text is quoted, followed
by an English explanation.

1. **“rle_encode 的四个参数 src、n、dst、capacity 分别传什么？为什么传数组地址后，还要另外传长度？uint8_t、size_t 和 const 在这里分别是什么意思？”**  
   I asked what the four arguments receive and what the types mean. The response
   separated input address/length from output address/capacity. It clarified that
   a pointer does not carry the array length and that passing a capacity does not
   allocate storage.

2. **“for (size_t i = 0; i < n;) 为什么没有 i++？为什么最后写 i += count？请列出每一轮的 i、count 和当前处理的数组元素。”**  
   I asked for a trace of the loop rather than only a definition. In `AAABBBAA`,
   the run starts are 0, 3, and 6, with counts 3, 3, and 2. Advancing by the count
   skips the whole run just processed. Adding a separate `i++` would skip data.

3. **“while (count < 255 && count < n - i && src[i + count] == src[i]) 的三个条件分别检查什么？src[i + count] 正在看哪个元素？读取它之前，哪个条件防止越界？”**  
   I asked which condition makes the next read safe. The explanation showed how
   `count < n - i` checks the remaining input and how `&&` stops before reading
   beyond the array. The 255 limit separately protects the one-byte count format.

## How I engaged with the responses

I challenged the explanations when they seemed disconnected from the course
or too shallow. The follow-up examples made the question more specific: RLE
must preserve order, and its count bytes have a storage cost. Lossless means
that the original data can be reconstructed exactly; it does not guarantee
that every input becomes smaller.

The assistant helped prepare a C encoder and decoder, and I personally ran
the program. I did not independently write the entire implementation. The
project's recorded experiment results show that 32 bytes can become either
8 or 64 bytes, depending on the pattern. Another example splits 300 copies of
a value into counts of 255 and 45. Running a program and understanding each
line are different tasks, so I also wanted to examine how decoding works.

In the earlier discussion, outside the shared follow-up, I selected two code
questions from the assistant's suggested list for further
discussion: why the decoder advances by two and uses `memset`, and why it
rejects odd-length input and zero counts. Each pair contains a count followed
by a value, so advancing by two moves to the next pair. `memset` repeats the
value into the output buffer. For example, `{3,7,2,2,1,7}` decodes to
`{7,7,7,2,2,7}`. An odd-length stream leaves an incomplete pair, and a zero
count violates our format's range of 1 through 255. A value byte of zero is
still valid. Exact reconstruction is checked by comparing the decoded length
and then the original and restored bytes. These questions connected the
idea of lossless compression to specific C operations and validation checks.

## What I would do differently

I would establish the core example and read the assignment requirements before
spending time on slide design. Next time, I would write down my prediction
before running each experiment, then explain any difference between my
prediction and the output. I would also trace a small example by hand before
asking AI for more polished presentation material. That would help me check
whether I can reproduce the reasoning independently.

AI helped draft this reflection and the reference slides as well as the code
and explanations. I still need to review this reflection for accuracy and create
my own final slides as the assignment requires. The attached link documents the
later code-learning exchange; it does not claim to contain all earlier work.

