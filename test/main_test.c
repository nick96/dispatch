#include <stdio.h>

#include "minunit.h"

int tests_run = 0;

char *test_1() {
    mu_assert("error, 1 != 1", 1 == 1);
    return 0;
}

char *run_all_tests() {
    mu_run_test(test_1);
    return 0;
}

int main(int argc, char *argv[]) {
    char *res = run_all_tests();
    if (res) {
        printf("%s\n", res);
    } else {
        printf("All tests passed");
    }
    printf("Tests run: %d\n", tests_run);
    return res != 0;
}
