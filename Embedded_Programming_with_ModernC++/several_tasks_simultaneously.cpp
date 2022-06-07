#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <array>
#include <condition_variable>

std::atomic<int> x, y;
int readX, readY;
std::mutex mutex_;
std::condition_variable condVar;
bool ready;  //=> false

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
            /*
            coutMutex.lock();
            std::cout << name << " : " << "Work " << i << " done on Thread " << std::this_thread::get_id() << "\n";
            coutMutex.unlock();
            */
            std::lock_guard<std::mutex> lockG(coutMutex);
            std::cout << name << " : " << "Work " << i << " done on Thread " << std::this_thread::get_id() << "\n";
        }
    }


    std::string name;
    static std::mutex coutMutex;
};

void Receiver() {
    std::cout << "On thread " << std::this_thread::get_id() << ", RECEIVER started execution.\n";
    std::unique_lock<std::mutex> lck(mutex_);
    condVar.wait(lck, []{return ready;});
    // process
    std::cout << "On thread " << std::this_thread::get_id() << ", RECEIVER started processing shared data.\n";
}

void Sender() {
    {
        std::lock_guard<std::mutex> lck(mutex_);
        ready = true;
    }
    std::cout << "On thread " << std::this_thread::get_id() << ", SENDER will notify RECEIVER.\n";
    condVar.notify_one();
}

struct Counter {
    explicit Counter(const int& i) : current(i) {}
    void operator() () {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counterMutex.lock();
        std::cout << "On thread : " << std::this_thread::get_id() << ", second : " << current << "\n";
        counterMutex.unlock();
    }
    int current;
    static std::mutex counterMutex;
};

std::mutex Worker::coutMutex;
std::mutex Counter::counterMutex;

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

    // Countdown
    std::array<std::thread, 10> threads;
    for (int i = threads.size() ; i > 0 ; i --) {
        threads[i] = std::thread(Counter(i));
    }

    for (int i = threads.size() ; i > 0 ; i --) {
        threads[i].join();
    }

    /**************************************************************/
    /*******************  Condition Variables *********************/
    std::cout << "\n\n\n\n";
    std::thread rec(Receiver);
    std::thread send(Sender);
    rec.join();
    send.join();

    // On thread 140029112329792, RECEIVER started execution.
    // On thread 140029112329792, RECEIVER started processing shared data.
    // On thread 140029120722496, SENDER will notify RECEIVER
    
    // On thread 140430884705856, RECEIVER started execution.
    // On thread 140430893098560, SENDER will notify RECEIVER.
    // On thread 140430884705856, RECEIVER started processing shared data.
    /**************************************************************/

    return EXIT_SUCCESS;
}