#ifndef GUARD_H
#define GUARD_H

#include <pthread.h>

class Guard {
public:
    // Constructor that locks the mutex
    explicit Guard(pthread_mutex_t& mutex) : m_mutex(mutex) {
        pthread_mutex_lock(&m_mutex);
    }

    // Destructor that unlocks the mutex
    ~Guard() {
        pthread_mutex_unlock(&m_mutex);
    }

    // Delete copy constructor and assignment operator to prevent copying
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;

private:
    pthread_mutex_t& m_mutex;
};

#endif // GUARD_H
