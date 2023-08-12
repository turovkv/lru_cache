#pragma once

#include "product_details.h"
#include "lru_cache.h"

class IRepository {
public:
    virtual ProductDetails fetchProductDetails(int productId) = 0;

    virtual std::vector<int> getProductIds() = 0;

    virtual ~IRepository() = default;
};


class StubRepository : public IRepository {
private:
    std::unordered_map<int, ProductDetails> db_;

public:
    StubRepository();

    ProductDetails fetchProductDetails(int productId) override;

    std::vector<int> getProductIds() override;
};

class LRUCachedRepository : public IRepository {
private:
    std::unique_ptr<IRepository> repo_ptr_;
    lru_cache::LRUCache<int, ProductDetails> cache_;

public:
    LRUCachedRepository(std::unique_ptr<IRepository> rep, int capacity);

    ProductDetails fetchProductDetails(int productId) override;

    std::vector<int> getProductIds() override;
};
