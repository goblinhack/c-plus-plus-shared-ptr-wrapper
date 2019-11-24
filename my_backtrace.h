#ifndef _MY_BACKTRACE_H_
#define _MY_BACKTRACE_H_

#include <array>
#include <string>

class Traceback {
    static const int max_traceback = 63;
    std::array<void *, max_traceback> tb;
    int size;
public:
    Traceback(void);
    std::string to_string(void);
};
#endif
