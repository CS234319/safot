#include "S.h"
#include "stack-trace.h"
#define PRODUCTION
#include "mode.h"

/* Global memory layout; we use no dynamic allocation of the host language.
 * TODO: deal with memory exhausting */

namespace Pairs {
  define(M = (1 << 15) - 1)
  // Falls in the data segment;
  static Pair buffer[M];
  Pair *const pool = buffer - 1;
  static H remaining = M;
  extern H to_go() {
    return remaining;
  }

  Pair &get(H h) {
    return pool[h];
  }

  static H init() {
    for (H h = 1; h < M; ++h)
      pool[h].next = h + 1;
    pool[M].next = 0;
    return 1;
  }

  static H &next() {
    static H inner = init();
    return inner;
  }


  H allocate() {
    D(next(), remaining);
    remaining > 0 || die(EXHAUSTED);
    next() != 0 || die(EXHAUSTED);;
    const H $ = next();
    remaining--, next() = pool[next()].next;
    D($, next(), remaining);
    return $;
  }

  H allocate(H car, H cdr) {
    D(next(), car, cdr, remaining);
    H $ = allocate();
    D(next(), car, cdr, remaining);
    pool[$].car = car;
    pool[$].cdr = cdr;
    //D($,pool[$].car,pool[$].cdr, S($), S(pool[$].car), S(pool[$].cdr));
    D($);
    return $;
  }

  void free(H h) { D(h, remaining);
    pool[h].next = next(), remaining++, next() = h;
  }
}

