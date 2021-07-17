#!/usr/bin/gawk -f
/\\begin{LIBRARY}/ { out = sprintf("library%02d.lisp", ++library); next; }
/\\begin{LISP}/ { out = sprintf("lisp%02d.lisp", ++lisp); next; }
/\\begin{KERNEL}/ { out = sprintf("kernel%02d.lisp", ++kernel);next;  }
/\\end{LIBRARY}/  { out = ""; next; } 
/\\end{LISP}/  { out = "";next;  } 
/\\end{KERNEL}/  { out = "";next;  } 
out != "" { printf("%s\n",$0)>out }
