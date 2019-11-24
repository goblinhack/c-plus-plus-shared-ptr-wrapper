Simple C++ 11 wrapper for std::shared_ptr
=========================================

Do you want to wrap shared_ptr so you can add data to help with debugging?
- of course you do! e.g.:

<pre>
//
// Create two classes that refer to each other. Once the references are
// reset, the classes should be auto destructed.
//
#include "shared_ptr_wrapper.h"

typedef SmartPointerWrapper< class Bar > Barp;

class Bar {
public:
    Barp other;
    Bar(void) { }
    ~Bar() { }
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

output (with some extra debugs):

<pre>
    create classes
    ==============
    init SmartPointerWrapper(0x7f9a29c029f8, nullptr)
    new Bar(0x7f9a29c029f8)
    make_shared SmartPointerWrapper(0x7ffeea9f16b8, bar1)
    init SmartPointerWrapper(0x7f9a29c02a38, nullptr)
    new Bar(0x7f9a29c02a38)
    make_shared SmartPointerWrapper(0x7ffeea9f16e0, bar2)

    create reference loop
    =====================
    rename SmartPointerWrapper(0x7f9a29c029f8, ref to bar2)
    rename SmartPointerWrapper(0x7f9a29c02a38, ref to bar1)

    remove reference loop
    =====================
    reset SmartPointerWrapper(0x7f9a29c029f8, ref to bar2)
    reset SmartPointerWrapper(0x7f9a29c02a38, ref to bar1)

    end of main, expect auto destruct
    =================================
    delete SmartPointerWrapper(0x7ffeea9f16e0, bar2)
    delete Bar(0x7f9a29c02a38)
    delete SmartPointerWrapper(0x7f9a29c02a38, ref to bar1)
    delete SmartPointerWrapper(0x7ffeea9f16b8, bar1)
    delete Bar(0x7f9a29c029f8)
    delete SmartPointerWrapper(0x7f9a29c029f8, ref to bar2)
</pre>

Building
========

Do

<pre>
    sh ./RUNME
</pre>

Or, if that fails, manual build:

<pre>
    c++ -std=c++11 -Werror -g -ggdb3 -O2 -Wall -Wall -c -o .o/shared_ptr_wrapper.o shared_ptr_wrapper.cpp
    c++ .o/shared_ptr_wrapper.o  -o shared_ptr_wrapper
</pre>

To test:

<pre>
    ./shared_ptr_wrapper
</pre>
