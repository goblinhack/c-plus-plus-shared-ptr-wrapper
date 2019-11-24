#ifndef MY_SHARED_PTR
#define MY_SHARED_PTR
#include <memory>
#include <string>
#include <iostream>
#define DEBUG
//#include "my_ptrcheck.h"

template <typename T> class SmartPointerWrapper {
private:
    std::shared_ptr<T> sptr;
    std::string name {"nullptr"};

    void debug (const std::string &what) {
#ifdef DEBUG
        std::cout << what << " SmartPointerWrapper(" << this << ", " << 
                     name << ")" << std::endl;
#endif
    }
public:
    // explicit means constructor must match exactly
    template <typename ...ARGS> explicit 
      SmartPointerWrapper(const std::string &name, ARGS... a) : name(name) { 
        sptr = std::make_shared<T>(a...);
        debug("make_shared");
        //newptr(this, this->name.c_str());
    }

    explicit SmartPointerWrapper(const std::string &name) : name(name) { 
        sptr = std::make_shared<T>();
        debug("make_shared");
        //newptr(this, this->name.c_str());
    }

    explicit SmartPointerWrapper(void) {
        debug("init");
        //newptr(this, this->name.c_str());
    }

    ~SmartPointerWrapper() {
        //oldptr(this);
        debug("delete");
    }

    void rename(const std::string &name) { 
        this->name = name;
        //oldptr(this);
        //newptr(this, this->name.c_str());
    }

    T* const operator->() { return sptr.operator->(); }
    T* get() const { return sptr.get(); }
    T& operator*() { return *sptr; }
    const T& operator*() const { return *sptr; }
    operator bool() const { return (bool)sptr; }
    void reset() { sptr.reset(); }
};
#endif
