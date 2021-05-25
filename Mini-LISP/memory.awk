#!/usr/bin/gawk -f
/documentclass/,/begin{document}/ {}
/end{code}/,/begin{code}/ {}
