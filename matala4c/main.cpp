#include "MySingleton.h"
#include <thread>
#include <iostream>

void threadFunction() {
    MySingleton* instance = MySingleton::getInstance();
    instance->doSomething();
}

int main() {
    // Create multiple threads
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);
    std::thread t3(threadFunction);

    // Wait for all threads to finish
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
