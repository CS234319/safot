#include "recorder.h"

String Recorder::playback() { return (char *)(tape); }
char *Recorder::head() { return length+(char *)(tape); }
void Recorder::start() { if (tape == 0) tape = malloc(1); length = 0; }

void Recorder::record(String s) {
  if (tape == (void *) 0) return;
  H n = size(s);
  tape = realloc(tape, length + n);
  for (int i = 0; i <= n; ++i, ++length) 
    *head() = s[i];
  D(n, s, tape, length, playback());
}
