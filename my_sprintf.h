#include <string>
#include <string.h>

std::string string_sprintf (const char *format, ...)
{
    va_list args;
    char *buf;

    va_start(args, format);

    if (vasprintf(&buf, format, args) == -1) {
        throw std::bad_alloc();
    }

    std::string ret = buf;
    free(buf);

    va_end(args);

    return (ret);
}
