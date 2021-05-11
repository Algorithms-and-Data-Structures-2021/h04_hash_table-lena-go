#include "hash_table.hpp"
#include <iostream>

#include <stdexcept>

namespace itis {

  int HashTable::hash(int key) const {
    return utils::hash(key, static_cast<int>(buckets_.size()));
  }

  HashTable::HashTable(int capacity, double load_factor) : load_factor_{load_factor} {
    if (capacity <= 0) {
      throw std::logic_error("hash table capacity must be greater than zero");
    }

    if (load_factor <= 0.0 || load_factor > 1.0) {
      throw std::logic_error("hash table load factor must be in range [0...1]");
    }

    // Tip: allocate hash-table buckets

    buckets_.resize(capacity);
  }

  std::optional<std::string> HashTable::Search(int key) const {
    // Tip: compute hash code (index) and use linear search
    int ind = hash(key);
    for (auto iter = buckets_[ind].begin(); iter != buckets_[ind].end(); iter++)
    {
      if (iter->first == key)
      {
        return iter->second;
      }
    }
    return std::nullopt;
  }

  void HashTable::Put(int key, const std::string &value) {
    // Tip 1: compute hash code (index) to determine which bucket to use

    int ind = hash(key);
    // Tip 2: consider the case when the key exists (read the docs in the header file)

    if (ContainsKey(key))
    {
      for (auto iter = buckets_[ind].begin(); iter != buckets_[ind].end(); iter++) {
        if (iter->first == key)
        {
          iter->second = value;
          break;
        }
      }
      return;
    }

    if (static_cast<double>(num_keys_) / buckets_.size() >= load_factor_) {
      // Tip 3: recompute hash codes (indices) for key-value pairs (create a new hash-table)
      // Tip 4: use utils::hash(key, size) to compute new indices for key-value pairs
      auto new_table = HashTable(static_cast<int>(capacity() * kGrowthCoefficient), load_factor_);
      for (auto bucket: buckets_)
      {
        for (auto item: bucket)
        {
          int new_hash = utils::hash(item.first, new_table.capacity());
          new_table.buckets_[new_hash].push_back(item);
        }
      }
      buckets_ = new_table.buckets_;
      ind = hash(key);
    }

    std::pair<int, std::string> new_item {key, value};
    buckets_[ind].push_back(new_item);
    num_keys_++;
  }

  std::optional<std::string> HashTable::Remove(int key) {
    // Tip 1: compute hash code (index) to determine which bucket to use
    int ind = hash(key);
    // TIp 2: find the key-value pair to remove and make a copy of value to return
    std::optional<std::string> item = Search(key);
    if (item)
    {
      for (auto iter = buckets_[ind].begin(); iter != buckets_[ind].end(); iter++)
      {
        if (iter->first == key)
        {
          std::string value {iter->second};
          buckets_[ind].erase(iter);
          num_keys_--;
          return value;
        }
      }
    }
    return std::nullopt;
  }

  bool HashTable::ContainsKey(int key) const {
    // Note: uses Search(key) which is not initially implemented
    return Search(key).has_value();
  }

  bool HashTable::empty() const {
    return size() == 0;
  }

  int HashTable::size() const {
    return num_keys_;
  }

  int HashTable::capacity() const {
    return static_cast<int>(buckets_.size());
  }

  double HashTable::load_factor() const {
    return load_factor_;
  }

  std::unordered_set<int> HashTable::keys() const {
    std::unordered_set<int> keys(num_keys_);
    for (const auto &bucket : buckets_) {
      for (const auto &[key, _] : bucket) {
        keys.insert(key);
      }
    }
    return keys;
  }

  std::vector<std::string> HashTable::values() const {
    std::vector<std::string> values;
    for (const auto &bucket : buckets_) {
      for (const auto &[_, value] : bucket) {
        values.push_back(value);
      }
    }
    return values;
  }

}  // namespace itis