#ifndef RECORDER_H
#define RECORDER_H
#ifndef PRODUCTION
#include "hacks.h"
#include "mode.h"
struct Recorder {
  void *tape = (void *) 0; 
  int length = 0;
  String playback();
  char *head();
  void start();
  void record(String s); 
};
#endif
#endif
