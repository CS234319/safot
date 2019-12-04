% rm -f make-hello-caml.c
cat << EOF > make-hello-caml.c
#include <stdio.h>
int main(int argc, char *argv[], char **envp) {
  printf("printₛtring \"Hello, World!\protect \let \relax \let \reserved@f \relax \let \reserved@d = *\def \begingroup \def ##1,{}\toks@ {{}{},}\edef {setentrycounter[]{page}\glsnumberformat\@nil }\endgroup \let  
