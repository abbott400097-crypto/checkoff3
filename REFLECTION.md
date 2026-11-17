# AI Exploration Reflection: Run-Length Encoding

**Student:** Bingxi Li  
**Course:** COMP211, Fall 2026  
**AI tool:** OpenAI Codex  
**Status:** Draft for my review before submission.  
**Conversation permalink:** See [AI-CONVERSATION.md](AI-CONVERSATION.md); the share link is not yet attached.

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

These are excerpts from my actual Chinese messages, followed by English
translations. They are not a reconstructed conversation.

1. **“先让我弄懂RLE，再告诉我每页怎么讲”**  
   “First help me understand RLE, then tell me how to explain each slide.”  
   I wanted to understand the mechanism before relying on an English script.
   The explanation used a sequence of repeated values, its count-value pairs,
   and the sequence reconstructed from those pairs.

2. **“这个跟211有啥关系”**  
   “What does this have to do with COMP211?”  
   This led to a concrete connection: a C program can scan a byte array, count
   equal neighboring values, and write a new byte representation. The
   discussion also separated selecting an approved topic from making the
   connection clear to an audience.

3. **“一般用数组吗 这种为什么不是HASHTABLE存”**  
   “Do people usually use an array? Why not store this in a hash table?”  
   The response distinguished ordered runs from total frequencies. A table
   that says there are five As and two Bs cannot recover the order in
   `AAABBAA`. The accompanying experiment compares two sequences with the
   same frequencies but different run lengths.

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

I selected two code questions from the assistant's suggested list for further
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
and explanations. I still need to review this reflection for accuracy, create
my own final slides as the assignment requires, and attach the share link to
the actual learning conversation.

