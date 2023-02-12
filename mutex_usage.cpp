/**
 * g++ mutex_usage.cpp -lpthread -o mutex ; ./mutex ; rm -rf ./mutex
 * https://medium.com/@simontoth/daily-bit-e-of-c-std-mutex-558fe54c9dc3
 * https://cplusplus.com/reference/mutex/unique_lock/
 * https://www.cppstories.com/2020/05/lambdas-async.html/
 */

#include <mutex>
#include <thread>
#include <iostream>

struct SharedData{
  int value{0};
  std::mutex mtx;
};

int main() {
  SharedData initialSharedData{.value=0, .mtx{}};

  auto thread1 = std::thread(
      [&initialSharedData]()
      {
        for (uint8_t u = 0; u < 100; u++) {
          std::unique_lock<std::mutex> lock(initialSharedData.mtx);
          initialSharedData.value += 1;
        }
      }
 );

  auto thread2 = std::thread(
      [&initialSharedData]()
      {
        for (uint8_t u = 0; u < 5; u++) {
          std::unique_lock<std::mutex> lock(initialSharedData.mtx);
          initialSharedData.value += 10;
        }
      }
  );

  thread1.join();
  thread2.join();

  std::cout << "SharedData : " << initialSharedData.value << "\n";

  return EXIT_SUCCESS;
}