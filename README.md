Simple C++ 11 wrapper for std::shared_ptr
=========================================

Do you want to wrap shared_ptr so you can add debugging or anything else
you want on top (perhaps to help debug leaks) - of course you do! e.g.:

<pre>
#include <iostream>
#include <string>
#include "shared_ptr_wrapper.h"

typedef SmartPointerWrapper< class Bar > Barp;

class Bar {
private:
    void debug (const std::string &what) {
        std::cout << what << " Bar(" << this << ")" << std::endl;
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
    auto bar1 = SmartPointerWrapper< class Bar >(std::string("bar1"));
    auto bar2 = SmartPointerWrapper< class Bar >(std::string("bar2"));

    bar1->other = bar2;
    bar1->other.rename(std::string("ref to bar2"));

    bar2->other = bar1;
    bar2->other.rename(std::string("ref to bar1"));

    bar1->other.reset();
    bar2->other.reset();
}
</pre>

output:

<pre>
init SmartPointerWrapper(0x7fdc48c029f8, nullptr)
new Bar(0x7fdc48c029f8)
make_shared SmartPointerWrapper(0x7ffee51dd6d8, bar1)
init SmartPointerWrapper(0x7fdc48c02a38, nullptr)
new Bar(0x7fdc48c02a38)
make_shared SmartPointerWrapper(0x7ffee51dd700, bar2)
delete SmartPointerWrapper(0x7ffee51dd700, bar2)
delete Bar(0x7fdc48c02a38)
delete SmartPointerWrapper(0x7fdc48c02a38, ref to bar1)
delete SmartPointerWrapper(0x7ffee51dd6d8, bar1)
delete Bar(0x7fdc48c029f8)
delete SmartPointerWrapper(0x7fdc48c029f8, ref to bar2)
</pre>

Building
========

Do

<pre>
    sh ./RUNME
</pre>

Or, if that fails, manual build:

<pre>
    c++ -std=c++11 -Werror -g -ggdb3 -O2 -Wall -Wall -c -o .o/main.o main.cpp
    c++ -std=c++11 -Werror -g -ggdb3 -O2 -Wall -Wall -c -o .o/shared_ptr_wrapper.o shared_ptr_wrapper.cpp
    c++ -std=c++11 -Werror -g -ggdb3 -O2 -Wall -Wall -c -o .o/vector_bounds_check.o vector_bounds_check.cpp
</pre>

To test:

<pre>
    ./bounds_check
</pre>
