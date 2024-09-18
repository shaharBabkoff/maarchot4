#ifndef SINGLETON_BASE_H
#define SINGLETON_BASE_H

#include <pthread.h>

template <typename T>
class SingletonBase {
public:
    // Delete copy constructor and assignment operator to prevent copying
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

    // Static method to get the Singleton instance
    static T* getInstance() {
        if (instance == nullptr) {
            pthread_mutex_lock(&mutex);
            if (instance == nullptr) {
                instance = new T();  // Assuming T has a default constructor
            }
            pthread_mutex_unlock(&mutex);
        }
        return instance;
    }

protected:
    // Constructor is protected to prevent direct instantiation
    SingletonBase() = default;

    // Virtual destructor to allow proper cleanup of derived classes
    virtual ~SingletonBase() = default;

private:
    static T* instance;
    static pthread_mutex_t mutex;
};

// Initialize static member variables
template <typename T>
T* SingletonBase<T>::instance = nullptr;

template <typename T>
pthread_mutex_t SingletonBase<T>::mutex = PTHREAD_MUTEX_INITIALIZER;

#endif // SINGLETON_BASE_H
