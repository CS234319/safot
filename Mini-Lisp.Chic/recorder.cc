#include "recorder.h"
#include <stdlib.h>
Recorder Recorder::stdout, Recorder::stderr; 
String Recorder::playback() { return (char *)(tape); }
char *Recorder::head() { return length+(char *)(tape); }
void Recorder::reset() { 
  if (tape != 0) free(tape), tape = 0;
  tape = malloc(1),  length = 0, *head() = '\0';
}
void Recorder::record(String s) {
  if (tape == 0) return;
  const H n = size(s);
  tape = realloc(tape, length + n);
  for (H i = 0; i < n; ++i, ++length) 
    *head() = s[i];
  --length;
}
