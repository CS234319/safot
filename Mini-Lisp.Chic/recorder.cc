#include "recorder.h"

String Recorder::playback() { return (char *)(tape); }
char *Recorder::head() { return length+(char *)(tape); }

void Recorder::start() { 
  if (tape == 0) 
    tape = malloc(1); 
  length = 0; 
  *head() = '\0';
}

static void record(String s) {
  if (file == stdout) 
    rout.record(s);
  else
    rerr.record(s);
}

namespace Printing { 
  void record() { rout.start(); } 
  String playback() { return rout.playback(); }
};

namespace Erroring { 
  void record() { rerr.start(); } 
  String playback() { return rerr.playback(); }
};
