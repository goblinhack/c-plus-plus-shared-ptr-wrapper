Simple C++ 11 wrapper for std::shared_ptr
=========================================

Do you want to wrap shared_ptr so you can add debugging or anything else
you want on top (perhaps to help debug leaks) - of course you do!

<pre>
TODO
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
