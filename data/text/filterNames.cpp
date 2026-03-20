#include <vector>
#include <string>

std::vector<std::string> filterNames(const std::vector<std::string>& names) {
    std::vector<std::string> result;
    for (const auto& name : names) {
        if (name.size() > 3) {
            result.push_back(name);
        }
    }
    return result;
}
