#include "ini_parser.h"
#include <algorithm>

std::string ini_parser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

template<typename T>
T ini_parser::convert(const std::string& value) const {
    if constexpr (std::is_same_v<T, int>) {
        return std::stoi(value);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return value;
    } else {
        throw std::runtime_error("Unsupported conversion type");
    }
}

ini_parser::ini_parser(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("File is not open");
    }
    std::string line;
    std::string currentSection;

    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == Consts::COMMENT_SYMBOL[0])
            continue;
        else if (line[0] == Consts::SECTION_START[0] && line.back() == Consts::SECTION_END[0])
            currentSection = trim(line.substr(1, line.size() - 2));
        else {
            size_t pos = line.find(Consts::EQUAL_SYMBOL);
            if (pos == std::string::npos) {
                throw std::runtime_error("Invalid line " + line);
            }
            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));
            data[currentSection + "." + key] = value;
        }
    }
}

template <typename T>
T ini_parser::get_value(const std::string& key) const {
    auto it = data.find(key);
    if (it == data.end()) {
        throw std::runtime_error("Key not found: " + key);
    }
    return convert<T>(it->second);
}

// Explicit instantiation of template methods
template int ini_parser::get_value<int>(const std::string& key) const;
template std::string ini_parser::get_value<std::string>(const std::string& key) const;
