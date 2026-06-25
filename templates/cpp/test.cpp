#include "__TYPE__/__NAME__.hpp"
#include <iostream>

#define RUN_TEST(test_func)                                                                        \
  do {                                                                                             \
    std::cout << "[ RUNNING ] " << #test_func << "...\n";                                          \
    test_func();                                                                                   \
    std::cout << "[ PASSED  ] " << #test_func << "\n\n";                                           \
  } while (0)

int main() {
  std::cout << "Testing __NAME__...\n\n";

  std::cout << "All tests passed for __NAME__\n";
  return 0;
}
