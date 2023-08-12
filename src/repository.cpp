#include "repository.h"


StubRepository::StubRepository() {
    db_ = {
            {1, ProductDetails{.productName="1"}},
            {2, ProductDetails{.productName="2"}},
            {3, ProductDetails{.productName="3"}},
            {4, ProductDetails{.productName="4"}},
            {5, ProductDetails{.productName="5"}},
            {6, ProductDetails{.productName="6"}},
    };
}

ProductDetails StubRepository::fetchProductDetails(int productId) {
    return db_[productId];
}

std::vector<int> StubRepository::getProductIds() {
    return {1, 2, 3, 4, 5, 6};
}


LRUCachedRepository::LRUCachedRepository(std::unique_ptr<IRepository> rep, int capacity)
        : repo_ptr_(std::move(rep)), cache_(capacity) {}

ProductDetails LRUCachedRepository::fetchProductDetails(int productId) {
    auto ans = cache_.get(productId);
    if (ans.has_value()) {
        return ans.value();
    }
    auto value = repo_ptr_->fetchProductDetails(productId);
    cache_.put(productId, value);
    return value;
}

std::vector<int> LRUCachedRepository::getProductIds() {
    return repo_ptr_->getProductIds();
}

