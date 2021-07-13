#include "basics.h"
#include "parser.h"

static inline auto prompt(String s) {
  fputs(s, stdout);
}

int print(String s) {
    return fputs(s,stdout);
}

// Use to print the error code number
int print(int num) {
    char char_arr[100];
    sprintf(char_arr, "%d", num); // itoa
    return print(char_arr);
}

int print(S s);

auto print(H h) {
  return print(S(h));
}

auto print(Pair p) {
   return print("["), print( p.car), print("."), print( p.cdr), print("]");
}

int print(S s) {
  if (s.null())
    return print("NIL");
  if (s.atom())
    return print( s.asAtom());
  if (!islist(s)) 
    return print("("), print( s.car()), print("."), print( s.cdr()), print(")");
  print("(") ;
  for (;;) {
    print(S(s.car())); 
    if ((s = s.cdr()).null())
      break;
    print(" ");
  }
  return print(")");
}

extern S alist ;

// Check if the string is balance, use to support multi-line input in RELP:
bool is_balance(const char* input) {
    bool balance = true;
    int count = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(') count++;
        if (input[i] == ')') count--;
        if (count < 0) return false;
    }
    return count == 0;
}

// Parse line, allow multi-line (e.g: "(car \n\n '(a.b)\n)")
void get_input(char * line) {
    line[0] = '\0';
    int i = 0;
    while(true) {
        char c = getchar();
        if ((c == '\n' && is_balance(line)) || c == EOF)
            break;
        line[i++] = c;
        line[i] = '\0';
    }
}

// Realizes the famous "Read, Evaluate, Print, Loop" of interpreters
static int REPL() {
  static size_t max_size = 1<<12;
  static char * line = (char *) malloc (max_size);
  using namespace Parser;

  Start:
    reset();
    prompt("> ");
  Read:
    get_input(line);
    supply((char*)line);
    switch (status()) {
      case ready:
        prompt("- ");
        goto Read;
      case accept:
        break;
      case reject:
        prompt("?");
        goto Start;
    }
  Eval:
    S res = S("");
    const S saved_alist = alist;
    try {
       const S e = result().eval();
       res = e;
    } catch (Pair error) {
      print("Error");
      print(error.car);
      print(error.cdr);
      alist = saved_alist; // Restore a-list in case of error
    }
  Print:
    print(res), print("\n");
  Loop:
    goto Start;
}

int main(int argc, char **argv) {
    try {
        return REPL();
    } catch (int error) {
        print("ERROR: Unexpected exception caught");
        print(error);
        print("\n");
    }
}
