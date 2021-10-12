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
  print $0>>out 
}

function start(outputName) {
  out = outputName;
  header = location();
  next;
}

function end() {
  print location() >> out
  out = ""; next
}

function location(result) {
  extracted = sprintf("; %s(%d)", inputName(),FNR) 
  result = result padding(extracted)  "\n"
  result = result extracted  "\n"
  result = result padding(extracted)
  return result;
}

function inputName() {
  gsub(/^[\.\/]*/, "", FILENAME) 
  return FILENAME
}



function padding(s,i, result) {
  result = "";
  for (i = 0; i < length(s); i++)
    result = result ";"
  return result; 
}


