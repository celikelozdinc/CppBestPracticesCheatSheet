#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <array>
#include <memory>

static std::size_t allocations{0};
static std::size_t deallocations{0};

struct MyInt {
    MyInt() : i_{-1} {
        std::cout << "DEFAULT Hello from " << i_ << "\n";
    }
    explicit MyInt(int i) : i_{i} {
        std::cout << "Hello from " << i_ << "\n";
    }

    ~MyInt() {
        std::cout << "Good bye from " << i_ << "\n";
    }

    int i_;
};

struct MyClass {
    std::string str{"VALUEVALUEVALUE"};
    //double d{8.0};
    //int val{5};
};

void* operator new(std::size_t sz) {
    std::cout << "Allocation of size : " << sz << "\n";
    allocations += 1;
    return std::malloc(sz);
}

void operator delete(void* ptr) {
    std::cout << "Deallocation\n";
    deallocations += 1;
    std::free(ptr);
}

void getInfo(){
    std::cout << "  Number of allocations : " << allocations << "\n";
    std::cout << "  Number of deallocations : " << deallocations << "\n";
}

class BigData {
public:
    explicit BigData(size_t len) : len_{len}, data_{new int[len]} {
        std::cout << "BigData::BigData(size_t len)\n";
    }

    //Copy C'tor
    BigData(const BigData& other): len_{other.len_}, data_{new int[other.len_]} {
        std::cout << "BigData::BigData(const BigData& other)\n";
        std::copy(other.data_, other.data_ + len_, data_);
    }

    //Copy Assignment
    BigData& operator=(const BigData& other) {
        std::cout << "BigData::operator=(const BigData& other)\n";
        if (&other != this) {
            delete[] data_;

            // Initialize this
            data_ = new int[other.len_];

            // Copy from other
            len_ = other.len_;
            std::copy(other.data_, other.data_ + len_, data_);
        }
        return *this;
    }

    //Move C'tor
    /*
    BigData(BigData&& other) : len_{other.len_}, data_{new int[other.len_]} {
        std::cout << "BigData::BigData(BigData&& other)\n";
        for (auto i = 0 ;  i < len_ ; i++) {
            data_[i] = std::move(other.data_[i]);
        }
        other.len_ = 0;
        other.data_ = nullptr;
    }
    */
    BigData(BigData&& other) : len_{other.len_}, data_{other.data_} {
        std::cout << "BigData::BigData(BigData&& other)\n";
        // Invalidate other
        other.len_ = 0;
        other.data_ = nullptr;
    }

    //Move Assignment
    BigData& operator=(BigData&& other) {
        std::cout << "BigData::operator=(BigData&& other)\n";
        if (&other != this) {
            delete[] data_;

            // Steal resources from other
            len_ = other.len_;
            data_ = other.data_;

            // Invalidate other
            other.len_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~BigData() {
        std::cout << "BigData::~BigData()\n";
        if (nullptr != data_) {
            delete[] data_;
        }
    }
private:
    size_t len_;
    int* data_;
};


template <typename T, typename Arg>
T create(Arg&& a) {
    return T(std::forward<Arg>(a));
}

int main() {
    /************************* Move Semantic **********************/
    std::cout << "\n\n\n\n";
    std::vector<BigData> vec{};
    vec.push_back(BigData(1000));
    /**************************************************************/
    /******************** Perferct Forwarding**********************/
    std::cout << "\n\n\n\n";
    // LVALUES
    int five = 5;
    int myFive = create<int>(five);
    std::cout << "myFive : " << myFive << "\n";

    double dFive = 5.0;
    double myDF = create<double>(dFive);
    std::cout << "myDoubleFive : " << myDF << "\n";

    std::string str{"LValue"};
    std::string str2 = create<std::string>(str);
    std::cout << "str2 : " << str2 << "\n";

    // RVALUES
    int myFive2 = create<int>(5);
    std::cout << "myFive2 : " << myFive2 << "\n";

    std::string str3 = create<std::string>(std::string{"RValue"});
    std::cout << "str3 : " << str3 << "\n";

    std::string str4 = create<std::string>(std::move(str3));
    std::cout << "str4 : " << str4 << "\n";
    /**************************************************************/
    /************ Overloading operator new and delete *************/
    std::cout << "\n\n\n\n";
    double* myDoubleArr = new double[2]{2.2, 4.4};
    auto myC = new MyClass;
    delete myC;
    delete[] myDoubleArr;
    getInfo();
    /**************************************************************/
    /*********** STL : Sequential Containers***********************/
    std::array<std::string, 5> strings{"bir", "ki", "uc", "dort", "bes"};
    std::cout << "strings[1] : " << strings[1] << "\n";
    std::cout << "strings[3] : " << strings[3] << "\n";

    try {
        std::cout << strings.at(6) << "\n";
    } catch (std::exception& ex) {
        std::cout << "Caught an exception : " << ex.what() << "\n";
    }

    //std::cout << "strings[7] : " << strings[7] << "\n";  //=> Does not check boundaries
    /**************************************************************/
    /***************   Smart Pointers *****************************/
    std::cout << "\n\n\n\n";
    std::unique_ptr<MyInt> up1{ new MyInt{1998} };
    std::cout << "up1.get() : " << up1.get() << "\n";

    std::unique_ptr<MyInt> up2;
    up2 = std::move(up1);
    std::cout << "After moving from up1 to up2:\n";
    std::cout << "up1.get() : " << up1.get() << "\n";
    std::cout << "up2.get() : " << up2.get() << "\n";

    {
        std::unique_ptr<MyInt> localPtr {new MyInt{2003}};
    }

    up2.reset(new MyInt{2011});
    auto myI = up2.release();
    delete myI;

    std::unique_ptr<MyInt> up3{ new MyInt{2020} };
    std::unique_ptr<MyInt> up4{ new MyInt{2022} };
    std::cout << "up3.get() : " << up3.get() << "\n";
    std::cout << "up4.get() : " << up4.get() << "\n";
    std::swap(up3, up4);
    std::cout << "After swapping up4 with up3:\n";
    std::cout << "up3.get() : " << up3.get() << "\n";
    std::cout << "up4.get() : " << up4.get() << "\n";

    std::unique_ptr<MyInt[]> myInts = std::make_unique<MyInt[]>(3);
    std::cout << "myInts[0] : " << myInts[0].i_ << "\n";
    myInts[0] = MyInt{30};
    myInts[1] = MyInt{20};
    myInts[2] = MyInt{10};
    std::cout << "myInts[0] : " << myInts[0].i_ << "\n";

    /**************************************************************/
    return EXIT_SUCCESS;
}