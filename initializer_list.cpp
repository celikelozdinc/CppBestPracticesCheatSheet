#include <iostream>
#include <initializer_list>
#include <vector>
#include <memory>

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
        std::cout << "Constructed Value at : " << (void*)(this) << '\n';
    }

    ~Value() {
        std::cout << "Destructed Value from : " << (void*)(this) << '\n';
    }

    Value(const Value& other) : _v{other._v} {
        std::cout << "Copy-Constructed Value at : " << (void*)(this) << ", from : " << (void*)(&other) << '\n';
    }

    Value(Value&& other) : _v{std::move(other._v)} {
        std::cout << "Move-Constructed Value at : " << (void*)(this) << ", from : " << (void*)(&other) << '\n';
    }

    int _v{};
};

int main() {
    std::cout << "/**********Example 9.4(test constructor with initializer_list)**********/\n";
    X x1;               //=> 2
    X x2{};             //=> 2
    X x3{1};            //=> 3
    X x4(1);        //=> 1
    X x5{1, 17, 41};    //=> 3
    std::cout << "/**********Example 9.4(test constructor with initializer_list)**********/\n";
    std::cout << "/**********Example 9.7(extra copy in initializer_list)**********/\n";
    {
        std::cout << "starting inner scope...\n";
        std::cout << "with initializer_list...\n";
        std::vector<Value> vec1{17, 41};
        std::vector<Value> vec2{};
        vec2.reserve(4);
        std::cout << "with emplace...\n";
        vec2.emplace_back(1);
        vec2.emplace_back(7);
        std::cout << "with push...\n";
        vec2.push_back(4);
        vec2.push_back(1);
        std::cout << "ending inner scope...\n";
    }
    std::cout << "/**********Example 9.7(extra copy in initializer_list)**********/\n";
    std::cout << "/**********Example 9.8(non-copyable types)**********/\n";
    //std::vector<std::unique_ptr<int>> uPtrs = {
    //        std::make_unique<int>(17),
    //        std::make_unique<int>(41)
    //};
    //std::vector<std::unique_ptr<int>> uPtrs(2); //=> Fill c'tor
    std::vector<std::unique_ptr<int>> uPtrs;
    uPtrs.reserve(2);
    std::cout << "Capacity of uPtrs: " << uPtrs.capacity() << '\n';
    std::cout << "Size of uPtrs: " << uPtrs.size() << '\n';
    uPtrs.emplace_back(std::make_unique<int>(17));
    uPtrs.emplace_back(std::make_unique<int>(41));
    std::cout << "Capacity of uPtrs: " << uPtrs.capacity() << '\n';
    std::cout << "Size of uPtrs: " << uPtrs.size() << '\n';
    std::cout << "/**********Example 9.8(non-copyable types**********/\n";
    return EXIT_SUCCESS;
}