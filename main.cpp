#include <iostream>
#include "include/repository.h"

int main() {
    LRUCachedRepository rep(std::make_unique<StubRepository>(), 3);

    for (int i = 1; i <= 5; i++) {
        std::cout << rep.fetchProductDetails(i).productName << '\n';
    }
    std::cout << "\n";
    for (int i = 5; i >= 1; i--) {
        std::cout << rep.fetchProductDetails(i).productName << '\n';
    }
    std::cout << "\n";
    for (int i = 1; i <= 5; i++) {
        std::cout << rep.fetchProductDetails(i).productName << '\n';
    }

    return 0;
}
