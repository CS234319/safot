#include <stdio.h>
int main(int argc, char *argv[], char **envp) {
  printf(
    "program HelloWorld(output);\n"
    "begin\n"
    " WriteLn('Hello, World!')\n"
    "end.\n");
  return 0;
}
