/**
 * g++ thread_safe_map.cpp -std=c++17 -lpthread -o thread_safe_map ; ./thread_safe_map ; rm -rf ./thread_safe_map
 */

#include <iostream>
#include <map>
#include <string>
#include <thread>

struct Payload {
  std::map<std::string, uint64_t> dictionary;
};

int main() {
  Payload p{};
  //p.dictionary.emplace("KEY1", 0);

  auto callable1 = [&p](){
    for (uint8_t i = 0 ; i < 100 ; i++) {
      std::string key = "KEY1_" + std::to_string(i);
      //p.dictionary.insert(std::make_pair(key, i));
      p.dictionary.emplace(key, i);
    }
  };
  auto callable2 = [&p](){
    for (uint8_t i = 0 ; i < 5 ; i++) {
      std::string key = "KEY2_" + std::to_string(i);
      //p.dictionary.insert(std::make_pair(key, i));
      p.dictionary.emplace(key, i);
    }
  };
  auto th1 = std::thread(callable1);
  auto th2 = std::thread(callable2);

  th1.join();
  th2.join();

  for (const auto& [key, value] : p.dictionary) {
    std::cout << "dictionary[" << key << "] = " << value << "\n";
  }
  std::cout << "After execution of 2 threads, size of map: " << p.dictionary.size() << "\n";

  return EXIT_SUCCESS;
}