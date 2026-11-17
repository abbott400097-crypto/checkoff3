# References

## Assignment

- [COMP211 Checkoff 3 instructions](https://docs.google.com/document/d/1pxvinVMAO8EKpSBYEjUCgU1Wm3C98W6AxTNVgyClTJg/edit).
  RLE appears under Data Representation → Data Compression. The instructions
  specify the presentation, recording, public repository, AI reflection,
  conversation permalink, and student-created-slide requirements.

## Real RLE formats

- [Microsoft: Bitmap Compression](https://learn.microsoft.com/en-us/windows/win32/gdi/bitmap-compression).
  A reference for how RLE appears in a real bitmap format. The small encoder in
  this repository does not implement the full BMP format.
- [DICOM: The RLE Algorithm](https://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_G.3.html).
  A reference showing another concrete RLE encoding scheme. It should not be
  confused with this project's fixed count-value pair format.

## Experiments and AI assistance

- Size results in the README come from the repository's own deterministic
  inputs and C experiment. See [results.txt](results.txt).
- AI-assisted explanations and question excerpts are documented in
  [AI-CONVERSATION.md](AI-CONVERSATION.md).
- The pixel patterns are project demonstration data, not measurements of
  compressed PNG, BMP, or DICOM files.

