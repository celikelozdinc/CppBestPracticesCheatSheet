#include <iostream>
#include <initializer_list>

/**
 * C++ Initialization Story
 * Example 9.4
 */
class X {
public:
    explicit X(size_t cnt) : _count{cnt} {
        std::cout << "1 => X(size_t cnt)" << '\n';
    }
    X() {
        std::cout << "2 => X()" << '\n';
    }
    X(std::initializer_list<int> list) : _count{list.size()} {
        std::cout << "3 => X(std::initializer_list<int>)" << '\n';
    }

private:
    size_t _count{};
};

/**
 * C++ Initialization Story
 * Example 9.7
 */
struct Value {
    Value(int v) : _v{v} {
        std::cout << "Construct Value at : " << (void*)(this) << '\n';
    }
    int _v{};
};

int main() {
    X x1;               //=> 2
    X x2{};             //=> 2
    X x3{1};            //=> 3
    X x4(1);        //=> 1
    X x5{1, 17, 41};    //=> 3
    return EXIT_SUCCESS;
}