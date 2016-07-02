#include <iostream>
#include <list>
#include <unordered_map>


template <typename K, typename V>
struct lru_cache {

    typedef std::pair<K, V> entry_type;
    typedef std::list<entry_type> cache_type;
    typedef typename cache_type::const_iterator const_iterator;

    typedef K key_type;
    typedef V value_type;

    lru_cache(unsigned const capacity) : cap_(capacity) {
    }

    value_type &operator[](key_type const &key) {

        auto it = map_.find(key);

        if (it == map_.end()) {

            if (cache_.size() == cap_) {
                map_.erase(cache_.back().first);
                cache_.pop_back();
            }

            std::cout << "value for key " << key << ": ";
            value_type val;
            std::cin >> val;

            cache_.push_front(std::make_pair(key, val));
            map_[key] = cache_.begin();

        } else {
            cache_.push_front(
                std::make_pair(it->first, it->second->second));
            cache_.erase(it->second);
            //cache_.splice(cache_.begin(), cache_, it->second);
        }

        return cache_.front().second;
    }

    const_iterator begin() const { return cache_.begin(); }
	const_iterator end() const { return cache_.end(); }

    unsigned cap_;
    cache_type cache_;

    std::unordered_map<key_type, typename cache_type::iterator> map_;
};


int main() {

    lru_cache<int, std::string> cache(5);

    lru_cache<int, std::string>::key_type key;

    while (std::cin >> key) {

        auto &value = cache[key];

        std::cout << "LRU cache contents" << '\n';
        for (auto &i : cache) {
            std::cout << i.first << ':' << i.second << '\n';
        }
    }

    return 0;
}