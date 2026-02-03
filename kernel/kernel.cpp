#include <iostream>
#include <cstring>
#include <optional>


struct Entry {
    std::string NAME;
    std::string PASSWORD;

    std::optional<std::string> USERNAME;
    std::optional<std::string> URL;
    std::optional<std::string> NOTE;
    std::optional<unsigned int> LAST_MODIFICATION_TIME;
    std::optional<unsigned int> CREATION_TIME;
};


class Manager {
    
};



int main() {

    std::cout << "Hello, kernel!" << std::endl;


}
