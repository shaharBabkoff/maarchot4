#include "MySingleton.h"

// Override getInstance to return the correct derived type
MySingleton* MySingleton::getInstance() {
    return static_cast<MySingleton*>(SingletonBase::getInstance());
}

void MySingleton::doSomething() {
     std::cout << "Singleton instance address: " << this << std::endl;
}
