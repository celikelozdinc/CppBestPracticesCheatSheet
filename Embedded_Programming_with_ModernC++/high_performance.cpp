#include <type_traits>
#include <typeinfo>
#include <iostream>

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

}