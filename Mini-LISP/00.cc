#include "repl.h"

int main(int argc, char **argv) {
  printf("Read, evaluated, and printed successfully %d expressions\n", REPL((char *)0));
  printf("Good bye!\n");
  return 0;
}
