#include <iostream>
#include <ostream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <functional>
#include <initializer_list>

struct InitializationData{
    InitializationData(std::initializer_list<int>) {
        std::cout << "InitializationData(std::initializer_list<int>)\n";
    }
};

namespace Distance {
    class MyDistance {
    public:
        MyDistance(double i) : m{i} {}
        friend std::ostream& operator<< (std::ostream& out, const MyDistance& dist) {
            out << dist.m << " m";
            return out;
        } 
    private:
        double m; //meter
    };
    namespace Unit {
        MyDistance operator"" _km(long double d) {
            return MyDistance(1000*d);
        }
        MyDistance operator"" _m(long double m) {
            return MyDistance(m);
        }

        MyDistance operator"" _cm(long double c) {
            return MyDistance(c/100);
        }

        MyDistance operator"" _ft(long double f) {
            return MyDistance(f*0.3048);
        }

        MyDistance operator"" _mi(long double mi) {
            return MyDistance(mi*1609.344);
        }
    }
}

using namespace Distance::Unit;

int main() {
    /*************************** Uniform initialization with {}**********************/
    InitializationData data1{-10, 5, 1, 4, 5};
    InitializationData data2 = {-10, 5, 1, 4, 5};
    std::vector<int> vec{-10, 5, 1, 4, 5};
    std::array<int, 5>  arr{-10, 5, 1, 4, 5};
    std::set<int> mySet{-10, 5, 1, 4, 5};  //=> duplicates will not be inserted
    for (auto& elem : mySet) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    /*********************************************************************************/
    /*****************************  Automatic type deduction: auto********************/
    std::initializer_list<int> myInts = {1, 2, 3};
    std::initializer_list<int>::const_iterator myIntBegin = myInts.begin();
    std::cout << *myIntBegin << "\n";

    std::map<int, std::string> myMap = {{1, std::string{"one"}}, {2, std::string{"two"}}};
    std::map<int, std::string>::const_iterator myMapBegin = myMap.begin();
    std::cout << (*myMapBegin).first << " -> " << (*myMapBegin).second << "\n";

    //auto func = [](const std::string& a) {return a;}
    std::function<std::string(const std::string&)> func = [](const std::string& a) {return a;};
    std::cout << func("XXxxXX") << "\n";

    std::pair<int, std::string> pa = std::make_pair(1, std::string("second"));
    //std::tuple<std::string, int, double, bool, char> tup = std::make_tuple(std:string("xxx"), 4, 1.1, true, 'a');
    /*********************************************************************************/
    /***************** User-Defined Literals : Introduction **************************/
    std::cout << "2.0_mi => " << 2.0_mi << "\n";
    std::cout << "1.0_mi => " << 1.0_mi << "\n";
    std::cout << "1.0_km => " << 1.0_km << "\n";
    std::cout << "1.0_m => " << 1.0_m << "\n";
    std::cout << "2.0_ft => " << 2.0_ft << "\n";
    std::cout << "1.0_ft => " << 1.0_ft << "\n";
    std::cout << "1.0_cm => " << 1.0_cm << "\n";
    /*********************************************************************************/

    return 0;
}