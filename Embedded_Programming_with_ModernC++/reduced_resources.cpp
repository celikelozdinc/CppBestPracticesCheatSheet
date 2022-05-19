#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

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
    std::vector<BigData> vec{};
    vec.push_back(BigData(1000));
    /**************************************************************/
    /******************** Perferct Forwarding**********************/
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
    return EXIT_SUCCESS;
}