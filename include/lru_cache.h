#pragma once

#include <vector>
#include <list>
#include <unordered_map>
#include <mutex>
#include <iostream>

namespace lru_cache {

    template<typename Key, typename Val>
    class LRUCache {
    private:
        struct ListNode {
            Key key;
            Val value;

            template<typename KeyArg, typename ValArg>
            ListNode(KeyArg&& key, ValArg&& value) :
                    key(std::forward<KeyArg>(key)),
                    value(std::forward<ValArg>(value)) {}
        };

        using List = std::list<ListNode>;
        using ListIterator = typename List::const_iterator;

        size_t capacity_;
        List list_;
        std::unordered_map<Key, ListIterator> map_;
        std::mutex mutex_;

    public:
        explicit LRUCache(size_t capacity) : capacity_{capacity} {
            map_.reserve(capacity_);
        }

        std::optional<Val> get(const Key& key) {
            std::lock_guard guard(mutex_);

            if (auto map_iter = map_.find(key); map_iter != map_.end()) {
                list_.splice(list_.begin(), list_, map_iter->second);
                std::cout << "cached "; // for demonstration
                return map_iter->second->value;
            }

            return std::nullopt;
        }


        template<typename KeyArg, typename ValArg>
        bool put(KeyArg&& key, ValArg&& val) {
            std::lock_guard guard(mutex_);

            if (auto map_iter = map_.find(key); map_iter != map_.end()) {
                list_.splice(list_.begin(), list_, map_iter->second);
                list_.begin()->value = std::forward<ValArg>(val);
                return false;
            }

            list_.emplace_front(key, std::forward<ValArg>(val));
            map_[std::forward<KeyArg>(key)] = list_.begin();

            if (list_.size() > capacity_) {
                map_.erase(list_.back().key);
                list_.pop_back();
            }

            return true;
        }
    };

} // namespace lru_cache
