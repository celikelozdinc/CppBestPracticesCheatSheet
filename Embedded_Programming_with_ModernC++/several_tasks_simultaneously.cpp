#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

std::atomic<int> x, y;
int readX, readY;

void X() {
    x.store(20);
    readY = y.load();
}

void Y() {
    y.store(10);
    readX = x.load();
}


void ThreadFunc() {
    std::cout<< "Thread ID : " << std::this_thread::get_id() <<", Hello from FUNCTION!\n";
}

struct ThreadFuncObj {
    void operator() () const {
        std::cout<< "Thread ID : " << std::this_thread::get_id() <<", Hello from FUNCTION OBJECT!\n";
    }
};

struct Worker {
    explicit Worker(const std::string& n) : name{n} {}
    void operator() () {
        for (int i = 1 ; i <= 3 ; i++) {
            // begin work
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            // end work
            coutMutex.lock();
            std::cout << name << " : " << "Work " << i << " done on Thread " << std::this_thread::get_id() << "\n";
            coutMutex.unlock();
        }
    }


    std::string name;
    static std::mutex coutMutex;
};

std::mutex Worker::coutMutex;

int main() {
    /***************   Synchronization and Ordering ***************/
    // Default memory mode : Sequential Consistency
    std::cout << "\n\n\n\n";
    readX = 0;
    readY = 0;
    std::thread tX(X);
    std::thread tY(Y);
    tX.join();
    tY.join();
    std::cout << "(readX, readY) = " << "(" << readX << "," << readY << ")\n";  //=> (20,0)/(0,10)
    /**************************************************************/
    /************************* Threads ****************************/
    std::cout << "\n\n\n\n";
    auto lambdaExpr = [](){std::cout<< "Thread ID : " << std::this_thread::get_id() <<", Hello from LAMBDA EXPRESSION!\n"; };
    std::cout<< "Thread ID : " << std::this_thread::get_id() <<", Hello from ***MAIN***\n";
    std:: thread t1{ThreadFunc};
    std::thread t2{ThreadFuncObj()};
    std::thread t3{lambdaExpr};

    std::cout << "Is t1 joinable? " << std::boolalpha << t1.joinable() << "\n";
    std::cout << "Is t2 joinable? " << std::boolalpha << t2.joinable() << "\n";
    std::cout << "Is t3 joinable? " << std::boolalpha << t3.joinable() << "\n";

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Is t1 joinable? " << std::boolalpha << t1.joinable() << "\n";
    std::cout << "Is t2 joinable? " << std::boolalpha << t2.joinable() << "\n";
    std::cout << "Is t3 joinable? " << std::boolalpha << t3.joinable() << "\n";

    /**************************************************************/
    /**********************  Mutexes     **************************/
    std::cout << "\n\n\n\n";
    std::thread herb = std::thread(Worker("Herb"));
    std::thread scott = std::thread(Worker("        Scott"));
    std::thread bjarne = std::thread(Worker("    Bjarne"));

    herb.join();
    scott.join();
    bjarne.join();
    /**************************************************************/

    return EXIT_SUCCESS;
}