#ifndef MY_SINGLETON_H
#define MY_SINGLETON_H

#include "SingletonBase.h"
#include <iostream>

class MySingleton : public SingletonBase {
public:
    static MySingleton* getInstance();

    void doSomething();

protected:
    MySingleton() = default;
    ~MySingleton() = default;
};

#endif // MY_SINGLETON_H
