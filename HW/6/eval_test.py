from eval import *

a_list = make_a_list()

a_list.append(("T", T))
a_list.append(("NIL",NIL))

assert eval(a_list, ["DEFUN", "myfunc", [], "T"]) == eval(a_list, ["QUOTE", ["LAMBDA", [], "T"]])
assert eval(a_list, ["myfunc"]) == S_Atom(value='T')

assert eval(a_list, ["DEFUN", "conslike", ["x", "y"], ["cons", "x", "y"]]) == eval(a_list, ["QUOTE", ["LAMBDA", ["x", "y"], ["cons", "x", "y"]]])
assert eval(a_list, "conslike") == eval(a_list, ["QUOTE", ["LAMBDA", ["x", "y"], ["cons", "x", "y"]]])
assert eval(a_list, ["conslike", ["QUOTE", "x"], ["QUOTE", "y"]]) == S_Cons(car=S_Atom(value='X'), cdr=S_Atom(value='Y'))

assert len(a_list) == 4
