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
  printvalcat<decltype((x))>(); //=> LVALUE
  printvalcat<decltype((y))>(); //=> LVALUE
  //fum(x,y); //1  =>can be bound to (int&, int&)
  quux(x, y);
  std::cout << "***************1******************\n";
  std::cout << "***************4******************\n";
  int* ptr = &x;
  printvalcat<decltype((ptr))>(); //=> LVALUE
  printvalcat<decltype((&x))>(); //=> PRVALUE
  printvalcat<decltype((&y))>(); //=> PRVALUE
  printvalcat<decltype((int{}))>(); //=> PRVALUE
  fum(&x, &x);
  //zoot(&x, &y);
  fum(int{}, int{});
  //quux(&x, &y);
  noot(&x, &y);
  std::cout << "***************4******************\n";
  std::cout << "***************5******************\n";
  /**
   *  All the literals, except from the string literals
   *  are PRValues
   */
  printvalcat<decltype(("bir"))>(); //=> LVALUE
  printvalcat<decltype(("iki"))>(); //=> LVALUE
  printvalcat<decltype((12))>(); //=> PRVALUE
  //fum("bir", "iki");
  std::cout << "***************5******************\n";
  std::cout << "***************6******************\n";
  printvalcat<decltype((std::move(x)))>(); //=> XVALUE
  printvalcat<decltype((std::move(y)))>(); //=> XVALUE
  fum(std::move(x), std::move(y));
  //quux(std::move(x), std::move(y));
  Widget&& wrr1 = Widget{}; //=> Materialization
  Widget&& wrr2 = std::move(w1);
  Widget w3 = std::move(w2);
  std::cout << "***************6******************\n";

  std::cout << "foo() ->\t"; printvalcat<decltype((foo()))>();
  std::cout << "bar() ->\t"; printvalcat<decltype((bar()))>();
  std::cout << "baz() ->\t"; printvalcat<decltype((baz()))>();
  std::cout << "x+5 ->\t"; printvalcat<decltype((x+5))>(); //=> PRVALUE
  std::cout << "x++ ->\t"; printvalcat<decltype((x++))>(); //=> PRVALUE
  std::cout << "--x ->\t"; printvalcat<decltype((--x))>(); //=> LVALUE
  std::cout << "std::string{''} ->\t"; printvalcat<decltype((std::string{"literal"}))>();
  std::cout << "'literal' ->\t"; printvalcat<decltype(("literal"))>();
}
