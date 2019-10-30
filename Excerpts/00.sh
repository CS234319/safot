% cat << EOF > echo.c
#include <stdio.h>

typedef char *strings_t[];

void print_strings(strings_t ss) {
  for (; *ss; ss++)
    printf("%s ", *ss);
  printf("\n");
}

int main(int argc, char *argv[], char **envp) {
  print_strings(argv);
  print_strings(envp);
  return 0;
}
EOF
