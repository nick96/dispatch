#include <criterion/criterion.h>

Test(sample, test1) {
  cr_expect(1 == 1, "Expected 1 == 1");
}


Test(sample, test2) {
  cr_expect(1 == 2, "Expected 1 == 2");
}
