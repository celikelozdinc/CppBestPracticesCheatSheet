#include <iostream>
// FWD Declarations
class Container;
Container MakeContainer();

class Container {
public:
  Container() : member{17} {std::cout << "Container::Container()" << "\n";}
  ~Container() {std::cout << "Container::~Container()" << "\n";}

  Container(const Container& other) : member{other.member}
  {
    std::cout << "Container::Container(const Container&)" << "\n";
  }
  Container(Container&& other) noexcept  : member{std::move(other.member)}
  {
    std::cout << "Container::Container(Container&&)" << "\n";
  }

  Container& operator=(const Container& other)
  {
    std::cout << "Container::operator=(const Container&)" << "\n";
    this->set_mem(other.member);
    return *this;
  }
  Container& operator=(Container&& other) noexcept {
    std::cout << "Container::operator=(Container&&)" << "\n";
    this->set_mem(other.member);
    return *this;
  }

  void set_mem(uint64_t t_mem) const noexcept {
    std::cout << "set_mem()::Before modification : " << member << "\n";
    member = t_mem;
    std::cout << "set_mem()::After modification : " << member << "\n";
  }

  uint64_t get_mem() const {
    return member;
  }
private:
  /**
   * Permits modification of the class members
   * even if the containing object is declared as const
   */
  mutable uint64_t member;
};

/** Lifetime extension of temporary objects
 *  https://pvs-studio.com/fr/blog/posts/cpp/1006/
 *  @return
 */
Container MakeContainer() {
  Container c{};
  c.set_mem(44);
  return c;
}

/**
 * Constant
 * Temp variables
 */
void process(const Container& c) {
  std::cout << "process()::Member of the container : " << c.get_mem() << "\n";
}

int main() {
  const Container& cnt = MakeContainer();
  //Container& cntnr = MakeContainer(); //=> cannot bind non-const lvalue reference of type ‘Container&’ to an rvalue of type ‘Container’
  cnt.set_mem(144);
  Container&& rValRefCnt = MakeContainer();
  rValRefCnt.set_mem(41);
  process(cnt);
  process(Container{});
  return EXIT_SUCCESS;
}