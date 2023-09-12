#include <iostream>
#include <fstream>
#include <type_traits>

/**
 * Answers corresponds to:
 * https://github.com/necatiergin/CPP_KURSU_KODLAR/tree/main/1214_LAMBDA_EXPRESSIONS/questions
 */
int main() {
    std::ofstream ofs{"./out/lambda.log"};
    if (!ofs) {
        std::cerr << "Output file could not be created!\n";
        exit(EXIT_FAILURE);
    }

    ofs << "********************Answer for Q6********************\n";
    int a[5]{};
    //auto f2 = [a=a] {a = nullptr;}; //=>Cannot assign to a variable captured by copy in a non-mutable lambda
    auto f3 = [a=a, &out = ofs] () mutable {
        out << "f3()\n";
        out << "\t\t\t";
        out << "Address of a: "<< (void*)a << ", size of a: "<< sizeof(a) << '\n';
        a = nullptr; //=> array decay
    };

    ofs << typeid(decltype(f3)).name() << '\n';
    f3();
    ofs << "\n\n";


    auto f6 = [a = a , &out = ofs] () {
        out << "f6()\n";
        ++ *a;
        //*a = *a + 10;

        out << "\t\t\t";
        out << "Address of a: "<< (void*)a << ", size of a: "<< sizeof(a) << '\n';
        out << "\t\t\t";
        out << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << ", " << a[4] << '\n';
    };
    ofs << typeid(decltype(f6)).name() << '\n';
    f6();
    ofs << "\n\n";

    auto f10 = [a, &out = ofs] () mutable {
        out << "f10()\n";

        for (auto& item : a) {
            item += 10;
        }

        out << "\t\t\t";

        for (const auto& item : a) {
            out << item << ",";
        }
    };
    ofs << typeid(decltype(f10)).name() << '\n';
    f10();
    ofs << "\n\n\n\n";

    ofs << "Address of a: "<< (void*)a << '\n';
    ofs << "Address of a: "<< (void*)&a[0] << '\n';
    for (const auto& item : a) {
        ofs << item << ",";
    }
    ofs << "\n";
    ofs << "********************Answer for Q6********************\n";
}