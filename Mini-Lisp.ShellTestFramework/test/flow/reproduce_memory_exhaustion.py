"""
Reproduction of memory exhausted bug (issue-456)
"""
from framework.lib.utils import get_env, generate_input_file, generate_book_files

if __name__ == '__main__':
    generate_book_files()
    env = get_env()
    alist = "(a.a t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote a) (quote {alist})) '({env}))"
    file = generate_input_file(f"{s_expr}\n{s_expr}\n{s_expr}\n")
    print(file)
