#include "probe.hpp"

namespace fs = std::experimental::filesystem;

std::vector<std::string> probe (std::string path) {
    std::vector<std::string> address;
    for (const auto & entry : fs::recursive_directory_iterator(path)) {
        if(!fs::is_directory(entry.status())) {
            address.push_back(entry.path());
        }
    }
    return address;
}