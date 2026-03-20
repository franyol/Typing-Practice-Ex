#include <vector>
#include <string>
#include <iostream>

struct Item {
    std::string name;
    int price;
    int quantity;
};

int calculateValue(const std::vector<Item>& items) {
    int total = 0;

    for (const auto& item : items) {
        if (item.quantity > 0) {
            total += item.price * item.quantity;
        }
    }

    return total;
}

std::vector<std::string> labelItems(const std::vector<Item>& items) {
    std::vector<std::string> result;

    for (const auto& item : items) {
        int value = item.price * item.quantity;

        if (value > 100) {
            result.push_back(item.name + " high");
        } else if (value > 50) {
            result.push_back(item.name + " medium");
        } else {
            result.push_back(item.name + " low");
        }
    }

    return result;
}

int main() {
    std::vector<Item> items = {
        {"A", 10, 2}, {"B", 30, 5}, {"C", 5, 1}
    };

    int total = calculateValue(items);
    auto labels = labelItems(items);

    std::cout << total << std::endl;
    return 0;
}
