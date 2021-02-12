#define BT_BUF_SIZE 100

#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
void stack_trace(void) {
  int nptrs;
  void *buffer[BT_BUF_SIZE];
  char **strings;

  nptrs = backtrace(buffer, BT_BUF_SIZE);
  printf("backtrace() returned %d addresses\n", nptrs);

  /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
   would produce similar output to the following: */

  strings = backtrace_symbols(buffer, nptrs);
  if (strings == NULL) {
    perror("backtrace_symbols");
    exit(EXIT_FAILURE);
  }

  for (int j = 0; j < nptrs; j++)
    printf("%s\n", strings[j]);

  free(strings);
  exit(3);
}
