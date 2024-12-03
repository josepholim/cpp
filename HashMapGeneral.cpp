#include <iostream>
#include <vector>
#include <functional>

template <typename Key, typename Value, typename HashFunc = std::hash<Key>>
class HashMap {
public:
  HashMap(size_t initialCapacity = 1, double loadFactor = 1) : table(initialCapacity), loadFactor(loadFactor) {}

  size_t computeHash(const Key& key, size_t sz) {
    return hashFunc(key) % sz;
  }

  void insert(const Key& key, const Value& value) {
    if (size() >= table.size() * loadFactor) {
      resize();
    }
    size_t index = computeHash(key, table.size());
    table[index].push_back(std::make_pair(key, value));
  }

  Value& find(const Key& key) {
    size_t index = computeHash(key, table.size());
    for (auto& pair : table[index]) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    throw std::out_of_range("Key not found");
  }

  bool contains(const Key& key) {
    try {
      find(key);
      return true;
    } catch (const std::out_of_range&) {
      return false;
    }
  }

  size_t size() const {
    size_t count = 0;
    for (const auto& bucket : table) {
      count += bucket.size();
    }
    return count;
  }

private:
  std::vector<std::vector<std::pair<Key, Value>>> table;
  HashFunc hashFunc;
  double loadFactor;

  void resize() {
    size_t newCapacity = table.size() * 2;
    std::vector<std::vector<std::pair<Key, Value>>> newTable(newCapacity);
    for (const auto& bucket : table) {
      for (const auto& pair : bucket) {
        size_t index = computeHash(pair.first, newCapacity);
        newTable[index].push_back(pair);
      }
    }
    table = std::move(newTable);
  }
};

int main() {
  HashMap<std::string, int> stringIntMap;
  stringIntMap.insert("apple", 10);
  stringIntMap.insert("banana", 20);
  stringIntMap.insert("cherry", 30);

  int value = stringIntMap.find("banana");
  std::cout << "Value for key \"banana\": " << value << std::endl;

  if (stringIntMap.contains("orange")) {
    std::cout << "Key \"orange\" exists" << std::endl;
  } else {
    std::cout << "Key \"orange\" does not exist" << std::endl;
  }

  if (stringIntMap.contains("apple")) {
    std::cout << "Key \"apple\" exists" << std::endl;
  } else {
    std::cout << "Key \"apple\" does not exist" << std::endl;
  }
  
  return 0;
}