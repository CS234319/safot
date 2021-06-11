#include <stdio.h>

static const int π = 3;

int get_naïve_pi() {
    return π;
}

int main(void) {
    printf("%d\n", get_naïve_pi());
    return 0;
}
