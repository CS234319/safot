#import "chic.h"
#import "Word.h"
Type Handle { // A handle of an S-Expression
  Constructor(Handle(Short));
  Property(Boolean ok); 
  Property(Short handle); 
  Property(Word& p); 
  Property(Text a); 
  private: struct { Short capsule; }; 
};
