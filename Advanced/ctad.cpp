#include <iostream>
#include <vector>
#include <algorithm>

template <typename T, std::size_t SIZE>
struct ArrayWrapper {
  ArrayWrapper(const T(&)[SIZE]) {
      std::cout << "ArrayWrapper invoked with size : " << SIZE << '\n';
      if (std::is_same_v<T, double>){
          std::cout << "T is double(" << typeid(T).name() << ")\n";
      } else if (std::is_same_v<T, char>){
          std::cout << "T is char(" << typeid(T).name() << ")\n";
      } else if (std::is_same_v<T, const char>){
          std::cout << "T is const char(" << typeid(T).name() << ")\n";
      }
  }
};

template <typename CB>
class CountCalls {
public:
    CountCalls(CB cb) : _callback{cb} {
        std::cout << "CountCalls(CB)\n";
    }

    ~CountCalls() {
        std::cout << "~CountCalls()\n";
    }

    /**
     * member template
     */
    template <typename ...Args>
    auto operator() (Args... args) {
        _count += 1;
        return _callback(std::forward<Args>(args)...);
    }

    uint64_t count() {
        return _count;
    }
private:
    CB _callback;
    uint64_t _count{};
};

void counter(const double& d) {
    std::cout << d << " is the new item.\n";
}

struct InterfaceMocker {
    [[nodiscard]]
    bool operator() (int x) {
        _count += 1;
        std::cout << "InterfaceMocker::operator() is called with : " << x << '\n';
        return true;
    }

    ~InterfaceMocker() {
        std::cout << "Destructed from " << this << '\n';
    }

    static int _count;
};

int InterfaceMocker::_count{};

int main() {
    auto lambdaCB = CountCalls {
        [](const auto& item) {
            std::cout << "Item is : " << item << ", type id : " << typeid(item).name() << '\n';
        }
    }; //CTAD

    std::vector<double> dval(10, 1.7);

    std::cout << "***************1******************\n";
    const auto& cb = std::for_each(dval.begin(), dval.end(), std::ref(lambdaCB));
    std::cout << "Count : " << cb.get().count() << '\n';

    //auto cb = std::for_each(dval.begin(), dval.end(), callback);
    //std::cout << "Count : " << cb.count() << '\n';
    std::cout << "***************1******************\n";
    std::cout << "***************2******************\n";
    auto freeFuncCB = CountCalls {counter}; //CTAD
    auto&& cbb = std::for_each(dval.begin(), dval.end(), std::ref(freeFuncCB));
    std::cout << "Count : " << cbb.get().count() << '\n';
    std::cout << "***************2******************\n";
    std::cout << "***************3******************\n";
    //https://en.cppreference.com/w/cpp/utility/functional/function
    InterfaceMocker ifMocker = InterfaceMocker{};
    std::function<bool(int)> mocker{ifMocker}; //callable is wrapped
    mocker(10);
    mocker(100);
    mocker(50);
    std::cout << "Total count of invocations of mock object : "<< ifMocker._count << '\n';
    std::cout << "***************3******************\n";
    std::cout << "***************4******************\n";
    //https://github.com/necatiergin/CPP_KURSU_KODLAR/blob/main/0720_TEMPLATES_CTAD/ctad_11.cpp
    ArrayWrapper arr1{"ozdinc"}; //CTAD
    std::boolalpha(std::cout);
    std::cout << "Is arr1 has a type of ArrayWrapper<char, 7> ? " << std::is_same_v<decltype(arr1), ArrayWrapper<char, 7>> << '\n';
    double darr[]{1.7, 4.1};
    ArrayWrapper arr2{darr}; //CTAD
    std::cout << "Is arr2 has a type of ArrayWrapper<double, 2> ? " << std::is_same_v<decltype(arr2), ArrayWrapper<double, 2>> << '\n';
    std::cout << "***************4******************\n";
}