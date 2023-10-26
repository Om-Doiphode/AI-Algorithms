#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 4;  // Replace with the desired size of the vector
    std::vector<int> forPositive;

    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1);

    for (int i = 0; i < n; i++) {
        int randomValue = distribution(gen);
        forPositive.push_back(randomValue);
    }

    // Print the generated vector
    for (int value : forPositive) {
        std::cout << value << ' ';
    }

    return 0;
}
