#include <iostream>
#include <vector>

void error() {
    unsigned n;
    std::cin >> n;
    std::vector<std::pair<double, double>> input(n);
    double total_probability = 0;
    for (unsigned i = 0; i < n; ++i) {
        std::cin >> input[i].first;
        std::cin >> input[i].second;
        total_probability += input[i].second * input[i].first / 100;
    }
    std::cout.precision(9);
    for (unsigned i = 0; i < n; ++i) {
        std::cout << input[i].second * input[i].first / 100 / total_probability;
        std::cout << std::endl;
    }
}

int main() {
    error();
    return 0;
}
