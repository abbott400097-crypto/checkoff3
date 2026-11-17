# Presentation Materials

`rle-presentation-draft.pptx` is an editable nine-slide **AI-generated reference
draft**. It contains bilingual speaker notes. It is not the student's completed
final slide submission.

The course explicitly requires student-created slides. Create the final slides
from your own understanding, add them here, and use the same final deck for the
recording and the live presentation. Do not label this reference deck as
independently student-created work.

The nine pages keep audience questions separate from their answers:

1. The question: can the same pixels occupy fewer bytes?
2. Question: how would you describe the pixel row? No encoded answer is shown.
3. Reveal: four count-value pairs use 8 bytes instead of 32.
4. Decoding and exact reconstruction.
5. Question: will an alternating row become smaller, stay the same, or grow?
6. Reveal: 32 pairs use 64 bytes; the payload doubles.
7. Simple comparison: RLE counts repeated values; LZ77 can reuse repeated
   sequences such as `AB`. This is a conceptual comparison, not an implementation
   or size benchmark of LZ77.
8. Three 12 × 12 patterns with different encoded sizes.
9. The role of long runs and the connection to C arrays.

Pause for 5–10 seconds on pages 2 and 5, let the audience respond, then advance.
The question titles do not disclose the answer. Page 7 adds a short explanation
after the alternating-color result; it does not add another audience question.
Rehearse the entire talk to keep it within 5–7 minutes.

[english-script.md](english-script.md) contains the complete revised English
script, with pause cues. The same narration is in the PowerPoint speaker notes;
[speaker-notes.md](speaker-notes.md) also includes Chinese explanations and sources.

The repository adds two useful questions for discussion without requiring a
longer main talk: why total frequencies are insufficient, and what happens
when a run exceeds 255 values. See the code walkthrough and experiment output.

No recording is included yet. The recording must be the student's own complete
5–7 minute presentation and must be submitted before the scheduled checkoff.
