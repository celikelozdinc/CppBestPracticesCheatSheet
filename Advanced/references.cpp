#include <utility>
#include <type_traits>
#include <iostream>

template <typename T>
void printvalcat() {
  if constexpr(std::is_rvalue_reference_v<T>) {
    std::cout << "XVALUE\n";
  } else if constexpr (std::is_lvalue_reference_v<T>) {
    std::cout << "LVALUE\n";
  } else if constexpr (!std::is_reference_v<T>) {
    std::cout << "PRVALUE\n";
  } else {
    std::cout << "UNDEFINED VALUE CATEGORY\n";
  }
}

template <typename T>
void fum(T, T&&) {
  std::cout << "(T, T&&)\n";
}

template <typename T>
void zoot(T&, T&&) {
  std::cout << "(T, T&&)\n";
}

template <typename T>
void quux(T, T&) {
  std::cout << "(T, T&)\n";
}

template <typename T>
void noot(T, const T&) {
  std::cout << "(T, const T&)\n";
}


int foo();
int& bar();
int&& baz();

struct Widget{};

/**
 * Nec C++ Quiz — 0043
 * https://necatiergin2019.medium.com/nec-c-quiz-0043-e484ffcffb97
 * @return
 */
int main () {
  int x{}, y{};
  Widget w1{}, w2{};
  std::cout << "***************1******************\n";
  printvalcat<decltype((x))>();
  printvalcat<decltype((y))>();
  //fum(x,y); //1  =>can be bound to (int&, int&)
  quux(x, y);
  std::cout << "***************1******************\n";
  std::cout << "***************4******************\n";
  int* ptr = &x;
  printvalcat<decltype((ptr))>();
  printvalcat<decltype((&x))>();
  printvalcat<decltype((&y))>();
  printvalcat<decltype((int{}))>();
  printvalcat<decltype((int{}))>();
  fum(&x, &x);
  //zoot(&x, &y);
  fum(int{}, int{});
  //quux(&x, &y);
  noot(&x, &y);
  std::cout << "***************4******************\n";
  std::cout << "***************5******************\n";
  printvalcat<decltype(("bir"))>();
  printvalcat<decltype(("iki"))>();
  printvalcat<decltype((12))>();
  //fum("bir", "iki");
  std::cout << "***************5******************\n";
  std::cout << "***************6******************\n";
  printvalcat<decltype((std::move(x)))>();
  printvalcat<decltype((std::move(y)))>();
  fum(std::move(x), std::move(y));
  //quux(std::move(x), std::move(y));
  Widget&& wrr1 = Widget{}; //=> Materialization
  Widget&& wrr2 = std::move(w1);
  Widget w3 = std::move(w2);
  std::cout << "***************6******************\n";

  printvalcat<decltype((foo()))>();
  printvalcat<decltype((bar()))>();
  printvalcat<decltype((baz()))>();
}
