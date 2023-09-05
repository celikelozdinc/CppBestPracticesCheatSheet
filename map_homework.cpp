#include <map>
#include <string>
#include <iostream>
#include <fstream>

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

    ofs.close();
    return EXIT_SUCCESS;
}