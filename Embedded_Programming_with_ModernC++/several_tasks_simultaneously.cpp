#include <iostream>
#include <thread>
#include <atomic>

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
    /**************************************************************/

    return EXIT_SUCCESS;
}