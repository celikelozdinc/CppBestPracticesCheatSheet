#include <utility>
#include <type_traits>
#include <iostream>
#include <string>
#include <string_view>

#include "value_categories.h"

/**
 * An expression’s value category
 * determines what references the expression may initialize
 * T& can be initialized only from lvalues
 * T&& can be initialized only from rvalues
 * const T& can be initialized from any value category
 *      but overload resolution will prefer
 *      T&& over const T& for rvalues if there are functions accepting both
 *          This is why copy constructors can fill the role of a missing move constructor.
 *  The reference binding rules mostly explain which functions can be selected in overload resolution for arguments of what value category.
 */

template <typename T>
void fum(T arg1, T &&arg2) {
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
 * https://www.scs.stanford.edu/~dm/blog/decltype.pdf
 */
int main () {
  using namespace std::literals;
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
  std::cout << "std::string{''}->\t"; printvalcat<decltype((std::string{"literal"}))>();
  std::cout << "'literal's->\t\t"; printvalcat<decltype(("literal"s))>();
  std::cout << "'literal'sv->\t\t"; printvalcat<decltype(("literal"sv))>();
  std::cout << "'literal'->\t\t"; printvalcat<decltype(("literal"))>();
  std::cout << "std::terminate()->\t"; printvalcat<decltype((std::terminate()))>();
  auto a{17};
  int& ref2a = a;
  std::cout << "a->\t\t"; printvalcat<decltype(a)>();
  std::cout << "(a)->\t\t"; printvalcat<decltype((a))>();
  std::cout << "ref2a->\t\t"; printvalcat<decltype((ref2a))>();
  std::cout << "true->\t\t"; printvalcat<decltype((true))>();
  std::cout << "nullptr->\t"; printvalcat<decltype((nullptr))>();

}
