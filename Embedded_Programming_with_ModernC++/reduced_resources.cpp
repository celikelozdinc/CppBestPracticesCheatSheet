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
            //...
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
        other.len_ = 0;
        other.data_ = nullptr;
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


int main() {
    /************************* Move Semantic **********************/
    std::vector<BigData> vec{};
    vec.push_back(BigData(1000));
    return EXIT_SUCCESS;
    /**************************************************************/
}