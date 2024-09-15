#ifndef SINGLETON_BASE_H
#define SINGLETON_BASE_H

#include <pthread.h>

// Abstract base class for Singleton
class SingletonBase {
public:
    // Delete copy constructor and assignment operator to prevent copying
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

    // Virtual destructor to allow proper cleanup of derived classes
    virtual ~SingletonBase() = default;

    // Static method to get the Singleton instance
    static SingletonBase* getInstance();

protected:
    // Constructor is protected to prevent direct instantiation
    SingletonBase() = default;

private:
    static SingletonBase* instance;
    static pthread_mutex_t mutex;
};

#endif // SINGLETON_BASE_H
