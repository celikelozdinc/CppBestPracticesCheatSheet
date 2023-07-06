#include <iostream>


/**
 * How to force RVO before C++17 : https://fekir.info/post/how-to-force-return-value-optimization/
 * cpp reference : https://en.cppreference.com/w/cpp/language/copy_elision
 * Guaranteed copy elision : https://jonasdevlieghere.com/post/guaranteed-copy-elision/
 */
struct Noisy {
  Noisy() { std::cout << "Default constructed at : " << this << "\n"; }
  Noisy(const Noisy&) {std::cout << "Copy constructed at " << "\n";}
  Noisy(Noisy&&) noexcept {std::cout << "Move constructed at " << "\n";}
  ~Noisy() { std::cout << "Destructed from : " << this << "\n"; }
  uint32_t member;
};


/**
 * RVO
 * @return Noisy
 */
Noisy zoot() {
  return Noisy{};
}

/**
 * NRVO
 * @return Noisy
 */
Noisy quux() {
  Noisy n{};
  return n;
}

int main () {
  Noisy n1 = zoot();
  Noisy n2 = quux();
  const Noisy& cn = Noisy{}; //=> Materialization
  Noisy&& rn = Noisy{}; //=> Materialization
  return EXIT_SUCCESS;
}