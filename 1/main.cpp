#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>

class ini_parser{
private:
    std::map<std::string, std::string> data;

    static std::string trim(const std::string& str){
        size_t first = str.find_first_not_of(" \t");
        if(first == std::string::npos)
            return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

    template<typename T>
    T convert(const std::string& value) const;

    template<>
    int convert<int>(const std::string& value) const {
        return std::stoi(value);
    }

    template<>
    std::string convert<std::string>(const std::string& value) const {
        return value;
    }

public:
    ini_parser(const std::string& fileName){
        std::ifstream file(fileName);
        if(!file.is_open()){
            throw std::runtime_error("File is not open");
        }
        std::string line;
        std::string currentSection;

        while (std::getline(file, line)){
            line = trim(line);
            if(line.empty() || line[0] == ';')
                continue;
            else if(line[0] == '[' && line.back() == ']')
                currentSection = trim(line.substr(1, line.size() - 2));
            else {
                size_t pos = line.find("=");
                if(pos == std::string::npos){
                    throw std::runtime_error("Invalid line " + line);
                }
                std::string key = trim(line.substr(0, pos));
                std::string value = trim(line.substr(pos + 1));
                data[currentSection + "." + key] = value;
            }
        }
    }

    template <typename T>
    T get_value(const std::string& key) const {
        auto it = data.find(key);
        if (it == data.end()) {
            throw std::runtime_error("Key not found: " + key);
        }
        return convert<T>(it->second);
    }
};

int main()
{
    try {
        ini_parser parser("config.ini");
        int int_value = parser.get_value<int>("section1.key1");
        std::string string_value = parser.get_value<std::string>("section2.key2");
        std::cout << "Integer value: " << int_value << std::endl;
        std::cout << "String value: " << string_value << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
