#ifndef MY_SHARED_PTR
#define MY_SHARED_PTR
#include <memory>
#include <string>
//#include "my_ptrcheck.h"

template <typename T> class SmartPointerWrapper {
private:
    std::shared_ptr<T> sptr;
    std::string name;
public:
    // explicit means constructor must match exactly
    template <typename ...ARGS> explicit SmartPointerWrapper(const char *name, ARGS... a) { 
        this->name = name;
        sptr = std::make_shared<T>(a...);
        //newptr(this, this->name.c_str());
    }

    template <typename ...ARGS> explicit SmartPointerWrapper(ARGS... a) { 
        this->name = "<unnamed>";
        sptr = std::make_shared<T>(a...);
        //newptr(this, this->name.c_str());
    }

    explicit SmartPointerWrapper(const char *name) { 
        this->name = name;
        sptr = std::make_shared<T>();
        //newptr(this, this->name.c_str());
    }

    explicit SmartPointerWrapper(void) { 
        this->name = "<unnamed>";
        sptr = std::make_shared<T>();
        //newptr(this, this->name.c_str());
    }

    explicit SmartPointerWrapper (std::shared_ptr<T> obj) {
        sptr = obj;
    }

    // a destructor should not throw an exception
    ~SmartPointerWrapper() {
        //oldptr(this);
    }

    operator std::shared_ptr<T>() {
        return *sptr;
    }

    void reset() {
        sptr.reset();
    }

    T& operator*() { return *sptr; }

    const T& operator*() const { return *sptr; }

    T* const operator->() { return sptr.operator->(); }

    const T* const operator->() const { return sptr.operator->(); }

    T* get() const { return sptr.get(); }

    operator bool() const { return (bool)sptr; }

    void rename(std::string &name) { 
        this->name = name;
        //oldptr(this);
        //newptr(this, this->name.c_str());
    }
};
#endif
