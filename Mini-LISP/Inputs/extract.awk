#!/usr/bin/gawk -f
out != "" { printf("%s\n",$0)>out }
/\\begin{LIBRARY}/ { out = sprintf("library%02d.lisp", ++library); }
/\\begin{LISP}/ { out = sprintf("lisp%02d.lisp", ++lisp); }
/\\begin{KERNEL}/ { out = sprintf("kernel%02d.lisp", ++kernel); }
/\\end{LIBRARY}/  { out = ""; } 
/\\end{LISP}/  { out = ""; } 
/\\end{KERNEL}/  { out = ""; } 
