#include <iostream>
#include <string>

struct MyStruct {
    int i;
    std::string s;
};

/**
 * Structured bindings with move semantics
 * @return
 */
int main() {
    MyStruct ms1{42, "Jim"};
    MyStruct ms2{34, "Ali"};
    std::boolalpha(std::cout);
    std::cout << "***************1******************\n";
    {
        auto&& [i,s] = std::move(ms1);//ms still holds its value
        std::cout << "s -> " << s << '\n';
        std::cout << "ms1.s -> " << ms1.s << '\n';
        std::string movedS = std::move(s);
        std::cout << "After moving:\n";
        std::cout << "\ts -> " << s << '\n';
        std::cout << "\ts.size() -> " << s.size() << '\n';
        std::cout << "\ts.empty() -> " << s.empty() << '\n';
        std::cout << "\tms1.s -> " << ms1.s << '\n';
        std::cout << "\tmovedS -> " << movedS << '\n';
    }
    std::cout << "***************1******************\n";

    std::cout << "***************2******************\n";
    {
        auto [i,s] = std::move(ms2);//ms already lost its value
        std::cout << "s -> " << s << '\n';
        std::cout << "ms2.s -> " << ms2.s << '\n';
        std::string movedS = std::move(s);
        s.assign("Lara");
        std::cout << "After moving:\n";
        std::cout << "\ts -> " << s << '\n';
        std::cout << "\tms2.s -> " << ms2.s << '\n';
        std::cout << "\tmovedS -> " << movedS << '\n';

    }
    std::cout << "***************2******************\n";

    return EXIT_SUCCESS;
}