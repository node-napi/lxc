#include <cstring>
#include <string>

std::string get_error_from_num(int num) {
    return std::string(strerror(num));
}