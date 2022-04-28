#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <unordered_set>

constexpr int sq(int x) {return x*x;}

template <typename Container>
void print_elements(Container C) {
    for (const auto& item : C) {
        std::cout << '{' << item << '}' << "\n";
    }
    std::cout << "Bucket Count : " << C.bucket_count() << "\n";
}

int main() {
    /*************************** Type Traits **********************/
    typedef int Integer;
    //typedef std::add_const<Integer>::type CI;
    typedef std::add_const_t<Integer> CI;

    // Is const?
    std::cout << "IS CONST? : " << std::boolalpha << std::is_const<Integer>::value <<"\n";

    // Add Const
    std::cout << "const int == CI ? " << std::boolalpha << std::is_same<const int, CI>::value << "\n";
    std::cout << "int == CI ? " <<std::boolalpha << std::is_same<int, CI>::value << "\n";
    //std::cout << typeid(int).name() << "\n";  //=> gives compiler-dependent output
    //std::cout << typeid(Integer).name() << "\n";  //=> gives compiler-dependent output
    //std::cout << typeid(CI).name() << "\n";  //=> gives compiler-dependent output

    // Remove Const
    typedef std::remove_const_t<CI> I;
    std::cout << "const int == I ? " << std::boolalpha << std::is_same<const int, I>::value << "\n";
    std::cout << "int == I ? " << std::boolalpha << std::is_same<int, I>::value << "\n";
    /**************************************************************/
    /*****************  constexpr  ********************************/
    int a = 10;
    //static_assert(100 == sq(a), "WRONG!"); //=> non-constant condition for static assertion
    constexpr int b = 10;
    static_assert(100 == sq(b), "WRONG!"); //=> non-constant condition for static assertion
    int arraySq[sq(2)];
    int arraySquare[sq(b)];
    /**************************************************************/
    /******************  Associative Containers********************/
    using Set = std::unordered_set<std::string>;
    using MultiSet = std::unordered_multiset<std::string>;
    Set set{"bin", "root"};
    std::cout << "Set before insertions: \n";
    print_elements(set);

    std::cout << "Set after some inserts: \n";
    set.insert({"etc", "tmp"});
    print_elements(set);

    auto varIter = set.find("var");
    if (set.end() != varIter) {
        std::cout << "Found {var} in set: " << *varIter << "\n";
    } else {
        std::cout << "Could not find {var} in set\n";
    }
    auto binIter = set.find("bin");
    if (set.end() != binIter) {
        std::cout << "Found {bin} in set: " << *binIter << "\n";
    } else {
        std::cout << "Could not find {bin} in set\n";
    }

    MultiSet multiSet{"grimm", "jaud-grimm"};
    std::cout << "MultiSet before insertions: \n";
    print_elements(multiSet);

    multiSet.insert({"grimm", "djikstra"});  //=> Accepts initializer list
    std::cout << "MultiSet after some inserts: \n";
    print_elements(multiSet);

    std::cout << "Multiset.count(grim) : " << multiSet.count("grim") << "\n";
    std::cout << "Multiset.count(djikstra) : " << multiSet.count("djikstra") << "\n";
    std::cout << "Multiset.count(grimm) : " << multiSet.count("grimm") << "\n";
    auto iter = multiSet.equal_range("grimm");
    std::cout << "Searching for grimm in multiset: \n";
    for (auto it = iter.first ; it != iter.second; ++it) {
        std::cout << *it << "\n";
    }
    /**************************************************************/
}