#!/usr/bin/gawk -f
BEGIN { out = "" } 
{ gsub("¢","") }
/\\begin{LIBRARY}/ { out = sprintf("library%02d.lisp", ++library); next; }
/\\begin{LISP}/ { out = sprintf("lisp%02d.lisp", ++lisp); next; }
/\\begin{KERNEL}/ { out = sprintf("kernel%02d.lisp", ++kernel);next;  }
/\\end{LIBRARY}/  { out = ""; next; } 
/\\end{LISP}/  { out = "";next;  } 
/\\end{KERNEL}/  { out = "";next;  } 
out == "" { next }
/\( *n?defun/ { 
  if (out == "") next;
  name = $0;
  gsub("[()]"," ",name);
  split(name,words);
  name = words[2]
  while (name in names)
    name = name "x" 
  names[name]++
  out = name ".lisp";
}
out != "" { 
  printf("%s\n",$0)>out 
}
