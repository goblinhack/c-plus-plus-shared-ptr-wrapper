#include <iostream>
#include <sstream>
#include <string>
#include "shared_ptr_wrapper.h"

typedef SmartPointerWrapper< class Foo > Foop;

class Foo {
private:
    std::string data;
    void debug (const std::string &what) {
#ifdef DEBUG
        std::cout << what << " " << to_string() << std::endl;
#endif
    }
public:
    Foop other;
    Foo(std::string data) : data(data) {
        debug("new");
    }
    ~Foo() {
        debug("delete");
    }
    std::string to_string (void) {
        auto address = static_cast<const void*>(this);
        std::stringstream ss;
        ss << address;  
        return "Foo(" + ss.str() + ", data=" + data + ")";
    }
};

typedef SmartPointerWrapper< class Bar > Barp;

class Bar {
private:
    void debug (const std::string &what) {
#ifdef DEBUG
        std::cout << what << " " << to_string() << std::endl;
#endif
    }
public:
    Barp other;
    Bar(void) {
        debug("new");
    }
    ~Bar() {
        debug("delete");
    }
    std::string to_string (void) {
        auto address = static_cast<const void*>(this);
        std::stringstream ss;
        ss << address;  
        return "Foo(" + ss.str() + ")";
    }
};

int main (void)
{
    auto foo1 = SmartPointerWrapper< class Foo >(std::string("ref to foo1"), 
                                                 std::string("foo1-data"));

    std::cout << "\ncreate classes" << std::endl;
    std::cout << "==============" << std::endl;
    auto bar1 = SmartPointerWrapper< class Bar >(std::string("bar1"));
    auto bar2 = SmartPointerWrapper< class Bar >(std::string("bar2"));

    std::cout << "\ncreate reference loop" << std::endl;
    std::cout << "=====================" << std::endl;
    bar1->other = bar2;
    bar1->other.rename(std::string("ref to bar2"));

    bar2->other = bar1;
    bar2->other.rename(std::string("ref to bar1"));

    std::cout << "\nremove reference loop" << std::endl;
    std::cout << "=====================" << std::endl;
    bar1->other.reset();
    bar2->other.reset();

    std::cout << "\nend of main, expect auto destruct" << std::endl;
    std::cout << "=================================" << std::endl;
}
