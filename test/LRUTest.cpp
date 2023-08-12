#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "lru_cache.h"


using namespace lru_cache;

TEST_CASE("LRU") {
    SUBCASE("test 1") {
        LRUCache<int, int> c(3);
        CHECK(c.put(1, 1) == true);
        CHECK(c.put(2, 2) == true);
        CHECK(c.put(3, 3) == true);
        CHECK(c.put(4, 4) == true);

        CHECK(c.get(2) == 2);
        CHECK(c.get(3) == 3);
        CHECK(c.get(4) == 4);
        CHECK(c.get(1) == std::nullopt);

        CHECK(c.get(1) == std::nullopt);
        CHECK(c.get(2) == 2);
        CHECK(c.get(3) == 3);
        CHECK(c.get(4) == 4);
    }

    SUBCASE("test 2") {
        LRUCache<int, int> c(3);
        CHECK(c.put(1, 1) == true);
        CHECK(c.put(2, 2) == true);
        CHECK(c.put(3, 3) == true);
        CHECK(c.put(4, 4) == true);

        CHECK(c.get(1) == std::nullopt);
        CHECK(c.get(2) == 2);
        CHECK(c.get(3) == 3);
        CHECK(c.get(4) == 4);

        CHECK(c.get(2) == 2);

        CHECK(c.put(5, 5) == true);

        CHECK(c.get(1) == std::nullopt);
        CHECK(c.get(2) == 2);
        CHECK(c.get(3) == std::nullopt);
        CHECK(c.get(4) == 4);
        CHECK(c.get(5) == 5);
    }

    SUBCASE("test 3") {
        LRUCache<int, int> c(3);

        CHECK(c.get(1) == std::nullopt);

        CHECK(c.put(1, 1) == true);
        CHECK(c.get(1) == 1);

        CHECK(c.put(1, 2) == false);
        CHECK(c.get(1) == 2);
    }
}
