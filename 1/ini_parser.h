#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>

namespace Consts {
const char* const EQUAL_SYMBOL = "=";
const char* const COMMENT_SYMBOL = ";";
const char* const SECTION_START = "[";
const char* const SECTION_END = "]";
}

class ini_parser {
private:
    std::map<std::string, std::string> data;

    static std::string trim(const std::string& str);

    template<typename T>
    T convert(const std::string& value) const;

public:
    ini_parser(const std::string& fileName);
    template <typename T>
    T get_value(const std::string& key) const;
    ~ini_parser() = default;
};

#endif // INI_PARSER_H
