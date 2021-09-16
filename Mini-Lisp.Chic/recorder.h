#ifndef RECORDER_H
#define RECORDER_H
#include "hacks.h"
#ifndef PRODUCTION
struct Recorder {
  void reset();
  void record(String s); 
  String playback();
  static struct Recorder stdout, stderr;
  private:
    char *head();
    void *tape = (void *) 0; 
    int length = 0;
};
#endif
#endif
