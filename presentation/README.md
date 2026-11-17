# Presentation Materials

`rle-presentation-draft.pptx` is an editable eight-slide **AI-generated reference
draft**. It contains bilingual speaker notes. It is not the student's completed
final slide submission.

The course explicitly requires student-created slides. Create the final slides
from your own understanding, add them here, and use the same final deck for the
recording and the live presentation. Do not label this reference deck as
independently student-created work.

The eight pages keep audience questions separate from their answers:

1. The question: can the same pixels occupy fewer bytes?
2. Question: how would you describe the pixel row? No encoded answer is shown.
3. Reveal: four count-value pairs use 8 bytes instead of 32.
4. Decoding and exact reconstruction.
5. Question: will an alternating row become smaller, stay the same, or grow?
6. Reveal: 32 pairs use 64 bytes; the payload doubles.
7. Three 12 × 12 patterns with different encoded sizes.
8. The role of long runs and the connection to C arrays.

Pause for 5–10 seconds on pages 2 and 5, let the audience respond, then advance.
The question titles do not disclose the answer. These two added pages are reveal
steps, not additional topics. Rehearse the entire talk to keep it within 5–7 minutes.

The repository adds two useful questions for discussion without requiring a
longer main talk: why total frequencies are insufficient, and what happens
when a run exceeds 255 values. See the code walkthrough and experiment output.

No recording is included yet. The recording must be the student's own complete
5–7 minute presentation and must be submitted before the scheduled checkoff.
