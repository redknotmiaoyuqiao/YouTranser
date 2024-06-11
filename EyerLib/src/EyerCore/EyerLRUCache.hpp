#ifndef EYERLIB_EYERLRUCACHE_HPP
#define EYERLIB_EYERLRUCACHE_HPP

#include <mutex>
#include <list>
#include <memory>
#include <map>
#include <unordered_map>
#include "EyerString.hpp"
#include "EyerLog.hpp"

namespace Eyer
{
    template<typename key_t, typename value_t>
    class EyerLRUCache {
    public:
        typedef typename std::pair<key_t, value_t> key_value_pair_t;
        typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

        EyerLRUCache(size_t max_size)
            : _max_size(max_size)
        {
        }

        void Put(const key_t& key, const value_t& value) {
            auto it = _cache_items_map.find(key);
            _cache_items_list.push_front(key_value_pair_t(key, value));
            if (it != _cache_items_map.end()) {
                _cache_items_list.erase(it->second);
                _cache_items_map.erase(it);
            }
            _cache_items_map[key] = _cache_items_list.begin();

            if (_cache_items_map.size() > _max_size) {
                auto last = _cache_items_list.end();
                last--;
                _cache_items_map.erase(last->first);
                _cache_items_list.pop_back();
            }
        }

        const value_t Get(const key_t& key) {
            auto it = _cache_items_map.find(key);
            if (it == _cache_items_map.end()) {
                // throw std::range_error("There is no such key in cache");
                return value_t();
            } else {
                _cache_items_list.splice(_cache_items_list.begin(), _cache_items_list, it->second);
                return it->second->second;
            }
        }

        bool Exists(const key_t& key) const {
            return _cache_items_map.find(key) != _cache_items_map.end();
        }

        size_t Size() const {
            return _cache_items_map.size();
        }

    private:
        std::list<key_value_pair_t> _cache_items_list;
        std::map<key_t, list_iterator_t> _cache_items_map;
        size_t _max_size;
    };
}

#endif //EYERLIB_EYERLRUCACHE_HPP
