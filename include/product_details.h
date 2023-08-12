#pragma once

#include <string>
#include <vector>

struct ProductDetails {
    int productId;
    std::string productName;
    std::string description;
    std::vector<uint8_t> image;
    std::vector<std::string> comments;
};
