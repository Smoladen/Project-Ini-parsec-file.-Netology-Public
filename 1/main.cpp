#include "ini_parser.h"
#include <iostream>

int main() {
    try {
        ini_parser parser("config.ini");
        int int_value = parser.get_value<int>("section1.key1");
        std::string string_value = parser.get_value<std::string>("section2.key2");
        std::cout << "Integer value: " << int_value << std::endl;
        std::cout << "String value: " << string_value << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
    }
    return 0;
}
