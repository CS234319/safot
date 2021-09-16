#ifndef RECORDER_H
#define RECORDER_H
#include "hacks.h"
struct Recorder {
  void reset();
  String playback();
  void record(String s); 
  private:
    char *head();
    void *tape = (void *) 0; 
    int length = 0;
 };
extern struct Recorder rout, rerr;
#endif

