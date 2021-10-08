#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <vector>

namespace fs = std::experimental::filesystem;

std::vector<std::string> probe (std::string path);


int main()
{
    std::cout << "welcome" << std::endl;
    std::string path = "./databases";
    std::vector<std::string> address = probe(path);
    std::cout << "size=" << address.size() << std::endl;
}

std::vector<std::string> probe (std::string path) {
    std::vector<std::string> address;
    for (const auto & entry : fs::recursive_directory_iterator(path)) {
        if(!fs::is_directory(entry.status())) {
            address.push_back(entry.path());
        }
    }
    return address;
}