#!/usr/bin/gawk -f
BEGIN { out = "" } 
{ gsub("¢","") }
/\\begin{LIBRARY}/ { start(sprintf("library%02d.lisp", ++library)) }
/\\begin{LISP}/ { start(sprintf("excerpt%02d.lisp", ++lisp))  }
/\\begin{KERNEL}/ { start(sprintf("kernel%02d.lisp", ++kernel)) }
/\\end{LIBRARY}/  { end() } 
/\\end{LISP}/  { end()  } 
/\\end{KERNEL}/  { end()  } 
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
  if (header != "") {
    print header >> out;
    header = "";
  }
  printf("%s\n",$0)>out 
}
function start(outputName) {
  out = outputName;
  header = ""
  header = header ";;;;;;;;;;;;;;;;;;;;\n" 
  header = header sprintf("; %s(%d) \n", origin(),NR) 
  header = header ";;;;;;;;;;;;;;;;;;;;" 
  next;
}
function origin(temp) {
  temp = FILENAME
  gsub(/^[\.\/]*/, "", temp) 
  return temp;
}
function end() {
  out = ""; next
}
