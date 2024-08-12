#ifndef ERROR_UTILS_H
#define ERROR_UTILS_H
#include <cstring>
#include <string>

std::string get_error_from_num(int num) {
    return std::string(strerror(num));
}
#endif // ERROR_UTILS_H