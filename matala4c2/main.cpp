#include "Guard.h"
#include <pthread.h>
#include <iostream>

pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

void criticalSection() {
    Guard guard(myMutex);  // Lock the mutex

    // Critical section code
    std::cout << "In the critical section" << std::endl;

    // Mutex will be automatically released when 'guard' goes out of scope
}

int main() {
    // Simulate entering a critical section
    criticalSection();

    return 0;
}
