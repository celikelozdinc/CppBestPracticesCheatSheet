#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

static constexpr const char* logFile = "./out/map_homework.log";

template<typename C>
void print_map(C c, std::ofstream& ofs) {
    ofs << "Size of container : " << c.size() << '\n';
    for (const auto& [i,s] : c)
        ofs << i << "->" << s << '\n';
}

int main(){
    /**
     * Bir map<k,v> olarak tutulan değerleri, multimap<v,k> açılımına taşıyın.
     */
    std::map<int, std::string> dictionary1{};
    int max = 10;
    for (int i = 0; i < max; ++i)
        dictionary1.emplace(i, std::to_string(i) + "," + std::to_string(max - i));

    for (int i = max; i < 2*max ; ++i)
        dictionary1.emplace(i, std::to_string(i-max) + "," + std::to_string(i));


    std::ofstream ofs {logFile};
    if (!ofs) {
        std::cerr << "Log file could not be opened!\n";
        exit(EXIT_FAILURE);
    }
    print_map(dictionary1, ofs);

    ofs << "\n\n\n";

    std::multimap<std::string, int> dictionary2{};
    for (const auto& [i,s] : dictionary1) {
        dictionary2.emplace(s, i);
    }
    print_map(dictionary2, ofs);

    ofs << "\n\n\n";

    /**
    * Bir multimap'te aynı anahtara karşılık gelen tüm değerleri değiştirin
    */
    std::multimap<int, std::string> dictionary3{};
    dictionary3.emplace(1, "one");
    dictionary3.emplace(2, "iki");
    dictionary3.emplace(1, "bir");
    dictionary3.emplace(1, "ein");

    const auto& [lower, upper] = dictionary3.equal_range(1);
    std::vector<std::pair<int, std::string>> range {lower, upper}; //=>RANGE Constructor
    // populate on vector
    for (auto& [i, s] : range) {
        s = "pır";
    }

    print_map(dictionary3, ofs);

    ofs << "\n\n\n";

    // print vector (in this case, multimap remains same)
    for (auto& [i, s] : range) {
        //std::cout << i << "->" << s << '\n';
        ofs << i << "->" << s << '\n';
    }

    ofs.close();
    return EXIT_SUCCESS;
}