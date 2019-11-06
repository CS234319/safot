% rm -f make-hello-caml.c
cat << EOF > make-hello-caml.c
#include <stdio.h>
int main(int argc, char *argv[], char **envp) {
  printf("printₛtring \"Hello, World!\protect \begingroup \immediate \write \@unused   \def \MessageBreak  
 \let \protect \edef  Your command was ignored.\MessageBreak Type  I <command> <return>  to replace it with another command,\MessageBreak or  <return>  to continue without it.  \errhelp \let \def \MessageBreak  
                \def   \errmessage  LaTeX Error: There's no line here to end.

See the LaTeX manual or LaTeX Companion for explanation.
Type  H <return>  for immediate help   \endgroup \par \let \reserved@d = *\def \begingroup \def ##1,{}\toks@ {{}{},}\edef {setentrycounter[]{page}\glsnumberformat\@nil }\endgroup \let  
