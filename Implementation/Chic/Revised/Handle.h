#import "chic.h"
#import "Word.h"
Type Handle { // A handle of an S-Expression
  Constructor(Handle(Short));
  Property(Boolean ok) below
  Property(Short handle) below 
  Property(Word& cons) below
  Property(Text text) below 
  private: struct { Short capsule; }; 
};
