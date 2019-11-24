#include <iostream>
#include <string>
#include "shared_ptr_wrapper.h"

typedef SmartPointerWrapper< class Foo > Foop;

class Foo {
private:
    std::string name;
    void debug (const std::string &what) {
#ifdef DEBUG
        std::cout << what << " Foo(" << this << ", " << name << ")" << std::endl;
#endif
    }
public:
    Foop other;
    Foo(std::string name) : name(name) {
        debug("new");
    }
    ~Foo() {
        debug("delete");
    }
};

typedef SmartPointerWrapper< class Bar > Barp;

class Bar {
private:
    void debug (const std::string &what) {
#ifdef DEBUG
        std::cout << what << " Bar(" << this << ")" << std::endl;
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
};

int main (void)
{
//    auto foo1 = SmartPointerWrapper< class Foo >(std::string("ref to foo1"), 
//    std::string("foo1-data"));

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
